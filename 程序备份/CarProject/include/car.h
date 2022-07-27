#ifndef __CAR__
#define __CAR__

#include "directedLine.h"

typedef struct
{
    DirectedLine crashDetecter;
    DirectedLine crashbody[4];
} Car;

void InitCar();

bool JudgeCarCrash(DirectedLine *line, Car *car);

#endif