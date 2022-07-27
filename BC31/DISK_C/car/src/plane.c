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

//����ƽ����Ϣ��ʼ�� 
planeInfo PlaneInfoInit(float *originA, float *originB, float *originC, float *originD, float *finalA, float *finalB, float *finalC, float *finalD)
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

//�������ƽ��ϵ������ 
void CalPlaneCoffiecient(planeInfo *planeInformation)
{
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;
	
	x1 = planeInformation->originDotID[0][0]; y1 = planeInformation->originDotID[0][1]; z1 = planeInformation->originDotID[0][2];
	x2 = planeInformation->originDotID[1][0]; y2 = planeInformation->originDotID[1][1]; z2 = planeInformation->originDotID[1][2];
	x3 = planeInformation->originDotID[2][0]; y3 = planeInformation->originDotID[2][1]; z3 = planeInformation->originDotID[2][2];
	planeInformation->coffiecient[0] = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
	planeInformation->coffiecient[1] = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
	planeInformation->coffiecient[2] = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
}

//��ƽ�� 
void DrawPlane(planeInfo *plane, coordinateSystem *coordinate, int color, int lcolor)
{
	putParallelogram(plane->finalDotID[0][0] * coordinate->maganification + 320, plane->finalDotID[0][1] * coordinate->maganification + 240, plane->finalDotID[1][0] * coordinate->maganification + 320, plane->finalDotID[1][1] * coordinate->maganification + 240, plane->finalDotID[2][0] * coordinate->maganification + 320, plane->finalDotID[2][1] * coordinate->maganification + 240, plane->finalDotID[3][0] * coordinate->maganification + 320, plane->finalDotID[3][1] * coordinate->maganification + 240, color);
	lineDDA(plane->finalDotID[0][0] * coordinate->maganification + 320, plane->finalDotID[0][1] * coordinate->maganification + 240, plane->finalDotID[1][0] * coordinate->maganification + 320, plane->finalDotID[1][1] * coordinate->maganification + 240, lcolor);
	lineDDA(plane->finalDotID[1][0] * coordinate->maganification + 320, plane->finalDotID[1][1] * coordinate->maganification + 240, plane->finalDotID[2][0] * coordinate->maganification + 320, plane->finalDotID[2][1] * coordinate->maganification + 240, lcolor);
	lineDDA(plane->finalDotID[2][0] * coordinate->maganification + 320, plane->finalDotID[2][1] * coordinate->maganification + 240, plane->finalDotID[3][0] * coordinate->maganification + 320, plane->finalDotID[3][1] * coordinate->maganification + 240, lcolor);
	lineDDA(plane->finalDotID[3][0] * coordinate->maganification + 320, plane->finalDotID[3][1] * coordinate->maganification + 240, plane->finalDotID[0][0] * coordinate->maganification + 320, plane->finalDotID[0][1] * coordinate->maganification + 240, lcolor);
}
