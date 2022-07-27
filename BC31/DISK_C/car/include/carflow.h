#ifndef __TRAFFICFLOW__
#define __TRAFFICFLOW__

#include "direct~1.h"

typedef struct CarflowStruct
{
    int term;
    int carnum;
    DirectedLine *road[12];
} Carflow;

extern Carflow carflow[4];

void InitCarflow(Carflow *carflow, DirectedLine roadS[], DirectedLine roadL[], DirectedLine roadR[], int term);

void ShowCarnum(Carflow *carflow, int x, int y);

#endif