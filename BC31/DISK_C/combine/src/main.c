#include "TEXTEDIT.H"
#include "Mouse.h"
#include <graphics.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"
#include "zwzSignal.h"
#include "connection.h"

void draw(void *useless, void *p)
{
	MouseState *mp = p;
	if(mp->mouseClick == 1)
	{
		circle(mp->mouseX, mp->mouseY, 5);
	}
}

void main()
{
	int driver = VGA;
	int mode = VGAHI;
	TextEdit *textEdit = NewTextEdit(100, 100, 200, 20);
	MouseState *mouse = (MouseState*)malloc(sizeof(MouseState));
	MouseState *mp;
	Queue *connectionQueue = newQueue(deleteConnection);
	Queue *signalQueue = newQueue(deleteSignal);
	Connection *c = NULL;
	Signal *s = NULL;

	c = newConnection("click", NULL, draw);
	queuePush(connectionQueue, c);

	initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
	setbkcolor(GREEN);
	setviewport(0, 0, 640, 480, 1);
	
	setcolor(RED);
	MouseInit(mouse);

	circle(50, 50, 5);

	while(1)
	{
		NewMouse(mouse, signalQueue);
		triggerSignal(connectionQueue, signalQueue);
		
	}
}