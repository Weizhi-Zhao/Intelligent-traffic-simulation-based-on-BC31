#ifndef __DirectedLine__
#define __DirectedLine__

//点结构体，用于记录一个点的坐标
typedef struct
{
    float x, y;
} Point;

//邻接表的边，记录所有支路
typedef struct
{
    DirectedLine *to;
    DLEdge *next;
} DLEdge;

//有向折线邻接表节点，记录一个线段的起点，终点，长度，支路个数，下一条边指针
typedef struct
{
    Point start, end;
    float lenth;
    int branchNum;
    DLEdge *next;
} DirectedLine;

DirectedLine *newDirectedLine(float startX, float StartY, float endX, float endY);

void ConnectDLine(DirectedLine *line1, DirectedLine *line2);

Point posToPoint(DirectedLine *line, float pos);

void DeleteDLine(DirectedLine *line);

#endif