#include "mouse.h"
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "zwzSignal.h"
#include "connection.h"
#include "2graphics.h"

void draw(void *useless, void *p)
{
	MouseState *mp = p;
	if(mp->mouseClick == 1)
	{
		putBar(mp->mouseX, mp->mouseY, 30, 30, 6);
	}
}

void main()
{
	int driver = VGA;
	int mode = VGAHI;
	Queue *connectionQueue = newQueue(deleteConnection);
	Queue *signalQueue = newQueue(deleteSignal);
	Connection *c = NULL;
	Signal *s = NULL;

	c = newConnection("mouse", NULL, draw);
	queuePush(connectionQueue, c);

	initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
	setbkcolor(BLACK);
	setviewport(0, 0, 639, 479, 1);
	
	setcolor(RED);
	MouseInit();

	while(1)
	{
		clearFrameBuffer();
		NewMouse(signalQueue);
		triggerSignal(connectionQueue, signalQueue);
		showFrameBuffer();
	}
}