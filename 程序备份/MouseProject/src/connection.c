#include "connection.h"
#include "queue.h"
#include "zwzSignal.h"
#include <stdlib.h>
#include <string.h>

Connection *newConnection(char *signalText, void *receiver
                        , void (*slotFunction)(void *, void *))
{
    Connection *connection = (Connection*)malloc(sizeof(Connection));
    connection->signalText = (char*)malloc(sizeof(char) * (strlen(signalText) + 1));
    strcpy(connection->signalText, signalText);
    connection->receiver = receiver;
    connection->slotFunction = slotFunction;
    return connection;
}

void triggerSignal(Queue *connectionQueue, Queue *signalQueue)
{
    QueueNode *iterator = NULL;//该变量一次指向connectionQueue中每个节点
    Connection *connection = NULL;
    Signal *signal = NULL;
    while(!queueEmpty(signalQueue))
    {
        //先取出队列头元素
        signal = queueTop(signalQueue);

        //循环枚举每一个connection
        for(iterator = connectionQueue->head; iterator != NULL; iterator = iterator->next)
        {
            connection = iterator->element;

            //若connection和signal文本相同，就触发函数
            if(strcmp(signal->signalText, connection->signalText) == 0)
            {
                connection->slotFunction(connection->receiver, signal->parameter);
            }
        }

        //最后把队列头删除，防止信号反复触发
        queuePop(signalQueue);
    }
}

void deleteConnection(void *connection)
{
    Connection *c = connection;
    free(c->signalText);//先删除文本
    free(c);//再删除连接
}