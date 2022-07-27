#ifndef __QUEUE__
#define __QUEUE__

typedef struct _QueueNode
{
	struct _QueueNode *next;//单向链表，记录下一个节点
    void *element;//指向链表元素的指针
} QueueNode;

typedef struct
{
    QueueNode *head;//记录队列头
    QueueNode *tail;//记录队列尾
    void (*deleteElement)(void *);//队列元素释放函数指针
} Queue;

//新建队列，需要元素释放函数
Queue *newQueue(void (*deleteElement)(void *));

//向队列尾添加元素
void queuePush(Queue *queue, void *element);

//查询队列头元素
void *queueTop(Queue *queue);

//删除队列头元素
void queuePop(Queue *queue);

//查看队列是否为空，为空返回1，不为空返回0
int queueEmpty(Queue *queue);

//删除整个队列
void deleteQueue(void *queue);

#endif