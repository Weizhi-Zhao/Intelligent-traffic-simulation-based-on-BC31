#include "2graph~1.h"
#include <string.h>
#include <dos.h>
#include <math.h>

void putPixel(long x, long y, int color)
{
	//计算该像素点在数组中的位置
    long pos = y * 640l + x;
    int i;
    //一个char能存8个pixel
    char pixel8;
    
    if(x < 0l || x > 639l || y < 0l || y > 479l)
	{
		return;
	}

	//先取出包含要修改像素在内的8个像素
	pixel8 = a1[pos / 8];
	//如果颜色的第一位为1
	if((color & (1 << (3 - 0))) != 0)
	{
		//将该像素设为1
		pixel8 = pixel8 | (1 << (7 - (pos % 8)));
	}
	else
	{
		//否则将该像素设为0
		pixel8 = pixel8 & (~(1 << (7 - (pos % 8))));
	}
	//将该像素放回a1数组
	a1[pos / 8] = pixel8;

	//同理，修改a2、a3、a4数组
	pixel8 = a2[pos / 8];
	if((color & (1 << (3 - 1))) != 0)
	{
		pixel8 = pixel8 | (1 << (7 - (pos % 8)));
	}
	else
	{
		pixel8 = pixel8 & (~(1 << (7 - (pos % 8))));
	}
	a2[pos / 8] = pixel8;

	pixel8 = a3[pos / 8];
	if((color & (1 << (3 - 2))) != 0)
	{
		pixel8 = pixel8 | (1 << (7 - (pos % 8)));
	}
	else
	{
		pixel8 = pixel8 & (~(1 << (7 - (pos % 8))));
	}
	a3[pos / 8] = pixel8;

	pixel8 = a4[pos / 8];
	if((color & (1 << (3 - 3))) != 0)
	{
		pixel8 = pixel8 | (1 << (7 - (pos % 8)));
	}
	else
	{
		pixel8 = pixel8 & (~(1 << (7 - (pos % 8))));
	}
	a4[pos / 8] = pixel8;
}

void putHorizontalLine(int x1, int x2, int y, int color)
{
    long start;
    long end;
    long i;
	int temp;

	//先将x1、x2按大小顺序排列
	if(x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	
	
	//若线出界，就直接退出
	if(y < 0 || y > 479 || x1 > 639 || x2 < 0)
	{
		return;
	}

	//如果最左端出界，只画界内的
	if(x1 < 0)
	{
		x1 = 0;
	}

	//如果最右端出界，只画界内的
	if(x2 > 639)
	{
		x2 = 639;
	}

	//设置该线段的起点和终点
	start = x1;
	end = x2;

	//如果线段长度小于等于16， 就直接一个个像素点画
	if(end - start + 1 <= 16)
	{
		for(i = start; i <= end; i++)
        {
            putPixel(i, y, color);
        }
		return;
	}

	//否则将start、end按照8bit等于1byte对齐，并把未对齐的像素点用putpixel填好
    if(start % 8 != 0)
    {
        start += 8 - start % 8;
        for(i = x1; i < start; i++)
        {
            putPixel(i, y, color);
        }
    }

    if(end % 8 != 7)
    {
        end -= end % 8 + 1;
        for(i = end + 1; i <= x2; i++)
        {
            putPixel(i, y, color);
        }
    }

	//如果color第一位为1
	if((color & (1 << (3 - 0))) != 0)
	{
		//用memset函数将start到end填为0xff，效率高于putpixel
		memset(a1 + (y * 640l + start) / 8, 0xff, (end - start + 1) / 8);
	}
	else
	{
		//否则用memset函数将start到end填为0x00，效率高于putpixel
		memset(a1 + (y * 640l + start) / 8, 0x00, (end - start + 1) / 8);
	}

	//a2、a3、a4数组同理
	if((color & (1 << (3 - 1))) != 0)
	{
		memset(a2 + (y * 640l + start) / 8, 0xff, (end - start + 1) / 8);
	}
	else
	{
		memset(a2 + (y * 640l + start) / 8, 0x00, (end - start + 1) / 8);
	}

	if((color & (1 << (3 - 2))) != 0)
	{
		memset(a3 + (y * 640l + start) / 8, 0xff, (end - start + 1) / 8);
	}
	else
	{
		memset(a3 + (y * 640l + start) / 8, 0x00, (end - start + 1) / 8);
	}

	if((color & (1 << (3 - 3))) != 0)
	{
		memset(a4 + (y * 640l + start) / 8, 0xff, (end - start + 1) / 8);
	}
	else
	{
		memset(a4 + (y * 640l + start) / 8, 0x00, (end - start + 1) / 8);
	}
}

void putBar(int left, int top, int width, int height, int color)
{
    int i;
    for(i = top; i <= top + height; i++)
    {
        putHorizontalLine(left, left + width - 1, i, color);
    }
}

void showFrameBuffer()
{
    //指向显存的指针
    char far *videoBuffer = (char far *)0xA0000000L;
    int i;

    //把颜色拆成4位bit，分4次写到显存里
	//好像是设置寄存器？
	outportb(0x3c4,2);
	outportb(0x3c5,1 << 0);
	//把缓冲写到显存里
	memcpy(videoBuffer, a1, 38400l);

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 1);
	//把缓冲写到显存里
	memcpy(videoBuffer, a2, 38400l);

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 2);
	//把缓冲写到显存里
	memcpy(videoBuffer, a3, 38400l);

	outportb(0x3c4,2);
	outportb(0x3c5,1 << 3);
	//把缓冲写到显存里
	memcpy(videoBuffer, a4, 38400l);
}

