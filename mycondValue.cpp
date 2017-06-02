#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct _node
{
    int data;
    struct _node* next;
}_node_t,*_node_p,**_node_pp;

_node_p head;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t need_product = PTHREAD_COND_INITIALIZER;

//GetNode
static _node_p GetNode(int data,_node_p node)
{
    _node_p tmp = (_node_p)malloc(sizeof(_node_t);
    if(NULL == tmp)
    {
        perror("malloc");
        exit(1);
    }
    tmp->data = data;
    tmp->next = node;
    return tmp;
}

//init
void init_list(_node_pp head)
{
   *head =  GetNode(0,NULL);         
}

int isEmpty(_node_p head)
{
    return head->next == NULL ? 1:0;
}

void pushFront(_node_p head,int data)
{
    if(head)
    {
        _node_p tmp = GetNode(data,NULL);
        _node_p cur = head->next;
        if(tmp)
        {
            tmp->next = cur;
            head->next = tmp;
        }
    }
}

static void FreeNode(_node_p node)
{
    if(node)
    {
        free(node);
        node = NULL;
    }
}

void PopFront(_node_p head,int* outData)
{
    if(!isEmpty(head))
    {
        _node_p tmp = head->next;
        head->next = tmp->next;
        *outData = tmp->data;
        FreeNode(tmp);
    }
}

void destoryList(_node_p head)
{
    while(!isEmpty(head))
    {
        int data = 0;
         PopFront(head,&data);
    }
    FreeNode(head);
}

void showList(_node_p head)
{
    if(head)
    {
        _node_p tmp = head->next;
        while(tmp)
        {
            printf("%d  ",tmp->data);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

void* product(void* arg)
{
        while(1)
        {
            pthread_mutex_lock(&lock);//get lock
            int data = rand()%1234;
            pushFront(head,data);
            printf("product done: %d\n ",data);
            pthread_mutex_unlock(&lock);//
            pthread_cond_signal(&need_product);//
            sleep(1);
        }
}
void* consume(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock);//get lock
        while(isEmpty(head))
        {
            printf("no data ,consume wait...\n");
            pthread_cond_wait(&need_product,&lock);//wait resource
        }//get lock again
        int data = 0;
        PopFront(head,&data);
        printf("consume done: %d \n",data);
        pthread_mutex_unlock(&lock);//
    }
}

int main()
{
     init_list(&head);
    pthread_t consumer,producter;

    pthread_create(&producter,NULL,product,head);

    pthread_create(&consumer,NULL,consume,head);
    pthread_join(consumer,NULL);
    pthread_join(producter,NULL);

     destoryList(head);
    return 0;
}

