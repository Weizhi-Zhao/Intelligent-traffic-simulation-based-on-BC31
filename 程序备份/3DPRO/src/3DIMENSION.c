#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <bios.h>
#include "3dimen.h"
#include "connection.h"
#include "queue.h"
#include "zwzSignal.h"
#include "2graphics.h"
#include "mouse.h"
#include "keyboard.h"
#include "directedLine.h"

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
    int i;
	double dis = 0;
	int EXIT = 0; 
    int gdriver = VGA;
    int gmode = VGAHI;
	Point pos;
    Queue *connectionQueue = newQueue(deleteConnection);
    Queue *signalQueue = newQueue(deleteSignal);
	coordinateSystem coordinate;
	bodyInfo body1;
	bodyInfo body2;
    Connection *c = newConnection("keyboard", &coordinate, ChangeView);
	DirectedLine *line1 = newDirectedLine(3, 0, 10, 0);
	DirectedLine *line2 = newDirectedLine(10, 0, 3, 0);

	ConnectDLine(line1, line2);

    queuePush(connectionQueue, c);
    c = newConnection("keyboard", &coordinate, FocusChange);
    queuePush(connectionQueue, c);
    c = newConnection("keyboard", &coordinate, ZoomInAndOut);
    queuePush(connectionQueue, c);
    c = newConnection("mouse", &EXIT, Close);
    queuePush(connectionQueue, c);

    BodyInfoInit(&body1, 2, 2, 2, 0, 0, 0, 1, 0, 0);
    BodyInfoInit(&body2, 1, 1, 1, 3, 0, 0, 1, 0, 0);
   
    CoordinateInit(&coordinate);
    VectorSet(coordinate.eye, 10, 10, 10, 1);
    initgraph(&gdriver, &gmode, "c:\\borlandc\\bgi");
    cleardevice();
    setbkcolor(BLACK);
    setviewport(0, 0, 639, 479, 1);
    
    CalUVN(&coordinate);
    
	GiveUnit(&coordinate);
	
    setfillstyle(SOLID_FILL, WHITE);
    while(1)
    {
		dis += 0.02;
		if(dis <= line1->lenth)
		{
			pos = posToPoint(line1, dis);
		}
		else if(dis - line1->lenth <= line2->lenth)
		{
			pos = posToPoint(line2, dis - line1->lenth);
		}
		else
		{
			dis = 0;
		}
		BodyInfoInit(&body2, 1, 1, 1, pos.x, pos.y, 0, 1, 0, 0);
    	clearFrameBuffer();
		for(i = 0;i < 8;i++)
		{
			VectorSet(body1.finalCoordinate[i], 0, 0, 0, 0);
			
	    	CoordinateChange(body1.originCoordinate[i], coordinate.change, body1.finalCoordinate[i]);
			VectorSet(body2.finalCoordinate[i], 0, 0, 0, 0);
	    	CoordinateChange(body2.originCoordinate[i], coordinate.change, body2.finalCoordinate[i]);
		}

		if(body1.finalCoordinate[0][2] > body2.finalCoordinate[0][2])
		{
			ConnectDots(&body2, &coordinate);
			ConnectDots(&body1, &coordinate);
		}
		else
		{
			ConnectDots(&body1, &coordinate);
	    	ConnectDots(&body2, &coordinate);
		}
	    detectKeyBoard(signalQueue);
	    NewMouse(signalQueue);
	    showFrameBuffer();
		
		if(EXIT == 1)
		{
			deleteQueue(signalQueue);
			deleteQueue(connectionQueue);
			return;
		}
		triggerSignal(connectionQueue, signalQueue);
	}
}

