#include "queue.h"
#include <stdlib.h>

Queue *newQueue(void (*deleteElement)(void *))
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
	queue->tail = NULL;
	queue->deleteElement = deleteElement;
	return queue;
}

void queuePush(Queue *queue, void *element)
{
	//新开一个节点
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->element = element;
    node->next = NULL;
    if(queueEmpty(queue))
    {
        queue->tail = node;
        queue->head = node;
    }
    else
    {
		//先将尾节点的下一个设为node
		queue->tail->next = node;
		//再将尾节点设为node
		queue->tail = node;
	}
}

void *queueTop(Queue *queue)
{
	if(queueEmpty(queue))
	{
		return NULL;
	}
	return queue->head->element;
}

void queuePop(Queue *queue)
{
	QueueNode *node = queue->head;
	if(queueEmpty(queue))
	{
		return;
	}
	if(queue->head == queue->tail)//如果只有一个元素
	{
		queue->deleteElement(node->element);//先删除元素
		free(node);//再删除节点
		queue->head = NULL;
		queue->tail = NULL;
		return;
	}
	queue->head = node->next;//将头节点设为其下一个
	queue->deleteElement(node->element);//先删除元素
	free(node);//再删除节点
}

int queueEmpty(Queue *queue)
{
	return queue->tail == NULL;
}

void deleteQueue(void *queue)
{
	Queue* q = queue;
    while(!queueEmpty(q))
    {
        queuePop(q);
    }
    free(q);
}