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

//����UVN���ᵥλ����
void CalUVN(coordinateSystem *coordinate)
{
	int i;
	for(i = 0;i < 3;i++)
    {
    	coordinate->nAxis[i] = - (coordinate->eye[i] - coordinate->focusPoint[i]) / sqrt(pow(coordinate->eye[0] - coordinate->focusPoint[0], 2) + pow(coordinate->eye[1] - coordinate->focusPoint[1], 2) + pow(coordinate->eye[2] - coordinate->focusPoint[2], 2));
	}

	coordinate->uAxis[0] = -(coordinate->V[1] * coordinate->nAxis[2] - coordinate->V[2] * coordinate->nAxis[1]);
	coordinate->uAxis[1] = -(coordinate->V[2] * coordinate->nAxis[0] - coordinate->V[0] * coordinate->nAxis[2]);
	coordinate->uAxis[2] = -(coordinate->V[0] * coordinate->nAxis[1] - coordinate->V[1] * coordinate->nAxis[0]);
	coordinate->u0 = coordinate->uAxis[0], coordinate->u1 = coordinate->uAxis[1], coordinate->u2 = coordinate->uAxis[2];
	for(i = 0;i < 3;i++)
	{
		coordinate->uAxis[i] = coordinate->uAxis[i] / sqrt(coordinate->u0 * coordinate->u0 + coordinate->u1 * coordinate->u1 + coordinate->u2 * coordinate->u2);
	}
	
	coordinate->vAxis[0] = coordinate->nAxis[1] * coordinate->uAxis[2] - coordinate->nAxis[2] * coordinate->uAxis[1];
	coordinate->vAxis[1] = coordinate->nAxis[2] * coordinate->uAxis[0] - coordinate->nAxis[0] * coordinate->uAxis[2];
	coordinate->vAxis[2] = coordinate->nAxis[0] * coordinate->uAxis[1] - coordinate->nAxis[1] * coordinate->uAxis[0];
} 

//���������õ�λ������������任���� 
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

//��ά�任 
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

//�������������ϵ��Ϊ�۲�����ϵ
void CoordinateChange(float origin[], float change[][4], float final[])
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

//���������
float DotMultiply(float a[], float b[])
{
    int i;
    float result = 0;
    for(i = 0; i < 3; i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

//������ʼ��
void VectorSet(float target[], float a, float b, float c, float d)
{
	target[0] = a;
	target[1] = b;
	target[2] = c;
	target[3] = d;
}

//�任�����ʼ�� 
void ChangeMatrixInit(float change[][4])
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

//����ͶӰ��ͼ�еĸ��� 
void ConnectDots(bodyInfo *body, coordinateSystem *coordinate, int color, int lcolor)
{	
	int i;
	float temp[3];
	
	for(i = 0;i < 3;i++)
	{
		temp[i] = coordinate->eye[i] - coordinate->focusPoint[i];
	}
	for(i = 0;i < 6;i++)
	{
		CalPlaneCoffiecient(&(body->planeInformation[i]));
		if(DotMultiply(body->planeInformation[i].coffiecient, temp) > 0)
		{
			DrawPlane(&(body->planeInformation[i]), coordinate, color, lcolor);
		}
	}
}

//��ת�ӽ� 
void ChangeView(void *coordinate, void *key)
{ 
	int *letter = key;
	static float angle = 120;
	coordinateSystem *c = coordinate;
	float distance = sqrt(pow(c->eye[0] - c->focusPoint[0], 2) + pow(c->eye[1] - c->focusPoint[1], 2));
	
	if((*letter & 0x00ff) == 's')
	{
		c->eye[2] -= 0.5;
	}
	else if((*letter & 0x00ff) == 'w')
	{
		c->eye[2] += 0.5;
	}
	else if((*letter & 0x00ff) == 'a')
	{
		angle -= 10.0 / 360;
	}
	else if((*letter & 0x00ff) == 'd')
	{
		angle += 10.0 / 360;
	}
	c->eye[0] = cos(angle) * distance + c->focusPoint[0];
	c->eye[1] = sin(angle) * distance + c->focusPoint[1];
	CalUVN(coordinate);
	GiveUnit(coordinate);
}

//�ӽ�ע�ӵ�任(ƽ��) 
void FocusChange(void *coordinate, void *key)
{
	int *letter = key;
	coordinateSystem *c = coordinate;
	
	if(*letter == 0x4b00)//����� 
	{
		c->eye[0]  += 1;
		c->focusPoint[0] += 1;
	}
	else if(*letter == 0x4d00)//�ҷ����
	{
		c->eye[0]  -= 1;
		c->focusPoint[0] -= 1;
	} 
	else if(*letter == 0x4800)//�Ϸ����
	{
		c->eye[1]  += 1;
		c->focusPoint[1] += 1;
	}
	else if(*letter == 0x5000)//�·����
	{
		c->eye[1]  -= 1;
		c->focusPoint[1] -= 1;
	}
	CalUVN(coordinate);
	GiveUnit(coordinate);
}

//�������� 
void ZoomInAndOut(void *coordinate, void *key)
{
	int *letter = key;
	coordinateSystem *c = coordinate;
	
	if(c->maganification >= 0 && c->maganification <= 80)
	{
		if((*letter & 0x00ff) == 'q')//��С 
		{
			if(c->maganification >= 1)
			{
				c->maganification -= 1;
			}
		}
		else if((*letter & 0x00ff) == 'e')//�Ŵ� 
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