void CalUVN(coordinateSystem *coordinate)
{
	
	int i;
	for(i = 0;i < 3;i++)
    {
    	coordinate->nAxis[i] = -(coordinate->eye[i] - coordinate->focusPoint[i]) / sqrt(pow(coordinate->eye[0] - coordinate->focusPoint[0], 2) + pow(coordinate->eye[1] - coordinate->focusPoint[1], 2) + pow(coordinate->eye[2] - coordinate->focusPoint[2], 2));
	}

	coordinate->uAxis[0] = coordinate->V[1] * coordinate->nAxis[2] - coordinate->V[2] * coordinate->nAxis[1];
	coordinate->uAxis[1] = coordinate->V[2] * coordinate->nAxis[0] - coordinate->V[0] * coordinate->nAxis[2];
	coordinate->uAxis[2] = coordinate->V[0] * coordinate->nAxis[1] - coordinate->V[1] * coordinate->nAxis[0];
	coordinate->u0 = coordinate->uAxis[0], coordinate->u1 = coordinate->uAxis[1], coordinate->u2 = coordinate->uAxis[2];
	for(i = 0;i < 3;i++)
	{
		coordinate->uAxis[i] = coordinate->uAxis[i] / sqrt(coordinate->u0 * coordinate->u0 + coordinate->u1 * coordinate->u1 + coordinate->u2 * coordinate->u2);
	}
	
	coordinate->vAxis[0] = coordinate->nAxis[1] * coordinate->uAxis[2] - coordinate->nAxis[2] * coordinate->uAxis[1];
	coordinate->vAxis[1] = coordinate->nAxis[2] * coordinate->uAxis[0] - coordinate->nAxis[0] * coordinate->uAxis[2];
	coordinate->vAxis[2] = coordinate->nAxis[0] * coordinate->uAxis[1] - coordinate->nAxis[1] * coordinate->uAxis[0];
} 

void GiveUnit(coordinateSystem *coordinate)
{
	int i; 
	
	for(i = 0;i < 3;i++)
	{
		coordinate->change[0][i] = coordinate->uAxis[i];
	}
	for(i = 0;i < 3;i++)
	{
		coordinate->change[1][i] = coordinate->vAxis[i];
	}
	for(i = 0;i < 3;i++)
	{
		coordinate->change[2][i] = coordinate->nAxis[i];
	}
	
    coordinate->change[0][3] = - DotMultiply(coordinate->uAxis, coordinate->eye);
    coordinate->change[1][3] = - DotMultiply(coordinate->vAxis, coordinate->eye);
    coordinate->change[2][3] = - DotMultiply(coordinate->nAxis, coordinate->eye);
}

void CoordinateInit(coordinateSystem *coordinate)
{
	int i;
	
	VectorSet(coordinate->V, 0, 0, 1, 1);
	VectorSet(coordinate->uAxis, 0, 0, 0, 1);
	VectorSet(coordinate->nAxis, 0, 0, 0, 1);
	VectorSet(coordinate->vAxis, 0, 0, 0, 1);
	coordinate->maganification = 50; 
	for(i = 0;i < 3;i++)
	{
		coordinate->focusPoint[i] = 0;
	}
	ChangeMatrixInit(coordinate->change);
}

void CoordinateChange(double origin[], double change[][4], double final[])
{
    int i, j;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            final[i] += change[i][j] * origin[j];
        }
    }
}

double DotMultiply(double a[], double b[])
{
    int i;
    double result = 0;
    for(i = 0; i < 3; i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

void VectorSet(double target[], double a, double b, double c, double d)
{
	target[0] = a;
	target[1] = b;
	target[2] = c;
	target[3] = d;
}

void ChangeMatrixInit(double change[][4])
{
	int i, j;
	
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 4;j++)
		{
			change[i][j] = 0;
		}
	}
	change[3][3] = 1;
}

void ConnectDots(bodyInfo *body, coordinateSystem *coordinate)
{	
	int i;
	double temp[3];
	
	for(i = 0;i < 3;i++)
	{
		temp[i] = coordinate->eye[i] - coordinate->focusPoint[i];
	}
	for(i = 0;i < 6;i++)
	{
		CalPlaneCoffiecient(&(body->planeInformation[i]));
		if(DotMultiply(body->planeInformation[i].coffiecient, temp) < 0)
		{
			DrawPlane(&(body->planeInformation[i]), coordinate);
		}
	}
}

void ChangeView(void *coordinate, void *key)
{ 
	int *letter = key;
	static double angle = 120;
	coordinateSystem *c = coordinate;
	double distance = sqrt(pow(c->eye[0] - c->focusPoint[0], 2) + pow(c->eye[1] - c->focusPoint[1], 2));
	
	if(keyToLetter(*letter) == 's')
	{
		c->eye[2] += 0.1;
	}
	else if(keyToLetter(*letter) == 'w')
	{
		c->eye[2] -= 0.1;
	}
	else if(keyToLetter(*letter) == 'a')
	{
		angle -= 10.0 / 360;
	}
	else if(keyToLetter(*letter) == 'd')
	{
		angle += 10.0 / 360;
	}
	c->eye[0] = cos(angle) * distance + c->focusPoint[0];
	c->eye[1] = sin(angle) * distance + c->focusPoint[1];
	CalUVN(coordinate);
	GiveUnit(coordinate);
}

