#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <bios.h>
#include <string.h>
#include "3dimen.h"
#include "connection.h"
#include "queue.h"
#include "zwzSignal.h"
#include "2graphics.h"
#include "mouse.h"
#include "keyboard.h"
#include "direct~1.h"
#include <time.h>
#include "car.h"
#include "road.h"
#include "traffi~1.h"
#include "carflow.h"

void Close(void *EXIT, void *p)
{
	MouseState *mp = p;
	if(mp->mouseClick == 1)
	{
		*(int*)EXIT = 1;
	}
}

void main()
{
	char timeCounter[4];
	DLEdge *it;
	Point pos;
    int i, j, k;
	float a = 0;
	int EXIT = 0; 
    int gdriver = VGA;
    int gmode = VGAHI;
    Queue *connectionQueue = newQueue(deleteConnection);
    Queue *signalQueue = newQueue(deleteSignal);
	coordinateSystem coordinate;
    Connection *c = newConnection("keyboard", &coordinate, ChangeView);

    queuePush(connectionQueue, c);
    c = newConnection("keyboard", &coordinate, FocusChange);
    queuePush(connectionQueue, c);
    c = newConnection("keyboard", &coordinate, ZoomInAndOut);
    queuePush(connectionQueue, c);
    c = newConnection("mouse", &EXIT, Close);
    queuePush(connectionQueue, c);

	for(i = 0; i < 12; i++)
	{
		InitBus(&car1[i]);
		
		car1[i].dis = 0;
		car1[i].nowLine = startLine[i % 7];
	}
   
    CoordinateInit(&coordinate);
	coordinate.maganification = 5;
    VectorSet(coordinate.eye, 10, 10, 10, 1);
    initgraph(&gdriver, &gmode, "c:\\borlandc\\bgi");
    cleardevice();
    setbkcolor(BLACK);
    setviewport(0, 0, 639, 479, 1);
    
    CalUVN(&coordinate);
    
	GiveUnit(&coordinate);

	DrawRoad(Road);
	InitLine();
	ConnectLine();

	srand(time(0));

	InitTrafficLight(&trafficLight[0], -5, -5, RGL, 20);
	InitTrafficLight(&trafficLight[1], -5, 55, RGL + 4, 20);
	InitTrafficLight(&trafficLight[2], 55, -5, RGL + 8, 20);
	InitTrafficLight(&trafficLight[3], 55, 55, RGL + 12, 20);

	InitCarflow(&carflow[0], lineCS[0], lineCL[0], lineCR[0], 30);
	InitCarflow(&carflow[1], lineCS[1], lineCL[1], lineCR[1], 30);
	InitCarflow(&carflow[2], lineCS[2], lineCL[2], lineCR[2], 30);
	InitCarflow(&carflow[3], lineCS[3], lineCL[3], lineCR[3], 30);

    while(1)
    {
    	clearFrameBuffer();
		
		for(i = 0; i < 15; i++)
		{
			for(j = 0; j < 8; j++)
			{
				VectorSet(Road[i].finalCoordinate[j], 0, 0, 0, 0);
				CoordinateChange(Road[i].originCoordinate[j], coordinate.change, Road[i].finalCoordinate[j]);
			}
			VectorSet(Road[i].finalCentrePosition, 0, 0, 0, 0);
			Road[i].centrePosition[3] = 1;
			CoordinateChange(Road[i].centrePosition, coordinate.change, Road[i].finalCentrePosition);
		}

		for(i = 0; i < 11; i++)
		{
			for(j = 0; j < 8; j++)
			{
				VectorSet(yellowLine[i].finalCoordinate[j], 0, 0, 0, 0);
				CoordinateChange(yellowLine[i].originCoordinate[j], coordinate.change, yellowLine[i].finalCoordinate[j]);
			}
			VectorSet(yellowLine[i].finalCentrePosition, 0, 0, 0, 0);
			yellowLine[i].centrePosition[3] = 1;
			CoordinateChange(yellowLine[i].centrePosition, coordinate.change, yellowLine[i].finalCentrePosition);
		}

		SortRoad(Road);

		for(i = 0; i < 15; i++)
		{
			ConnectDots(&Road[i], &coordinate, 14, 15);
		}

		for(i = 0; i < 11; i++)
		{
			ConnectDots(&yellowLine[i], &coordinate, 7, 7);
		}

		RunCar(car1, 12, startLine, &coordinate);

		for(i = 0; i < 12; i++)
		{
			if(car1[i].visiable)
			{
				DrawCar(&car1[i], &coordinate);
			}
		}

		for(i = 0; i < 4; i++) 
		{
			DrawTrafficLight(&trafficLight[i], &coordinate);
		}
	    detectKeyBoard(signalQueue);
	    NewMouse(signalQueue);
	    showFrameBuffer();

		settextstyle(0, 0, 0);
		outtextxy(10, 460, " ");
		for(i = 0; i < 4; i++) 
		{
			itoa(trafficLight[i].timeCounter, timeCounter, 10);
			settextstyle(0, 0, 2);
			outtextxy(trafficLight[i].light[2].finalCentrePosition[0] * coordinate.maganification + 320
			, trafficLight[i].light[2].finalCentrePosition[1] * coordinate.maganification + 210
			, timeCounter);

			ShowCarnum(&carflow[i]
			, trafficLight[i].light[2].finalCentrePosition[0] * coordinate.maganification + 320
			, trafficLight[i].light[2].finalCentrePosition[1] * coordinate.maganification + 180);
		}
		if(EXIT == 1)
		{
			deleteQueue(signalQueue);
			deleteQueue(connectionQueue);
			return;
		}
		triggerSignal(connectionQueue, signalQueue);
	}
}