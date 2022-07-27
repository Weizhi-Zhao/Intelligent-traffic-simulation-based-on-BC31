#ifndef __ROAD__
#define __ROAD__

#include "3dimen.h"

extern DirectedLine lineN[5], lineS[5], lineE[6], lineW[6], lineCL[4][4], lineCR[4][4], lineCS[4][4], *startLine[7];
extern bodyInfo yellowLine[11];
extern bodyInfo Road[15];

void DrawCenterRoad(bodyInfo *road, float x, float y);

void DrawEWRoad(bodyInfo *road, float x, float y);

void DrawSNRoad(bodyInfo *road, float x, float y);

void setEWLine(DirectedLine *up, DirectedLine *down, float x, float y);

void setSNLine(DirectedLine *left, DirectedLine *right, float x, float y);

void DrawSNLine(bodyInfo *line, float x, float y);

void DrawEWLine(bodyInfo *line, float x, float y);

void setCenterRightLine(DirectedLine *up, DirectedLine *down, DirectedLine *left
    , DirectedLine *right, float x, float y);

void setCenterLeftLine(DirectedLine *up, DirectedLine *down, DirectedLine *left
    , DirectedLine *right, float x, float y);

void setCenterStraightLine(DirectedLine *up, DirectedLine *down, DirectedLine *left
    , DirectedLine *right, float x, float y);

void InitLine();

void ConnectLine();

void SortRoad(bodyInfo road[]);

#endif