planeInfo PlaneInfoInit(double *originA, double *originB, double *originC, double *originD, double *finalA, double *finalB, double *finalC, double *finalD)
{
	planeInfo planeInformation;
	
	planeInformation.originDotID[0] = originA;
	planeInformation.originDotID[1] = originB;
	planeInformation.originDotID[2] = originC;
	planeInformation.originDotID[3] = originD;
	
	planeInformation.finalDotID[0] = finalA;
	planeInformation.finalDotID[1] = finalB;
	planeInformation.finalDotID[2] = finalC;
	planeInformation.finalDotID[3] = finalD;
	CalPlaneCoffiecient(&planeInformation);
	
	return planeInformation;
}

void CalPlaneCoffiecient(planeInfo *planeInformation)
{
	double x1, y1, z1;
	double x2, y2, z2;
	double x3, y3, z3;
	
	x1 = planeInformation->originDotID[0][0]; y1 = planeInformation->originDotID[0][1]; z1 = planeInformation->originDotID[0][2];
	x2 = planeInformation->originDotID[1][0]; y2 = planeInformation->originDotID[1][1]; z2 = planeInformation->originDotID[1][2];
	x3 = planeInformation->originDotID[2][0]; y3 = planeInformation->originDotID[2][1]; z3 = planeInformation->originDotID[2][2];
	planeInformation->coffiecient[0] = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
	planeInformation->coffiecient[1] = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
	planeInformation->coffiecient[2] = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
}

void BodyInfoInit(bodyInfo *body, double length, double width, double height, double cenX, double cenY, double cenZ, double vecX, double vecY, double vecZ)
{
	int i;
	
	body->centrePosition[0] = cenX, body->centrePosition[1] = cenY, body->centrePosition[2] = cenZ;
	body->length = length, body->width = width, body->height = height;
	for(i = 0;i < 8;i++)
	{
		body->originCoordinate[i][3] = 1;
	}
	body->originCoordinate[0][0] = cenX - length / 2; body->originCoordinate[0][1] = cenY - width / 2; body->originCoordinate[0][2] = cenZ - height / 2;
	body->originCoordinate[1][0] = cenX - length / 2; body->originCoordinate[1][1] = cenY + width / 2; body->originCoordinate[1][2] = cenZ - height / 2;
	body->originCoordinate[2][0] = cenX + length / 2; body->originCoordinate[2][1] = cenY + width / 2; body->originCoordinate[2][2] = cenZ - height / 2;
	body->originCoordinate[3][0] = cenX + length / 2; body->originCoordinate[3][1] = cenY - width / 2; body->originCoordinate[3][2] = cenZ - height / 2;
	body->originCoordinate[4][0] = cenX - length / 2; body->originCoordinate[4][1] = cenY - width / 2; body->originCoordinate[4][2] = cenZ + height / 2;
	body->originCoordinate[5][0] = cenX - length / 2; body->originCoordinate[5][1] = cenY + width / 2; body->originCoordinate[5][2] = cenZ + height / 2;
	body->originCoordinate[6][0] = cenX + length / 2; body->originCoordinate[6][1] = cenY + width / 2; body->originCoordinate[6][2] = cenZ + height / 2;
	body->originCoordinate[7][0] = cenX + length / 2; body->originCoordinate[7][1] = cenY - width / 2; body->originCoordinate[7][2] = cenZ + height / 2;
	
	body->vector[0] = vecX; body->vector[1] = vecY; body->vector[2] = vecZ;
	body->planeInformation[0] = PlaneInfoInit(body->originCoordinate[0], body->originCoordinate[1], body->originCoordinate[2], body->originCoordinate[3], body->finalCoordinate[0], body->finalCoordinate[1], body->finalCoordinate[2], body->finalCoordinate[3]);
	body->planeInformation[1] = PlaneInfoInit(body->originCoordinate[7], body->originCoordinate[6], body->originCoordinate[5], body->originCoordinate[4], body->finalCoordinate[7], body->finalCoordinate[6], body->finalCoordinate[5], body->finalCoordinate[4]);
	body->planeInformation[2] = PlaneInfoInit(body->originCoordinate[5], body->originCoordinate[6], body->originCoordinate[2], body->originCoordinate[1], body->finalCoordinate[5], body->finalCoordinate[6], body->finalCoordinate[2], body->finalCoordinate[1]);
	body->planeInformation[3] = PlaneInfoInit(body->originCoordinate[6], body->originCoordinate[7], body->originCoordinate[3], body->originCoordinate[2], body->finalCoordinate[6], body->finalCoordinate[7], body->finalCoordinate[3], body->finalCoordinate[2]);
	body->planeInformation[4] = PlaneInfoInit(body->originCoordinate[7], body->originCoordinate[4], body->originCoordinate[0], body->originCoordinate[3], body->finalCoordinate[7], body->finalCoordinate[4], body->finalCoordinate[0], body->finalCoordinate[3]);
	body->planeInformation[5] = PlaneInfoInit(body->originCoordinate[1], body->originCoordinate[0], body->originCoordinate[4], body->originCoordinate[5], body->finalCoordinate[1], body->finalCoordinate[0], body->finalCoordinate[4], body->finalCoordinate[5]);
}
 
