#include "3dimen.h"
#include "direct~1.h"
#include "road.h"

void DrawCenterRoad(bodyInfo *road, float x, float y)
{
    BodyInfoInit(road, 10, 10, 0.1, x, y, -0.05, 0, 0, 0);
}

void DrawEWRoad(bodyInfo *road, float x, float y)
{
    BodyInfoInit(road, 10, 50, 0.1, x, y, -0.05, 0, 0, 0);
}

void DrawSNLine(bodyInfo *line, float x, float y)
{
    BodyInfoInit(line, 50, 0.3, 0.01, x, y, 0.055, 0, 0, 0);
}

void DrawEWLine(bodyInfo *line, float x, float y)
{
    BodyInfoInit(line, 0.3, 50, 0.01, x, y, 0.055, 0, 0, 0);
}

void DrawSNRoad(bodyInfo *road, float x, float y)
{
    BodyInfoInit(road, 50, 10, 0.1, x, y, -0.05, 0, 0, 0);
}

void setEWLine(DirectedLine *up, DirectedLine *down, float x, float y)
{
    *up = newDirectedLine(x - 2.75, y + 25, x - 2.75, y - 25);
    *down = newDirectedLine(x + 2.75, y - 25, x + 2.75, y + 25);
}

void setSNLine(DirectedLine *left, DirectedLine *right, float x, float y)
{
    *right = newDirectedLine(x + 25, y + 2.75, x - 25, y + 2.75);
    *left = newDirectedLine(x - 25, y - 2.75, x + 25, y - 2.75);
}

void setCenterRightLine(DirectedLine *up, DirectedLine *down, DirectedLine *left
    , DirectedLine *right, float x, float y)
{
    *down = newDirectedLine(x + 5, y + 2.75, x + 2.75, y + 5);
    *right = newDirectedLine(x - 2.75, y + 5, x - 5, y + 2.75);
    *up = newDirectedLine(x - 5, y - 2.75, x - 2.75, y - 5);
    *left = newDirectedLine(x + 2.75, y - 5, x + 5, y - 2.75);
}

void setCenterLeftLine(DirectedLine *up, DirectedLine *down, DirectedLine *left
    , DirectedLine *right, float x, float y)
{
    *down = newDirectedLine(x + 5, y + 2.75, x - 2.75, y - 5);
    *right = newDirectedLine(x - 2.75, y + 5, x + 5, y - 2.75);
    *up = newDirectedLine(x - 5, y - 2.75, x + 2.75, y + 5);
    *left = newDirectedLine(x + 2.75, y - 5, x - 5, y + 2.75);
}

void setCenterStraightLine(DirectedLine *up, DirectedLine *down, DirectedLine *left
    , DirectedLine *right, float x, float y)
{
    *down = newDirectedLine(x + 5, y + 2.75, x - 5, y + 2.75);
    *right = newDirectedLine(x - 2.75, y + 5, x - 2.75, y - 5);
    *up = newDirectedLine(x - 5, y - 2.75, x + 5, y - 2.75);
    *left = newDirectedLine(x + 2.75, y - 5, x + 2.75, y + 5);
}

