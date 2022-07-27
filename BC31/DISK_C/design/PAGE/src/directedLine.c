#include "Direct~1.h"
#include <math.h>
#include <stdlib.h>
#include <alloc.h>

DirectedLine newDirectedLine(float startX, float startY, float endX, float endY)
{
    DirectedLine line;
    line.start.x = startX;
    line.start.y = startY;
    line.end.x = endX;
    line.end.y = endY;
    line.lenth = sqrt(pow(endX - startX, 2) + pow(endY - startY, 2));
    line.straight = NULL;
    line.left = NULL;
    line.right = NULL;
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
    
    // point.x = -1;
    // point.y = -1;
    
    // if(pos < 0)
    // {
    //     return point;
    // }

	point.x = line->start.x + (line->end.x - line->start.x) / line->lenth * pos;
	point.y = line->start.y + (line->end.y - line->start.y) / line->lenth * pos;

    return point;
}

int JudgeCrash(DirectedLine *line1, DirectedLine *line2)
{
    
    float ax1 = line1->start.x;
    float ay1 = line1->start.y;
    float ax2 = line1->end.x;
    float ay2 = line1->end.y;
    float bx1 = line2->start.x;
    float by1 = line2->start.y;
    float bx2 = line2->end.x;
    float by2 = line2->end.y;
    //printf("lalala");
    if( ( max(ax1, ax2) >= min(bx1, bx2) && min(ax1, ax2) <= max(bx1, bx2) ) 
        && ( max(ay1, ay2) >= min(by1, by2) && min(ay1, ay2) <= max(by1, by2) ) )
    {
        if(
            ( (bx1 - ax1) * (ay2 - ay1) - (by1 - ay1) * (ax2 - ax1) )
            * ( (bx2 - ax1) * (ay2 - ay1) - (by2 - ay1) * (ax2 - ax1) ) <= 0
            &&
            ( (ax1 - bx1) * (by2 - by1) - (ay1 - by1) * (bx2 - bx1) )
            * ( (ax2 - bx1) * (by2 - by1) - (ay2 - by1) * (bx2 - bx1) ) <= 0
        )
        {
			return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
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