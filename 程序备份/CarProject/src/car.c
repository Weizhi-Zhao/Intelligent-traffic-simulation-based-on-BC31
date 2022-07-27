#include "Car.h"
#include "directedLine.h"

int JudgeCarCrash(DirectedLine *line, Car *car)
{
    int i;
    for(i = 0; i < 4; i++)
    {
        if(JudgeCarCrash(line, &(car->crashbody[i])))
        {
            return 1;
        }
    }
    return 0;
}