#include "carflow.h"
#include <time.h>
#include <string.h>

Carflow carflow[4];

void InitCarflow(Carflow *carflow, DirectedLine roadS[], DirectedLine roadL[], DirectedLine roadR[], int term)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        carflow->road[i] = &roadS[i];
    }
    for(i = 0; i < 3; i++)
    {
        carflow->road[i + 4] = &roadL[i];
    }
    for(i = 0; i < 3; i++)
    {
        carflow->road[i + 8] = &roadL[i];
    }
    carflow->term = term;
    carflow->carnum = 0;
}

void ShowCarnum(Carflow *carflow, int x, int y)
{
    char carnum[4];

    if(time(0) % carflow->term == 0)
    {
        carflow->carnum = 0;
    }

    itoa(carflow->carnum, carnum, 10);
    outtextxy(x, y, carnum);
}