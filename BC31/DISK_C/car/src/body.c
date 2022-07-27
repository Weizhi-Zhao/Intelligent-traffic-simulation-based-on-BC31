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

//������������Ϣ��ʼ�� 
void BodyInfoInit(bodyInfo *body, float length, float width, float height, float cenX, float cenY, float cenZ, float vecX, float vecY, float vecZ)
{
	int i;
	
	body->centrePosition[0] = cenX, body->centrePosition[1] = cenY, body->centrePosition[2] = cenZ;
	body->length = length, body->width = width, body->height = height;
	body->angle = 0;
	for(i = 0;i < 8;i++)
	{
		body->originCoordinate[i][3] = 1;
	}
	OriginBodyPointCal(body);
	BodyPlaneCal(body);
}

//�����ʼ������������� 
void OriginBodyPointCal(bodyInfo *body)
{
	body->originCoordinate[0][0] = body->centrePosition[0] - body->length / 2; body->originCoordinate[0][1] = body->centrePosition[1] - body->width / 2; body->originCoordinate[0][2] = body->centrePosition[2] - body->height / 2;
	body->originCoordinate[1][0] = body->centrePosition[0] - body->length / 2; body->originCoordinate[1][1] = body->centrePosition[1] + body->width / 2; body->originCoordinate[1][2] = body->centrePosition[2] - body->height / 2;
	body->originCoordinate[2][0] = body->centrePosition[0] + body->length / 2; body->originCoordinate[2][1] = body->centrePosition[1] + body->width / 2; body->originCoordinate[2][2] = body->centrePosition[2] - body->height / 2;
	body->originCoordinate[3][0] = body->centrePosition[0] + body->length / 2; body->originCoordinate[3][1] = body->centrePosition[1] - body->width / 2; body->originCoordinate[3][2] = body->centrePosition[2] - body->height / 2;
	body->originCoordinate[4][0] = body->centrePosition[0] - body->length / 2; body->originCoordinate[4][1] = body->centrePosition[1] - body->width / 2; body->originCoordinate[4][2] = body->centrePosition[2] + body->height / 2;
	body->originCoordinate[5][0] = body->centrePosition[0] - body->length / 2; body->originCoordinate[5][1] = body->centrePosition[1] + body->width / 2; body->originCoordinate[5][2] = body->centrePosition[2] + body->height / 2;
	body->originCoordinate[6][0] = body->centrePosition[0] + body->length / 2; body->originCoordinate[6][1] = body->centrePosition[1] + body->width / 2; body->originCoordinate[6][2] = body->centrePosition[2] + body->height / 2;
	body->originCoordinate[7][0] = body->centrePosition[0] + body->length / 2; body->originCoordinate[7][1] = body->centrePosition[1] - body->width / 2; body->originCoordinate[7][2] = body->centrePosition[2] + body->height / 2;
	
	body->relaCoordinate[0][0] = - body->length / 2; body->relaCoordinate[0][1] = - body->width / 2; body->relaCoordinate[0][2] = - body->height / 2;
	body->relaCoordinate[1][0] = - body->length / 2; body->relaCoordinate[1][1] = + body->width / 2; body->relaCoordinate[1][2] = - body->height / 2;
	body->relaCoordinate[2][0] = + body->length / 2; body->relaCoordinate[2][1] = + body->width / 2; body->relaCoordinate[2][2] = - body->height / 2;
	body->relaCoordinate[3][0] = + body->length / 2; body->relaCoordinate[3][1] = - body->width / 2; body->relaCoordinate[3][2] = - body->height / 2;
	body->relaCoordinate[4][0] = - body->length / 2; body->relaCoordinate[4][1] = - body->width / 2; body->relaCoordinate[4][2] = + body->height / 2;
	body->relaCoordinate[5][0] = - body->length / 2; body->relaCoordinate[5][1] = + body->width / 2; body->relaCoordinate[5][2] = + body->height / 2;
	body->relaCoordinate[6][0] = + body->length / 2; body->relaCoordinate[6][1] = + body->width / 2; body->relaCoordinate[6][2] = + body->height / 2;
	body->relaCoordinate[7][0] = + body->length / 2; body->relaCoordinate[7][1] = - body->width / 2; body->relaCoordinate[7][2] = + body->height / 2;
}

