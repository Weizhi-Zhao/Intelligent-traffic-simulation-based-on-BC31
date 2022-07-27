#include "Direct~1.h"
#include "DirectedLine.h"
#include <math.h>
#include <stdlib.h>
#include <alloc.h>

DirectedLine *newDirectedLine(float startX, float StartY, float endX, float endY)
{
    DirectedLine *line = (DirectedLine*)malloc(sizeof(DirectedLine));
    line->start.x = startX;
    line->start.y = startY;
    line->end.x = endX;
    line->end.y = endY;
    line->lenth = sqrtf(powf(endX - startX, 2) + powf(endY - startY, 2));
    line->branchNum = 0;
    line->next = NULL;
    return line;
}

void ConnectDLine(DirectedLine *line1, DirectedLine *line2)
{
    DLEdge *edge = (DLEdge*)malloc(sizeof(DLEdge));
    edge->to = line2;
    edge->next = line1->next;
    line1->next = edge;
    line1->branchNum++;
}

Point posToPoint(DirectedLine *line, float pos)
{
    Point point;
    
    point.x = -1;
    point.y = -1;
    
    if(pos < 0)
    {
        return point;
    }

    point.x = line->start->x + (line->end->x - line->start->x) / line->lenth * pos;
    point.y = line->start->y + (line->end->y - line->start->y) / line->lenth * pos;

    return point;
}

void DeleteDLine(DirectedLine *line)
{
    DLEdge *now, *next;
    now = line->next;
    while(now != NULL)
    {
        next = now->next;
        free(now);
        now = next;
    }
    free(line);
}