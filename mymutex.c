
#include<stdio.h>
#include<pthread.h>

int g_val = 0;
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;


void* thread_run(void*  argc)
{
    int tmp = 0;
    int i = 0;
    while(i < 5000)
    {
        pthread_mutex_lock(&mutex_lock);
        i++;
        tmp = g_val;
        printf("g_val : %d\n",g_val);//system call
        g_val = tmp + 1;

        pthread_mutex_unlock(&mutex_lock);
    }
}

int main()
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,thread_run,NULL);
    pthread_create(&tid2,NULL,thread_run,NULL);
    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("g_count: %d\n",g_val);
    return 0;
}
