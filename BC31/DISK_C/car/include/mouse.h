#ifndef __Mouse__
#define __Mouse__

#include "queue.h"

typedef struct
{
	int mouseX;
	int mouseY;
	int mouseS;
	int mouseClick;
} MouseState;

//初始化
void MouseInit();

//画鼠标
void MouseShape(int x, int y);

//得到当前鼠标位置
void RegsRead(MouseState *mouse); 

//更新鼠标状态
void NewMouse(Queue *signalQueue);

//检测鼠标点击
void MouseClick(MouseState *mouse);

#endif