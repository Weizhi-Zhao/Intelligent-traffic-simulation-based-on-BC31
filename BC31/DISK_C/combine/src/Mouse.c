#include "Mouse.h"
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zwzSignal.h"
#include "queue.h"

void MouseInit(MouseState *mouse)
{
	union REGS regs;
	int retCode;
	int xMin, xMax, yMin, yMax, xRealMax = 639, yRealMax = 479;
	
	xMin = 0;
	xMax = xRealMax;
	yMin = 0;
	yMax = yRealMax;
	regs.x.ax = 0;
	int86(0x33, &regs, &regs);
	retCode = regs.x.ax;
	if(retCode == 0)
	{
		printf("Mouse or Mouse Driver Absent. Please Install!\n");
    }
	else
	{
		regs.x.ax = 0x07;
		regs.x.cx = xMin;
		regs.x.dx = xMax;
		int86(0x33, &regs, &regs);
		regs.x.ax = 0x08;
		regs.x.cx = yMin;
		regs.x.dx = yMax;
		int86(0x33, &regs, &regs);
    }//设置鼠标运动范围 
	mouse->mouseS = 0;//鼠标类型 
	mouse->mouseX = 320, mouse->mouseY = 240;
	SaveBackImage(mouse);//保存初始位置背景 
	MouseShape(mouse->mouseX, mouse->mouseY, mouse->mouseS);
	//mouse->mouseExist = 1;
}
void RegsRead(MouseState *mouse)
{
	union REGS regs;
	regs.x.ax = 0x03;
	int86(0x33, &regs, &regs);
	mouse->mouseX = regs.x.cx;
	mouse->mouseY = regs.x.dx;
	//mouse->mouseS = regs.x.bx;
	mouse->mouseS = 0;
	MouseClick(mouse);
}

