/*************************************************************************
	> File Name: mypthread.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 May 2017 03:19:57 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void * thread_run(void* arg)
 {
    printf("new thread running\n");
    printf("pid : %d,tid : %u\n",getpid(),pthread_self());
     sleep(4);
//     pthread_detach(pthread_self());
//    pthread_exit((void*)123);
 }

int main()
{
    printf("main thread\n"); 
    printf("pid : %d,tid : %u\n",getpid(),pthread_self());
    pthread_t tid;
    pthread_create(&tid,NULL,thread_run,NULL);
 
     pthread_detach(tid);
    //  pthread_cancel(tid);
    void* ret;
    int err = pthread_join(tid,&ret);
    if(err == 0)
    {
        printf("wait success: %d\n",(int)ret);

    }else
    {
        printf("err :%d error msg: %s\n",err,strerror(err));
    }
    sleep(4);
    return 0;
}
