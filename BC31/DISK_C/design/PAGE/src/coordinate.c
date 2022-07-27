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
#include "mouse1.h"

//ï¿½ï¿½ï¿½ï¿½UVNï¿½ï¿½ï¿½áµ¥Î»ï¿½ï¿½ï¿½ï¿½
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

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ãµï¿½Î»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ä»»ï¿½ï¿½ï¿½ï¿½ 
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

//ï¿½ï¿½Î¬ï¿½ä»» 
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

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ïµï¿½ï¿½Îªï¿½Û²ï¿½ï¿½ï¿½ï¿½ï¿½Ïµ
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

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
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

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¼ï¿½ï¿½
void VectorSet(float target[], float a, float b, float c, float d)
{
	target[0] = a;
	target[1] = b;
	target[2] = c;
	target[3] = d;
}

//ï¿½ä»»ï¿½ï¿½ï¿½ï¿½ï¿½Ê¼ï¿½ï¿½ 
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

//ï¿½ï¿½ï¿½ï¿½Í¶Ó°ï¿½ï¿½Í¼ï¿½ÐµÄ¸ï¿½ï¿½ï¿½ 
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

//ï¿½ï¿½×ªï¿½Ó½ï¿½ 
void ChangeView(void *coordinate, void *key)
{ 
	int *letter = key;
	static float angle = 120;
	coordinateSystem *c = coordinate;
	float distance = sqrt(pow(c->eye[0] - c->focusPoint[0], 2) + pow(c->eye[1] - c->focusPoint[1], 2));
	
	if((*letter & 0x00ff) == 's')
	{
		c->eye[2] -= 3;
	}
	else if((*letter & 0x00ff) == 'w')
	{
		c->eye[2] += 3;
	}
	else if((*letter & 0x00ff) == 'a')
	{
		angle -= 20.0 / 180 * M_PI;
	}
	else if((*letter & 0x00ff) == 'd')
	{
		angle += 20.0 / 180 * M_PI;
	}
	c->eye[0] = cos(angle) * distance + c->focusPoint[0];
	c->eye[1] = sin(angle) * distance + c->focusPoint[1];
	CalUVN(coordinate);
	GiveUnit(coordinate);
}

//ï¿½Ó½ï¿½×¢ï¿½Óµï¿½ä»»(Æ½ï¿½ï¿½) 
void FocusChange(void *coordinate, void *key)
{
	static int state = 0;
	int *letter = key;
	coordinateSystem *c = coordinate;
	
	if(*letter == 0x4b00)//×ó
	{
		c->eye[1] -= 5;
		c->focusPoint[1] -= 5;
	}
	else if(*letter == 0x4d00)//ÓÒ
	{
		c->eye[1] += 5;
		c->focusPoint[1] += 5;
	} 
	else if(*letter == 0x4800)//ÉÏ
	{
		c->eye[0] -= 5; 
		c->focusPoint[0] -= 5;
	}
	else if(*letter == 0x5000)//ÏÂ
	{
		c->eye[0] += 5;
		c->focusPoint[0] += 5;
	}
	else if(*letter == 0x2c7a)//z¼ü¶þÎ¬ÈýÎ¬×ª»»
	{
		state = 1 - state;
		if(state == 1)
		{
			c->eye[0] = c->focusPoint[0] + 0.1;
			c->eye[1] = c->focusPoint[1] + 0.1;
		}
		else
		{
			c->eye[0] = c->focusPoint[0] + 10;
			c->eye[1] = c->focusPoint[1] + 10;
		}
	}
	CalUVN(coordinate);
	GiveUnit(coordinate);
}

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 
void ZoomInAndOut(void *coordinate, void *key)
{
	int *letter = key;
	coordinateSystem *c = coordinate;
	
	if(c->maganification >= 0 && c->maganification <= 80)
	{
		if((*letter & 0x00ff) == 'q')//ï¿½ï¿½Ð¡ 
		{
			if(c->maganification >= 2)
			{
				c->maganification -= 2;
			}
		}
		else if((*letter & 0x00ff) == 'e')//ï¿½Å´ï¿½ 
		{
			if(c->maganification <= 78)
			{
				c->maganification += 2;
			}
		}
	}
	else
	{
		return;
	}
}
