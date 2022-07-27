#include "keyboard.h"
#include "queue.h"
#include "zwzSignal.h"
#include "connection.h"
#include <string.h>
#include <stdlib.h>
#include <bios.h>

void print(void *useless, void *key);

void main()
{
	Queue *connectionQueue = newQueue(deleteConnection);
	Queue *signalQueue = newQueue(deleteSignal);
	Connection *c = NULL;
	c = newConnection("keyboard", NULL, print);
	queuePush(connectionQueue, c);

	while(1)
	{
		detectKeyBoard(signalQueue);
		triggerSignal(connectionQueue, signalQueue);
	}
}

void print(void *useless, void *key)
{
	printf("%c", keyToLetter(*(int*)key));
}