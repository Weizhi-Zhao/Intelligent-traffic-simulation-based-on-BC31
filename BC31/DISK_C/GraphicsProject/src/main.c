#include "2graph~1.h"
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <alloc.h>

void main()
{
	int driver = VGA;
	int mode = VGAHI;
	double i;
	long j;
	double k;

	initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
	setbkcolor(BLACK);
	setviewport(0, 0, 639, 479, 1);

	printf("lalala");
	for(i = 0; i < 16; i++)
	{
		//putHorizontalLine(10, i * 10, 200, i);
		lineDDA(i * 30, 480 - i * 30, 600, 80, i);
	}
	//putParallelogram(250, 240, 370, 240, 320, 310, 320, 170, 9);
	showFrameBuffer();
	getch();

	for(j = 0; j < 20; j++)
	{
		for(i = 10; i <= 100; i++)
		{
			clearFrameBuffer();
			putParallelogram(320, 360 - i,320 - i, 240,  320 + i, 240, 320, 120 + i, 14);
			showFrameBuffer();
		}
		for(i = 100; i >= 10; i--)
		{
			clearFrameBuffer();
			putParallelogram(320, 360 - i,320 - i, 240,  320 + i, 240, 320, 120 + i, 14);
			showFrameBuffer();
		}
	}

	getch();
	for(i = 0; i < 361; i+=10)
	{
		for(k = 1; k < 20; k++)
		{
			putBar(sin((i + k * 72) / 180 * 3.14) * 200 + 320, cos((i + k * 72) / 180 * 3.14) * 200 + 240, 20, 20, GREEN);
		`	putParallelogram(320, 360 - i,320 - i, 240,  320 + i, 240, 320, 120 + i, 14);
		}
		putBar(sin((i) / 180 * 3.14) * 200 + 320, cos((i) / 180 * 3.14) * 200 + 240, 20, 20, RED);
		//for(j = 0; j < 38400l * 4; j++)k = 0;
		//putBar_t(buffer, sin(i / 180 * 3.14) * 100 + 320, cos(i / 180 * 3.14) * 100 + 240, 20, 20, RED);
		showFrameBuffer();
		//delay(18);
		clearFrameBuffer();
	}
	getch();
}