//���������������� 
void BodyPointCal(bodyInfo *body)
{
	body->originCoordinate[0][0] = body->centrePosition[0] + body->relaCoordinate[0][0]; body->originCoordinate[0][1] = body->centrePosition[1] + body->relaCoordinate[0][1]; body->originCoordinate[0][2] = body->centrePosition[2] + body->relaCoordinate[0][2]; 
	body->originCoordinate[1][0] = body->centrePosition[0] + body->relaCoordinate[1][0]; body->originCoordinate[1][1] = body->centrePosition[1] + body->relaCoordinate[1][1]; body->originCoordinate[1][2] = body->centrePosition[2] + body->relaCoordinate[1][2]; 
	body->originCoordinate[2][0] = body->centrePosition[0] + body->relaCoordinate[2][0]; body->originCoordinate[2][1] = body->centrePosition[1] + body->relaCoordinate[2][1]; body->originCoordinate[2][2] = body->centrePosition[2] + body->relaCoordinate[2][2]; 
	body->originCoordinate[3][0] = body->centrePosition[0] + body->relaCoordinate[3][0]; body->originCoordinate[3][1] = body->centrePosition[1] + body->relaCoordinate[3][1]; body->originCoordinate[3][2] = body->centrePosition[2] + body->relaCoordinate[3][2]; 
	body->originCoordinate[4][0] = body->centrePosition[0] + body->relaCoordinate[4][0]; body->originCoordinate[4][1] = body->centrePosition[1] + body->relaCoordinate[4][1]; body->originCoordinate[4][2] = body->centrePosition[2] + body->relaCoordinate[4][2]; 
	body->originCoordinate[5][0] = body->centrePosition[0] + body->relaCoordinate[5][0]; body->originCoordinate[5][1] = body->centrePosition[1] + body->relaCoordinate[5][1]; body->originCoordinate[5][2] = body->centrePosition[2] + body->relaCoordinate[5][2]; 
	body->originCoordinate[6][0] = body->centrePosition[0] + body->relaCoordinate[6][0]; body->originCoordinate[6][1] = body->centrePosition[1] + body->relaCoordinate[6][1]; body->originCoordinate[6][2] = body->centrePosition[2] + body->relaCoordinate[6][2]; 
	body->originCoordinate[7][0] = body->centrePosition[0] + body->relaCoordinate[7][0]; body->originCoordinate[7][1] = body->centrePosition[1] + body->relaCoordinate[7][1]; body->originCoordinate[7][2] = body->centrePosition[2] + body->relaCoordinate[7][2]; 
}

//�������ƽ����� 
void BodyPlaneCal(bodyInfo *body)
{
	body->planeInformation[0] = PlaneInfoInit(body->originCoordinate[0], body->originCoordinate[1], body->originCoordinate[2], body->originCoordinate[3], body->finalCoordinate[0], body->finalCoordinate[1], body->finalCoordinate[2], body->finalCoordinate[3]);
	body->planeInformation[1] = PlaneInfoInit(body->originCoordinate[7], body->originCoordinate[6], body->originCoordinate[5], body->originCoordinate[4], body->finalCoordinate[7], body->finalCoordinate[6], body->finalCoordinate[5], body->finalCoordinate[4]);
	body->planeInformation[2] = PlaneInfoInit(body->originCoordinate[5], body->originCoordinate[6], body->originCoordinate[2], body->originCoordinate[1], body->finalCoordinate[5], body->finalCoordinate[6], body->finalCoordinate[2], body->finalCoordinate[1]);
	body->planeInformation[3] = PlaneInfoInit(body->originCoordinate[6], body->originCoordinate[7], body->originCoordinate[3], body->originCoordinate[2], body->finalCoordinate[6], body->finalCoordinate[7], body->finalCoordinate[3], body->finalCoordinate[2]);
	body->planeInformation[4] = PlaneInfoInit(body->originCoordinate[7], body->originCoordinate[4], body->originCoordinate[0], body->originCoordinate[3], body->finalCoordinate[7], body->finalCoordinate[4], body->finalCoordinate[0], body->finalCoordinate[3]);
	body->planeInformation[5] = PlaneInfoInit(body->originCoordinate[1], body->originCoordinate[0], body->originCoordinate[4], body->originCoordinate[5], body->finalCoordinate[1], body->finalCoordinate[0], body->finalCoordinate[4], body->finalCoordinate[5]);
	//body->vector[0] = body->planeInformation[3].coffiecient[0];
	//body->vector[1] = body->planeInformation[3].coffiecient[1];
	//body->vector[2] = body->planeInformation[3].coffiecient[2];
}

//����ƽ�� 
void Translation(bodyInfo *body, float finalX, float finalY, float finalZ)
{
	body->centrePosition[0] = finalX;
	body->centrePosition[1] = finalY;
	body->centrePosition[2] = finalZ;
	BodyPointCal(body);
	BodyPlaneCal(body);
}

//������ת 
void Spin(bodyInfo *body, float angle)
{
	int i;
	
	for(i = 0;i < 8;i++)
	{
		//SpinPoint(body->relaCoordinate[i], - body->angle);
		SpinPoint(body->relaCoordinate[i], angle);
	}
	body->angle = angle;
	BodyPointCal(body);
	BodyPlaneCal(body);
}


void SpinPoint(float point[], float angle)
{
	int i;
	float temp[3];
	
	for(i = 0;i < 3;i++)
	{
		temp[i] = point[i];
	}
	point[0] = cos(angle * M_PI / 180) * temp[0] + (-1) * sin(angle * M_PI / 180) * temp[1];
	point[1] = sin(angle * M_PI / 180) * temp[0] + cos(angle * M_PI / 180) * temp[1];
	point[2] = temp[2];
}