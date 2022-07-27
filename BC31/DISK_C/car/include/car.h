#ifndef __CAR__
#define __CAR__

#include "direct~1.h"
#include "3dimen.h"

typedef struct CarStruct
{
    DirectedLine crashDetecter, slowDetecter;
    DirectedLine crashbody[4];
    DirectedLine oriCrashDetecter, oriSlowDetecter;
    DirectedLine oriCrashbody[4];
    DirectedLine *nowLine;
    float dis;
    int color;
    bodyInfo carBody[7];
    float carBodyRelaPos[7][3];
    float pos[3];
    float speed;
    float angle;
    float maxSpeed, slowSpeed;
    float acc;
    int visiable;
    int turn;
} Car;

extern Car car1[12];

void InitCar(Car *car);

void InitBus(Car *car);

void VectorSet3(float v[], float a, float b, float c);

void DrawCar(Car *car, coordinateSystem *coordinate);

void MoveCar(Car *car, float x, float y, float angle, coordinateSystem *coordinate);

int JudgeCarCrash(DirectedLine *line, Car *car);

void SpinPoint_Point(Point *p, float angle);

void RunCar(Car car[], int carnum, DirectedLine *startLine[], coordinateSystem *coordinate);

#endif