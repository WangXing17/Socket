#include<pthread.h>
#include<stdio.h>
#include<errno.h>

void* thread_main(void* ptr)
{
  for(int i=0;i<5;i++)
  	printf("hello!%s,%d\n",ptr,i);
  return NULL;
}

int main(int argc, char** argv)
{

  pthread_t threadOne;  
  pthread_t threadTwo;
  char* msgOne = "I am messageOne!";
  char* msgTwo = "I am messageTwo!";
  //创建一个线程,创建成功返回0，否则返回error number
  if(pthread_create(&threadOne,NULL,&thread_main,(void*)msgOne) == 0)
	printf("线程1创建成功！\n");
  else
	//printf("线程创建失败:%s\n",strerror(errno));
	perror("线程1创建失败");
  
  if(pthread_create(&threadTwo,NULL,&thread_main,(void*)msgTwo) == 0)
	printf("线程2创建成功！\n");
  else
	//printf("线程创建失败:%s\n",strerror(errno));
	perror("线程2创建失败");
  

  //等待线程退出
  //pthread_join(threadOne, NULL);
  if(pthread_join(threadOne, NULL) == 0)
	printf("threadOne exit successful!\n");
  else
	perror("threadOne exit failure!");
  //pthread_join(threadTwo, NULL);
  if(pthread_join(threadTwo, NULL) == 0)
	printf("threadTwo exit successful!\n");
  else
	perror("threadTwo exit failure!");
  return 0;
}
