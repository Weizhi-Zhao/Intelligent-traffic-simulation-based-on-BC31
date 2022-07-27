#ifndef __DirectedLine__
#define __DirectedLine__

#define max(x, y) x > y ? x : y
#define min(x, y) x < y ? x : y

//点结构体，用于记录一个点的坐标
typedef struct
{
    float x, y;
} Point;

struct structDirectedLine;

//邻接表的边，记录所有支路
typedef struct structDLEdge
{
    struct structDirectedLine *to;
    struct structDLEdge *next;
} DLEdge;

//有向折线邻接表节点，记录一个线段的起点，终点，长度，支路个数，下一条边指针
typedef struct structDirectedLine
{
    Point start, end;
    float lenth;
    int branchNum;
    struct structDirectedLine *straight, *left, *right;
    DLEdge *next;
} DirectedLine;

DirectedLine newDirectedLine(float startX, float StartY, float endX, float endY);

void ConnectDLine(DirectedLine *line1, DirectedLine *line2);

Point posToPoint(DirectedLine *line, float pos);

int JudgeCrash(DirectedLine *line1, DirectedLine *line2);

void DeleteDLine(DirectedLine *line);

#endif