void NewMouse(MouseState *mouse, Queue *signalQueue)
{
	MouseState *newMouse = (MouseState*)malloc(sizeof(MouseState));
	MouseState *mouseParameter;
	Signal *signal;
	int originMouseX = mouse->mouseX, originMouseY = mouse->mouseY, originMouseS = mouse->mouseS;
	RegsRead(newMouse);
	mouse->mouseX = newMouse->mouseX;
	mouse->mouseY = newMouse->mouseY;
	mouse->mouseS = newMouse->mouseS;
	mouse->mouseClick = newMouse->mouseClick;
	if(mouse->mouseClick == 1)
	{
		mouseParameter = (MouseState*)malloc(sizeof(MouseState));
		*mouseParameter = *mouse;
		signal = newSignal("click", mouseParameter, free);
		queuePush(signalQueue, signal);
	}
	if(newMouse->mouseX == originMouseX && newMouse->mouseY == originMouseY && newMouse->mouseS == originMouseS)
	{
		DrawMouse(mouse);//绘制新鼠标 
   		free(newMouse);
		return;
	}//比较新旧状态 
	ClearMouse(originMouseX, originMouseY, mouse);//清除原鼠标 
	SaveBackImage(mouse);//保存新状态背景 
	DrawMouse(mouse);//绘制新鼠标 
	free(newMouse);
    
}
void ClearMouse(int originMouseX, int originMouseY, MouseState *mouse)
{
	putimage(max(originMouseX - 1, 0),max(originMouseY - 2, 0), mouse->buffer, COPY_PUT);//用原背景覆盖 
	free(mouse->buffer);
}
void SaveBackImage(MouseState *mouse)
{
	int size = imagesize(max(mouse->mouseX - 1, 0), max(mouse->mouseY - 2, 0), min(mouse->mouseX + 11, 639), min(mouse->mouseY + 17, 479));
	
	if((mouse->buffer = malloc(size)) != NULL)
	    getimage(max(mouse->mouseX - 1, 0), max(mouse->mouseY - 2, 0), min(mouse->mouseX + 11, 639), min(mouse->mouseY + 17, 479), mouse->buffer);
	else
	    printf("Error!\n");   
}
void MouseShape(int mouseX, int mouseY, int mouseS)
{
	int x = mouseX, y = mouseY;
	switch(mouseS)
	{
	case 1://手势鼠标
		setcolor(WHITE);
		setlinestyle(0,0,1);
		line(x-1,y+9,x-1,y+8);
		line(x,y+7,x,y+11);
		line(x+1,y+6,x+1,y+13);
		line(x+2,y+8,x+2,y+14);
		line(x+3,y-1,x+3,y+15);
		arc(x+4,y-1,0,180,1);
		line(x+4,y-2,x+4,y+15);
		line(x+5,y-1,x+5,y+16);
		arc(x+6,y+3,0,180,1);
		line(x+6,y+2,x+6,y+16);
		line(x+7,y+3,x+7,y+17);
		arc(x+8,y+5,0,180,1);
		line(x+8,y+4,x+8,y+17);
		line(x+9,y+5,x+9,y+16);
		arc(x+10,y+7,0,180,1);
		line(x+10,y+6,x+10,y+16);
		line(x+11,y+7,x+11,y+13);

		setcolor(DARKGRAY);
		line(x-1,y+9,x-1,y+8);
		line(x-1,y+8,x+1,y+6);
		line(x+1,y+6,x+3,y+10);
		line(x+3,y+10,x+3,y-1);
		arc(x+4,y-1,0,180,1);
		line(x+5,y-1,x+5,y+5);
		arc(x+6,y+3,0,180,1);
		line(x+7,y+3,x+7,y+7);
		arc(x+8,y+5,0,180,1);
		line(x+9,y+5,x+9,y+9);
		arc(x+10,y+7,0,180,1);
		line(x+11,y+7,x+11,y+13);
		arc(x+7,y+13,-90,0,4);
		line(x+7,y+17,x+3,y+15);
		line(x+3,y+15,x+1,y+13);
		line(x+1,y+13,x-1,y+9);
		break;
	case 2://光标
		setcolor(DARKGRAY);
		setlinestyle(0,0,1);
		line(x+1,y-1,x+9,y-1);
		line(x+1,y+15,x+9,y+15);
		line(x+5,y-1,x+5,y+15);
		break;
	case 3://十字
		setcolor(WHITE);
		setlinestyle(0,0,1);
		line(x-1,y+7,x+11,y+7);
		line(x+5,y-1,x+5,y+15);
		break;
	default://默认鼠标
		setlinestyle(0,0,1);
		setcolor(WHITE);
		line(x,y,x,y+13);
		line(x+1,y+1,x+1,y+12);
		line(x+2,y+2,x+2,y+11);
		line(x+3,y+3,x+3,y+10);
		line(x+4,y+4,x+4,y+12);
		line(x+5,y+5,x+5,y+9);
		line(x+5,y+11,x+5,y+14);
		line(x+6,y+6,x+6,y+9);
		line(x+6,y+13,x+6,y+15);
		line(x+7,y+7,x+7,y+9);
		line(x+8,y+8,x+8,y+9);
		line(x+9,y+9,x+9,y+9);
		setcolor(DARKGRAY);
		line(x-1,y-1,x-1,y+14);
		line(x-1,y+14,x+3,y+11);
		line(x+3,y+11,x+3,y+12);
		line(x+3,y+12,x+4,y+13);
		line(x+4,y+13,x+4,y+14);
		line(x+4,y+14,x+7,y+17);
		line(x+7,y+17,x+7,y+13);
		line(x+7,y+13,x+6,y+12);
		line(x+6,y+12,x+6,y+11);
		line(x+6,y+11,x+5,y+10);
		line(x+5,y+10,x+11,y+10);
		line(x+11,y+10,x-1,y-2);
		break;
	}
}
void DrawMouse(MouseState *mouse)
{
//	if(mouse->mouseExist == 0)
//	{
//		setwritemode(COPY_PUT);
//	    MouseShape(mouse->mouseX, mouse->mouseY, mouse->mouseS);
//		mouse->mouseExist = 1;
//	}
	MouseShape(mouse->mouseX, mouse->mouseY, mouse->mouseS);
}
void MouseClick(MouseState *mouse)
{
    union REGS regs;
	regs.x.ax = 0x03;
	int86(0x33, &regs, &regs);
	if(regs.x.bx & 1)
	{
		mouse->mouseClick = 1;
	}//检测点击 
	else
	{
		mouse->mouseClick = 0;
	}
}