void InitLine()
{
	setEWLine(&lineW[0], &lineE[0], -5, -35);
	setEWLine(&lineW[1], &lineE[1], -5, 25);
	setEWLine(&lineW[2], &lineE[2], -5, 85);
	setEWLine(&lineW[3], &lineE[3], 55, -35);
	setEWLine(&lineW[4], &lineE[4], 55, 25);
	setEWLine(&lineW[5], &lineE[5], 55, 85);

	setSNLine(&lineS[0], &lineN[0], -35, -5);
	setSNLine(&lineS[1], &lineN[1], 25, -5);
	setSNLine(&lineS[2], &lineN[2], -35, 55);
	setSNLine(&lineS[3], &lineN[3], 25, 55);
	setSNLine(&lineS[4], &lineN[4], 85, 55);

	setCenterLeftLine(&lineCL[0][0], &lineCL[0][1], &lineCL[0][2], &lineCL[0][3], -5, -5);
	setCenterLeftLine(&lineCL[1][0], &lineCL[1][1], &lineCL[1][2], &lineCL[1][3], -5, 55);
	setCenterLeftLine(&lineCL[2][0], &lineCL[2][1], &lineCL[2][2], &lineCL[2][3], 55, -5);
	setCenterLeftLine(&lineCL[3][0], &lineCL[3][1], &lineCL[3][2], &lineCL[3][3], 55, 55);

	setCenterRightLine(&lineCR[0][0], &lineCR[0][1], &lineCR[0][2], &lineCR[0][3], -5, -5);
	setCenterRightLine(&lineCR[1][0], &lineCR[1][1], &lineCR[1][2], &lineCR[1][3], -5, 55);
	setCenterRightLine(&lineCR[2][0], &lineCR[2][1], &lineCR[2][2], &lineCR[2][3], 55, -5);
	setCenterRightLine(&lineCR[3][0], &lineCR[3][1], &lineCR[3][2], &lineCR[3][3], 55, 55);

	setCenterStraightLine(&lineCS[0][0], &lineCS[0][1], &lineCS[0][2], &lineCS[0][3], -5, -5);
	setCenterStraightLine(&lineCS[1][0], &lineCS[1][1], &lineCS[1][2], &lineCS[1][3], -5, 55);
	setCenterStraightLine(&lineCS[2][0], &lineCS[2][1], &lineCS[2][2], &lineCS[2][3], 55, -5);
	setCenterStraightLine(&lineCS[3][0], &lineCS[3][1], &lineCS[3][2], &lineCS[3][3], 55, 55);
}

void ConnectLine()
{
	lineE[0].straight = &lineCS[0][2];
	lineE[0].left = &lineCL[0][2];
	lineE[0].right = &lineCR[0][2];
	
	lineW[1].straight = &lineCS[0][3];
	lineW[1].left = &lineCL[0][3];
	lineW[1].right = &lineCR[0][3];

	lineS[0].straight = &lineCS[0][0];
	lineS[0].left = &lineCL[0][0];
	lineS[0].right = &lineCR[0][0];

	lineN[1].straight = &lineCS[0][1];
	lineN[1].left = &lineCL[0][1];
	lineN[1].right = &lineCR[0][1];

	lineCS[0][3].straight = &lineW[0];
	lineCL[0][1].straight = &lineW[0];
	lineCR[0][0].straight = &lineW[0];

	lineCS[0][2].straight = &lineE[1];
	lineCL[0][0].straight = &lineE[1];
	lineCR[0][1].straight = &lineE[1];

	lineCS[0][1].straight = &lineN[0];
	lineCL[0][2].straight = &lineN[0];
	lineCR[0][3].straight = &lineN[0];

	lineCS[0][0].straight = &lineS[1];
	lineCL[0][3].straight = &lineS[1];
	lineCR[0][2].straight = &lineS[1];


	lineE[1].straight = &lineCS[1][2];
	lineE[1].left = &lineCL[1][2];
	lineE[1].right = &lineCR[1][2];
	
	lineW[2].straight = &lineCS[1][3];
	lineW[2].left = &lineCL[1][3];
	lineW[2].right = &lineCR[1][3];

	lineS[2].straight = &lineCS[1][0];
	lineS[2].left = &lineCL[1][0];
	lineS[2].right = &lineCR[1][0];

	lineN[3].straight = &lineCS[1][1];
	lineN[3].left = &lineCL[1][1];
	lineN[3].right = &lineCR[1][1];

	lineCS[1][3].straight = &lineW[1];
	lineCL[1][1].straight = &lineW[1];
	lineCR[1][0].straight = &lineW[1];

	lineCS[1][2].straight = &lineE[2];
	lineCL[1][0].straight = &lineE[2];
	lineCR[1][1].straight = &lineE[2];

	lineCS[1][1].straight = &lineN[2];
	lineCL[1][2].straight = &lineN[2];
	lineCR[1][3].straight = &lineN[2];

	lineCS[1][0].straight = &lineS[3];
	lineCL[1][3].straight = &lineS[3];
	lineCR[1][2].straight = &lineS[3];


	lineE[3].straight = &lineCS[2][2];
	lineE[3].left = &lineCL[2][2];
	//lineE[3].right = &lineCR[2][2];
	
	lineW[4].straight = &lineCS[2][3];
	//lineW[4].left = &lineCL[2][3];
	lineW[4].right = &lineCR[2][3];

	//lineS[1].straight = &lineCS[2][0];
	lineS[1].left = &lineCL[2][0];
	lineS[1].right = &lineCR[2][0];

	lineCS[2][3].straight = &lineW[3];
	lineCL[2][1].straight = &lineW[3];
	lineCR[2][0].straight = &lineW[3];

	lineCS[2][2].straight = &lineE[4];
	lineCL[2][0].straight = &lineE[4];
	lineCR[2][1].straight = &lineE[4];

	lineCS[2][1].straight = &lineN[1];
	lineCL[2][2].straight = &lineN[1];
	lineCR[2][3].straight = &lineN[1];


	lineE[4].straight = &lineCS[3][2];
	lineE[4].left = &lineCL[3][2];
	lineE[4].right = &lineCR[3][2];
	
	lineW[5].straight = &lineCS[3][3];
	lineW[5].left = &lineCL[3][3];
	lineW[5].right = &lineCR[3][3];

	lineS[3].straight = &lineCS[3][0];
	lineS[3].left = &lineCL[3][0];
	lineS[3].right = &lineCR[3][0];

	lineN[4].straight = &lineCS[3][1];
	lineN[4].left = &lineCL[3][1];
	lineN[4].right = &lineCR[3][1];

	lineCS[3][3].straight = &lineW[4];
	lineCL[3][1].straight = &lineW[4];
	lineCR[3][0].straight = &lineW[4];

	lineCS[3][2].straight = &lineE[5];
	lineCL[3][0].straight = &lineE[5];
	lineCR[3][1].straight = &lineE[5];

	lineCS[3][1].straight = &lineN[3];
	lineCL[3][2].straight = &lineN[3];
	lineCR[3][3].straight = &lineN[3];

	lineCS[3][0].straight = &lineS[4];
	lineCL[3][3].straight = &lineS[4];
	lineCR[3][2].straight = &lineS[4];

	startLine[0] = &lineE[0];
	startLine[1] = &lineE[3];
	startLine[2] = &lineW[2];
	startLine[3] = &lineW[5];
	startLine[4] = &lineS[0];
	startLine[5] = &lineS[2];
	startLine[6] = &lineN[4];
}

