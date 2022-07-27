#include "queue.h"
#include "zwzSignal.h"
#include "connection.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void queueTest();
void square(void *useless, void *parameter);
void hello(void *useless, void *times);
void signalTest();

void main()
{
	signalTest();
}

void signalTest()
{
	//创建连接队列和信号队列
	Queue *connectionQueue = newQueue(deleteConnection);
	Queue *signalQueue = newQueue(deleteSignal);
	char str[100];
	int temp;
	int *x;
	Connection *c = NULL;
	Signal *s = NULL;

	//新建两个连接，分别触发square函数和hello函数
	c = newConnection("square", NULL, square);
	queuePush(connectionQueue, c);
	c = newConnection("hello", NULL, hello);
	queuePush(connectionQueue, c);

	while(1)
	{
		scanf("%s", str);
		if(strcmp(str, "square") == 0)
		{
			scanf("%d", &temp);
			
			//新建参数
			x = (int*)malloc(sizeof(int));
			*x = temp;

			//新建信号，文本为square，参数为指针x，参数删除函数为free
			s = newSignal("square", x, free);
			queuePush(signalQueue, s);
		}
		else if(strcmp(str, "hello") == 0)
		{
			scanf("%d", &temp);

			//新建参数
			x = (int*)malloc(sizeof(int));
			*x = temp;

			//新建信号，文本为hello，参数为指针x，参数删除函数为free
			s = newSignal("hello", x, free);
			queuePush(signalQueue, s);
		}
		else if(strcmp(str, "trigger") == 0)
		{
			//依次对比信号的文本和连接的文本，触发对应函数
			triggerSignal(connectionQueue, signalQueue);
		}
		else if(strcmp(str, "exit") == 0)
		{
			break;
		}
	}

	//删除两个队列，我的宝贝内存，让你受苦了
	deleteQueue(connectionQueue);
	deleteQueue(signalQueue);
}

void hello(void *useless, void *t)
{
	int *times = t;
	int i = 1;
	for(i = 1; i <= *times; i++)
	{
		printf("%d: hello\n", i);
	}
}

void square(void *useless, void *p)
{
	int *n = p;
	printf("%d\n", *n * *n);
}

void queueTest()
{
	Queue *q = newQueue(free);
	char str[100];
	int *x;
	int temp;
	QueueNode *i;
	while(1)
	{
		scanf("%s", str);
		if(strcmp(str, "push") == 0)
		{
			scanf("%d", &temp);
			x = (int*)malloc(sizeof(int));
			*x = temp;
			queuePush(q, x);
		}
		else if(strcmp(str, "top") == 0)
		{
			x = queueTop(q);
			printf("top = %d\n", *x);
		}
		else if(strcmp(str, "pop") == 0)
		{
			queuePop(q);
		}
		else if(strcmp(str, "show") == 0)
		{
			for(i = q->head; i != NULL; i = i->next)
			{
				printf("%d\n", *((int*)i->element));
			}
		}
		else if(strcmp(str, "exit") == 0)
		{
			break;
		}
	}
	deleteQueue(q);
}