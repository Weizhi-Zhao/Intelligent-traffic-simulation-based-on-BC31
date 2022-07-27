#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int driver = VGA;
int mode = VGAHI;

void* buffer;
unsigned long size;
int i;
int j;
int step = 1;
int *p;

FILE *fp;

void draw_bitmap();
void draw_delay();

void main()
{
	unsigned size;
	initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
	setbkcolor(GREEN);
	setviewport(0, 0, 639, 479, 1);
	draw_delay();
	//draw_bitmap();
}

void draw_delay()
{
	for(j = 0; j < 5; j++)
	{
		for(i = 0; i < 360; i+=step)
		{
			setcolor(WHITE);
			setfillstyle(SOLID_FILL, WHITE);
			fillellipse(320 + 100 * cos(i / 180.0 * 3.14), 240 + 100 * sin(i / 180.0 * 3.14), 20, 20);
			delay(17);
			setcolor(BLACK);
			setfillstyle(SOLID_FILL, BLACK);
			fillellipse(320 + 100 * cos(i / 180.0 * 3.14), 240 + 100 * sin(i / 180.0 * 3.14), 20, 20);
		}
		getch();
	}
}

void draw_bitmap()
{
	size = imagesize(200, 120, 440, 360);
	printf("%d\n", size);

	fp = fopen("ilovebc31.dat", "wb+");
	buffer = malloc(size);

	for(i = 0; i < 360; i+=step)
	{
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		fillellipse(320 + 100 * cos(i / 180.0 * 3.14), 240 + 100 * sin(i / 180.0 * 3.14), 20, 20);
		getimage(200, 120, 440, 360, buffer);
		fwrite(buffer, size, 1, fp);
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, BLACK);
		fillellipse(320 + 100 * cos(i / 180.0 * 3.14), 240 + 100 * sin(i / 180.0 * 3.14), 20, 20);
	}
	fwrite(buffer, size, 10, fp);
	fclose(fp);

	fp = fopen("ilovebc31.dat", "rb");
	for(j = 0; j < 10; j++)
	{
		for(i = 0; i < 360; i+=step)
		{
			fread(buffer, size, 1, fp);
			fseek(fp, size, SEEK_CUR);
			putimage(200, 120, buffer, COPY_PUT);
			delay(17);
		}
		rewind(fp);
		printf("ilovebc31.dat\n");
		getch();
	}

	free(buffer);
	fclose(fp);
	getch();
}