void DrawRoad(bodyInfo Road[])
{
	DrawCenterRoad(&Road[0], -5, -5);
	DrawCenterRoad(&Road[1], -5, 55);
	DrawCenterRoad(&Road[2], 55, -5);
	DrawCenterRoad(&Road[3], 55, 55);
	DrawEWRoad(&Road[4], -5, -35);
	DrawEWRoad(&Road[5], -5, 25);
	DrawEWRoad(&Road[6], -5, 85);
	DrawEWRoad(&Road[7], 55, -35);
	DrawEWRoad(&Road[8], 55, 25);
	DrawEWRoad(&Road[9], 55, 85);
	DrawSNRoad(&Road[10], -35, -5);
	DrawSNRoad(&Road[11], 25, -5);
	DrawSNRoad(&Road[12], -35, 55);
	DrawSNRoad(&Road[13], 25, 55);
	DrawSNRoad(&Road[14], 85, 55);

	DrawEWLine(&yellowLine[0], -5, -35);
	DrawEWLine(&yellowLine[1], -5, 25);
	DrawEWLine(&yellowLine[2], -5, 85);
	DrawEWLine(&yellowLine[3], 55, -35);
	DrawEWLine(&yellowLine[4], 55, 25);
	DrawEWLine(&yellowLine[5], 55, 85);
	DrawSNLine(&yellowLine[6], -35, -5);
	DrawSNLine(&yellowLine[7], 25, -5);
	DrawSNLine(&yellowLine[8], -35, 55);
	DrawSNLine(&yellowLine[9], 25, 55);
	DrawSNLine(&yellowLine[10], 85, 55);
}

void SortRoad(bodyInfo road[])
{
	int i, j;
	bodyInfo temp;
	for(i = 0; i < 15; i++)
	{
		for(j = i + 1; j < 15; j++)
		{
			if(road[i].finalCentrePosition[2] < road[j].finalCentrePosition[2])
			{
				temp = road[i];
				road[i] = road[j];
				road[j] = temp;
				BodyPlaneCal(&road[i]);
				BodyPlaneCal(&road[j]);
				BodyPointCal(&road[i]);
				BodyPointCal(&road[j]);
			}
		}
	}
}