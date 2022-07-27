#include "traffi~1.h"
#include <time.h>

void InitTrafficLight(TrafficLight *TL, float x, float y, DirectedLine *stopper, int term)
{
    int i;
    TL->x = x;
    TL->y = y;

    TL->term = term;
    TL->NSGreenTime = term / 2;

    BodyInfoInit(&(TL->light[0]), 0.2, 2, 2, x + 1.2, y, 7.1, 0, 0, 0);
    BodyInfoInit(&(TL->light[1]), 0.2, 2, 2, x + 1.2, y, 9.2, 0, 0, 0);
    BodyInfoInit(&(TL->light[2]), 0.2, 2, 2, x + 1.2, y, 11.3, 0, 0, 0);

    BodyInfoInit(&(TL->light[3]), 0.2, 2, 2, x - 1.2, y, 7.1, 0, 0, 0);
    BodyInfoInit(&(TL->light[4]), 0.2, 2, 2, x - 1.2, y, 9.2, 0, 0, 0);
    BodyInfoInit(&(TL->light[5]), 0.2, 2, 2, x - 1.2, y, 11.3, 0, 0, 0);

    BodyInfoInit(&(TL->light[6]), 2, 0.2, 2, x, y - 1.2, 7.1, 0, 0, 0);
    BodyInfoInit(&(TL->light[7]), 2, 0.2, 2, x, y - 1.2, 9.2, 0, 0, 0);
    BodyInfoInit(&(TL->light[8]), 2, 0.2, 2, x, y - 1.2, 11.3, 0, 0, 0);

    BodyInfoInit(&(TL->light[9]), 2, 0.2, 2, x, y + 1.2, 7.1, 0, 0, 0);
    BodyInfoInit(&(TL->light[10]), 2, 0.2, 2, x, y + 1.2, 9.2, 0, 0, 0);
    BodyInfoInit(&(TL->light[11]), 2, 0.2, 2, x, y + 1.2, 11.3, 0, 0, 0);

    for(i = 0; i < 4; i++)
    {
        TL->stopper[i] = stopper + i;
    }
}

void DrawTrafficLight(TrafficLight *TL, coordinateSystem *coordinate)
{
    int did[13] = {0};
    int id = 0;
    int i, j;
    int NSGreen;
    bodyInfo temp;

    for(i = 0; i < 12; i++)
    {
        for(j = 0; j < 8; j++)
        {
            VectorSet(TL->light[i].finalCoordinate[j], 0, 0, 0, 0);
            CoordinateChange(TL->light[i].originCoordinate[j], coordinate->change, TL->light[i].finalCoordinate[j]);
        }
        VectorSet(TL->light[i].finalCentrePosition, 0, 0, 0, 0);
        TL->light[i].centrePosition[3] = 1;
        CoordinateChange(TL->light[i].centrePosition, coordinate->change, TL->light[i].finalCentrePosition);
    }

    if(time(0) % TL->term <= TL->NSGreenTime - 1)
    {
        TL->timeCounter = TL->NSGreenTime - time(0) % TL->term;
        NSGreen = 1;
        *(TL->stopper[0]) = newDirectedLine(TL->x + 5, TL->y + 0, TL->x + 5, TL->y + 0);
		*(TL->stopper[1]) = newDirectedLine(TL->x + 0, TL->y + 5, TL->x - 5, TL->y + 5);
		*(TL->stopper[2]) = newDirectedLine(TL->x - 5, TL->y + 0, TL->x - 5, TL->y + 0);
		*(TL->stopper[3]) = newDirectedLine(TL->x + 0, TL->y - 5, TL->x + 5, TL->y - 5);
    }
    else
    {
        TL->timeCounter = TL->term - time(0) % TL->term;
        NSGreen = 0;
        *(TL->stopper[0]) = newDirectedLine(TL->x + 5, TL->y + 0, TL->x + 5, TL->y + 5);
		*(TL->stopper[1]) = newDirectedLine(TL->x + 0, TL->y + 5, TL->x + 0, TL->y + 5);
		*(TL->stopper[2]) = newDirectedLine(TL->x - 5, TL->y + 0, TL->x - 5, TL->y - 5);
		*(TL->stopper[3]) = newDirectedLine(TL->x + 0, TL->y - 5, TL->x + 0, TL->y - 5);
    }

    for(i = 0; i < 13; i++)
    {
        temp.finalCentrePosition[2] = -1200000;
        //id = i;
        for(j = 0; j < 13; j++)
        {
            if(did[j] == 0)
            {
                if(temp.finalCentrePosition[2] < TL->light[j].finalCentrePosition[2])
                {
                    id = j;
                    temp = TL->light[j];
                }
            }
        }
        if(NSGreen)
        {
            if(time(0) % TL->term <= 1)
            {
                if(id == 7 || id == 10)
                {
                    ConnectDots(&temp, coordinate, 7, 15);
                }
            }
            else
            {
                if(id == 8 || id == 11)
                {
                    ConnectDots(&temp, coordinate, 2, 15);
                }
            }
            if(id == 0 || id == 3)
            {
                ConnectDots(&temp, coordinate, 5, 15);
            }
        }
        else
        {
            if(time(0) % TL->term <= TL->NSGreenTime + 1)
            {
                if(id == 1 || id == 4)
                {
                    ConnectDots(&temp, coordinate, 7, 15);
                }
            }
            else
            {
                if(id == 2 || id == 5)
                {
                    ConnectDots(&temp, coordinate, 2, 15);
                }
            }
            if(id == 6 || id == 9)
            {
                ConnectDots(&temp, coordinate, 5, 15);
            }
        }
        did[id] = 1;
    }
}
