#include<stdio.h>
#include<stdlib.h>
#include <semaphore.h>

int blank[64];
sem_t semBlank;//空格子的信号量
sem_t semData;//数据的信号量

//消费者读数据
void *consumer(void *arg)
{
    //p
    int step = 0;//每次读取数据的下标
    while(1)
    {
        sem_wait(&semData);//等待数据信号量（p操作）
        //下面两行是临界区
        int data = blank[step];
        printf("consume  done... %d\n",data);

        step++;
        sem_post(&semBlank);//释放格子资源（v操作）
        step %= 64;//保证下标不越界
     //   sleep(1);
    }
}

void *producter(void *arg)
{
    int step = 0;
    while(1)
    {
       sem_wait(&semBlank);//等待格子资源（p操作--）
        int data = rand()%1234;
        blank[step] = data;
        printf("product done... %d\n",data);
        step++;
        sem_post(&semData);//释放数据资源（v操作++）
        step %= 64;
        sleep(2);
    }
}


int main()
{
    sem_init(&semBlank,0,64);
    sem_init(&semData,0,0);
    pthread_t c,p;
    pthread_create(&c,NULL,consumer,NULL);
    pthread_create(&p,NULL,producter,NULL);

    pthread_join(c,NULL);
    pthread_join(p,NULL);
    sem_destroy(&semBlank);
    sem_destroy(&semData);
    return 0;
}
