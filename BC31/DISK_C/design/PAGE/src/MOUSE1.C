#include "includeall.h"

void MouseInit(MouseState *mouse)
{
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
		//è®¾ç½®é¼ æ ‡è¿åŠ¨èŒƒå›´ 
		regs.x.ax = 0x07;
		regs.x.cx = xMin;
		regs.x.dx = xMax;
		int86(0x33, &regs, &regs);
		regs.x.ax = 0x08;
		regs.x.cx = yMin;
		regs.x.dx = yMax;
		int86(0x33, &regs, &regs);
    }
	mouse->mouseS = 0;//Êó±êÀàĞÍ 
	mouse->mouseX = 320, mouse->mouseY = 240;
	SaveBackImage(mouse);//±£´æ³õÊ¼Î»ÖÃ±³¾° 
	MouseShape(mouse->mouseX, mouse->mouseY, mouse->mouseS);
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
void NewMouse(MouseState *mouse)
{
	RegsRead(mouse);
	SaveBackImage(mouse);//±£´æĞÂ×´Ì¬±³¾° 
	DrawMouse(mouse);//»æÖÆĞÂÊó±ê 
}
void ClearMouse(int originMouseX, int originMouseY, MouseState *mouse)
{
	putimage(Max(originMouseX - 1, 0), Max(originMouseY - 2, 0), mouse->buffer, COPY_PUT);//ÓÃÔ­±³¾°¸²¸Ç 
	free(mouse->buffer);
}
void SaveBackImage(MouseState *mouse)
{
	int size = imagesize(Max(mouse->mouseX - 1, 0), Max(mouse->mouseY - 2, 0), Min(mouse->mouseX + 11, 639), Min(mouse->mouseY + 17, 479));
	
	if((mouse->buffer = malloc(size)) != NULL)
	    getimage(Max(mouse->mouseX - 1, 0), Max(mouse->mouseY - 2, 0), Min(mouse->mouseX + 11, 639), Min(mouse->mouseY + 17, 479), mouse->buffer);
	else
	    printf("Error!\n");   
}
void MouseShape(int mouseX, int mouseY, int mouseS)
{
	int x = mouseX, y = mouseY;
	switch(mouseS)
	{
	case 1://ÊÖÊÆÊó±ê
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
	case 2://¹â±ê
		setcolor(DARKGRAY);
		setlinestyle(0,0,1);
		line(x+1,y-1,x+9,y-1);
		line(x+1,y+15,x+9,y+15);
		line(x+5,y-1,x+5,y+15);
		break;
	case 3://Ê®×Ö
		setcolor(WHITE);
		setlinestyle(0,0,1);
		line(x-1,y+7,x+11,y+7);
		line(x+5,y-1,x+5,y+15);
		break;
	default://Ä¬ÈÏÊó±ê
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
	}//¼ì²âµã»÷ 
	else
	{
		mouse->mouseClick = 0;
	}
}

int Max(int a, int b)
{
	return a > b?a : b;
}

int Min(int a, int b)
{
	return a < b?a : b;
}
