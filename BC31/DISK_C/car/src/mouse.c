#include "Mouse.h"
#include <conio.h>
#include <graphics.h>
#include "2graphics.h"
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zwzSignal.h"
#include "queue.h"

void MouseInit()
{
	MouseState mousel;
	union REGS regs;
	int retCode;
	int xMin = 0, xMax = 639, yMin = 0, yMax = 479;

	regs.x.ax = 0;
	int86(0x33, &regs, &regs);

	retCode = regs.x.ax;

	if(retCode == 0)
	{
		printf("Mouse or Mouse Driver Absent. Please Install!\n");
		return;
    }
	else
	{
		//设置鼠标运动范围 
		regs.x.ax = 0x07;
		regs.x.cx = xMin;
		regs.x.dx = xMax;
		int86(0x33, &regs, &regs);
		regs.x.ax = 0x08;
		regs.x.cx = yMin;
		regs.x.dx = yMax;
		int86(0x33, &regs, &regs);
    }
}

void RegsRead(MouseState *mouse)
{
	union REGS regs;

	regs.x.ax = 0x03;
	int86(0x33, &regs, &regs);
	mouse->mouseX = regs.x.cx;
	mouse->mouseY = regs.x.dx;
	MouseClick(mouse);
}

void NewMouse(Queue *signalQueue)
{
	MouseState newMouse, *mouseParameter;
	Signal *signal;

	RegsRead(&newMouse);
	mouseParameter = (MouseState*)malloc(sizeof(MouseState));
	*mouseParameter = newMouse;

	signal = (Signal*)newSignal("mouse", mouseParameter, free);
	queuePush(signalQueue, signal);

	//绘制新鼠标 
	MouseShape(newMouse.mouseX, newMouse.mouseY);
}

void MouseShape(int x, int y)
{
	putTriangle(x + 0, y + 0, x + 9, y + 9, x + 4, y + 9, 15);
	putTriangle(x + 0, y + 1, x + 3, y + 9, x + 0, y + 13, 15);
	putBar(x + 4, y + 10, 3, 2, 15);
	putBar(x + 5, y + 12, 3, 2, 15);
	putBar(x + 6, y + 14, 3, 2, 15);

	lineDDA(x - 1, y - 2, x + -1, y + 14, 0);
	lineDDA(x - 1, y + 14, x + 3, y + 10, 0);
	lineDDA(x + 3, y + 10, x + 6, y + 16, 0);
	lineDDA(x + 7, y + 16, x + 8, y + 16, 0);
	lineDDA(x + 9, y + 15, x + 7, y + 10, 0);
	lineDDA(x + 8, y + 10, x + 11, y + 10, 0);
	lineDDA(x + 10, y + 9, x + 0, y - 1, 0);
}

void MouseClick(MouseState *mouse)
{
    union REGS regs;

	regs.x.ax = 0x03;
	int86(0x33, &regs, &regs);

	//检测点击 
	if(regs.x.bx & 1)
	{
		mouse->mouseClick = 1;
	}
	else
	{
		mouse->mouseClick = 0;
	}
}