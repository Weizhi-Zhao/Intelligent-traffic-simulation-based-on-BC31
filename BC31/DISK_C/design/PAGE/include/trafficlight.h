#ifndef __TRAFFICLIGHT__
#define __TRAFFICLIGHT__

#include "3dimen.h"
#include "direct~1.h"

typedef struct TrafficLightStruct
{
    bodyInfo light[12];
    DirectedLine *stopper[4];
    int term;
    int NSGreenTime;
    float x, y;
    int timeCounter;
} TrafficLight;

extern TrafficLight trafficLight[4];

extern DirectedLine RGL[16];

void InitTrafficLight(TrafficLight *TL, float x, float y, DirectedLine *stopper, int term);

void DrawTrafficLight(TrafficLight *TL, coordinateSystem *coordinate);

#endif