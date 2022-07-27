#ifndef __CONNECTION__
#define __CONNECTION__

#include "queue.h"
#include "signal.h"

typedef struct
{
    //链接的文本信息，若链接接受某信号，那么它们的文本信息应相同
    char *signalText;
    
    //信号的接收者
    void *receiver;
    
    //接收到信号后触发该函数，第一个参数是接收者，第二个是参数
    void (*slotFunction)(void *, void *);//这是一个函数指针
} Connection;

//新建连接
Connection *newConnection(char *signalText, void *receiver
                        , void (*slotFunction)(void *, void *));

//触发信号，信号和连接应保存在队列中，触发后signalQueue会清空
void triggerSignal(Queue *connectionQueue, Queue *signalQueue);

//删除连接
void deleteConnection(void *connection);

#endif