void DrawPlane(planeInfo *plane, coordinateSystem *coordinate)
{
	putParallelogram(plane->finalDotID[0][0] * coordinate->maganification + 320, plane->finalDotID[0][1] * coordinate->maganification + 240, plane->finalDotID[1][0] * coordinate->maganification + 320, plane->finalDotID[1][1] * coordinate->maganification + 240, plane->finalDotID[2][0] * coordinate->maganification + 320, plane->finalDotID[2][1] * coordinate->maganification + 240, plane->finalDotID[3][0] * coordinate->maganification + 320, plane->finalDotID[3][1] * coordinate->maganification + 240, 3);
	lineDDA(plane->finalDotID[0][0] * coordinate->maganification + 320, plane->finalDotID[0][1] * coordinate->maganification + 240, plane->finalDotID[1][0] * coordinate->maganification + 320, plane->finalDotID[1][1] * coordinate->maganification + 240, 15);
	lineDDA(plane->finalDotID[1][0] * coordinate->maganification + 320, plane->finalDotID[1][1] * coordinate->maganification + 240, plane->finalDotID[2][0] * coordinate->maganification + 320, plane->finalDotID[2][1] * coordinate->maganification + 240, 15);
	lineDDA(plane->finalDotID[2][0] * coordinate->maganification + 320, plane->finalDotID[2][1] * coordinate->maganification + 240, plane->finalDotID[3][0] * coordinate->maganification + 320, plane->finalDotID[3][1] * coordinate->maganification + 240, 15);
	lineDDA(plane->finalDotID[3][0] * coordinate->maganification + 320, plane->finalDotID[3][1] * coordinate->maganification + 240, plane->finalDotID[0][0] * coordinate->maganification + 320, plane->finalDotID[0][1] * coordinate->maganification + 240, 15);
}

void FocusChange(void *coordinate, void *key)
{
	int *letter = key;
	coordinateSystem *c = coordinate;
	
	if(*letter == 0x4b00)//�����? 
	{
		c->eye[0]  += 0.1;
		c->focusPoint[0] += 0.1;
	}
	else if(*letter == 0x4d00)//�ҷ����?
	{
		c->eye[0]  -= 0.1;
		c->focusPoint[0] -= 0.1;
	} 
	else if(*letter == 0x4800)//�Ϸ����?
	{
		c->eye[1]  += 0.1;
		c->focusPoint[1] += 0.1;
	}
	else if(*letter == 0x5000)//�·����?
	{
		c->eye[1]  -= 0.1;
		c->focusPoint[1] -= 0.1;
	}
	CalUVN(coordinate);
	GiveUnit(coordinate);
}

void ZoomInAndOut(void *coordinate, void *key)
{
	int *letter = key;
	coordinateSystem *c = coordinate;
	
	if(c->maganification >= 0 && c->maganification <= 80)
	{
		if(keyToLetter(*letter) == 'q')//��С 
		{
			if(c->maganification >= 1)
			{
				c->maganification -= 1;
			}
		}
		else if(keyToLetter(*letter) == 'e')//�Ŵ� 
		{
			if(c->maganification <= 79)
			{
				c->maganification += 1;
			}
		}
	}
	else
	{
		return;
	}
}