void lineDDA(int x0, int y0, int xEnd, int yEnd, int color)
{
	//计算x、y的变化量
    int dx = xEnd - x0;
    int dy = yEnd - y0;
    int steps, k;
    float xIncreasement, yIncreasement, x = x0, y = y0;

	//找到dx、dy的最大值
    if(abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

	//计算每步x、y的增量
    xIncreasement = (float)(dx) / (float)(steps);
    yIncreasement = (float)(dy) / (float)(steps);

	//进行step次循环，每次x、y有一定增量，用putpixel填充(x, y)点
    putPixel((int)(x + 0.5), (int)(y + 0.5), color);

    for(k = 0; k < steps; k++)
    {
        x += xIncreasement;
        y += yIncreasement;
        putPixel((int)(x + 0.5), (int)(y + 0.5), color);
    }
}

void putTriangle(int x1, int y1, int x2, int y2,  int x3, int y3, int color)
{
	float x1Increasement, y1Increasement;
	float x2Increasement, y2Increasement;
	float x3Increasement, y3Increasement;
	float xStart, xEnd;
	int i;

	//先将3个点按y方向从小到大排序
	int temp;
	if(y3 < y2)
	{
		temp = y3;
		y3 = y2;
		y2 = temp;
		temp = x3;
		x3 = x2;
		x2 = temp;
	}
	if(y2 < y1)
	{
		temp = y2;
		y2 = y1;
		y1 = temp;
		temp = x2;
		x2 = x1;
		x1 = temp;
	}
	if(y3 < y2)
	{
		temp = y3;
		y3 = y2;
		y2 = temp;
		temp = x3;
		x3 = x2;
		x2 = temp;
	}

	//如果三个点y值相同，三角形是一条平线，直接调用putHorizontalLine函数
	if(y1 == y2 && y2 == y3)
	{
		putHorizontalLine(min(min(x1, x2), x3), max(max(x1, x2), x3), y1, color);
		return;
	}

	//如果前两个点y值相同，则三角形为倒三角
	if(y1 == y2)
	{
		//计算两条斜线在同一y坐标的x值，用putHorizontalLine填充，效率较高
		x1Increasement = ((float)x3 - (float)x1) / ((float)y3 - (float)y1);
		x2Increasement = ((float)x3 - (float)x2) / ((float)y3 - (float)y2);
		xStart = x1;
		xEnd = x2;

		putHorizontalLine(xStart, xEnd, y1, color);
		for(i = y1 + 1; i <= y3; i++)
		{
			xStart += x1Increasement;
			xEnd += x2Increasement;
			putHorizontalLine((int)(xStart + 0.5), (int)(xEnd + 0.5), i, color);
		}
	}
	else if(y2 == y3)
	{
		//如果后两个点y值相同，则三角为正三角
		//计算两条斜线在同一y坐标的x值，用putHorizontalLine填充，效率较高
		x1Increasement = ((float)x3 - (float)x1) / ((float)y3 - (float)y1);
		x2Increasement = ((float)x2 - (float)x1) / ((float)y2 - (float)y1);
		xStart = x1;
		xEnd = x1;

		putHorizontalLine(xStart, xEnd, y1, color);
		for(i = y1 + 1; i <= y3; i++)
		{
			xStart += x1Increasement;
			xEnd += x2Increasement;
			putHorizontalLine((int)(xStart + 0.5), (int)(xEnd + 0.5), i, color);
		}
	}
	else
	{
		//否则3条线段均为斜线，也使用扫描线填充法
		x1Increasement = ((float)x3 - (float)x1) / ((float)y3 - (float)y1);
		x2Increasement = ((float)x2 - (float)x1) / ((float)y2 - (float)y1);
		x3Increasement = ((float)x3 - (float)x2) / ((float)y3 - (float)y2);
		xStart = x1;
		xEnd = x1;

		putHorizontalLine(xStart, xEnd, y1, color);
		for(i = y1 + 1; i <= y2; i++)
		{
			xStart += x1Increasement;
			xEnd += x2Increasement;//此处不同
			putHorizontalLine((int)(xStart + 0.5), (int)(xEnd + 0.5), i, color);
		}
		for(i = y2 + 1; i <= y3; i++)
		{
			xStart += x1Increasement;
			xEnd += x3Increasement;//此处不同
			putHorizontalLine((int)(xStart + 0.5), (int)(xEnd + 0.5), i, color);
		}
	}
}

void putParallelogram(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int color)
{
	//画四边形就是画两个三角形
	putTriangle(x1, y1, x2, y2, x3, y3, color);
	putTriangle(x3, y3, x4, y4, x1, y1, color);
}

void clearFrameBuffer()
{
	//清空缓冲，就是把缓冲全设为0x00
	memset(a1, 0x00, 38400l);
	memset(a2, 0x00, 38400l);
	memset(a3, 0x00, 38400l);
	memset(a4, 0x00, 38400l);
}
