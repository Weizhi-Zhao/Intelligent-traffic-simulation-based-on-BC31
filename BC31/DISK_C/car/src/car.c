#include "car.h"
#include "direct~1.h"
#include <math.h>
#include <stdlib.h>
#include "3dimen.h"
#include "carflow.h"

int JudgeCarCrash(DirectedLine *line, Car *car)
{
    int i;

    for(i = 0; i < 4; i++)
    {
        if(JudgeCrash(line, &(car->crashbody[i])))
        {
            return 1;
        }
    }
    return 0;
}

void InitCar(Car *car)
{
    car->turn = 0;
    car->visiable = 0;
    car->acc = 0.4;
    car->maxSpeed = 2;
    car->slowSpeed = 0.7;
    car->oriCrashDetecter = newDirectedLine(0, 0, 5, 0);
    car->oriSlowDetecter = newDirectedLine(0, 0, 10, 0);
    car->oriCrashbody[0] = newDirectedLine(2.25, 1, -2.25, 1);
    car->oriCrashbody[1] = newDirectedLine(-2.25, 1, -2.25, -1);
    car->oriCrashbody[2] = newDirectedLine(-2.25, -1, 2.25, -1);
    car->oriCrashbody[3] = newDirectedLine(2.25, -1, 2.25, 1);

    car->color = 8;
    car->angle = 0;
    car->dis = 0;
    BodyInfoInit(&(car->carBody[0]), 1, 2, 0.5, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[0], 1.75, 0, 0.35);
    // BodyInfoInit(&(car->carBody[1]), 0.5, 2, 0.5, 0, 0, 0, 0, 0, 0);
    // VectorSet3(car->carBodyRelaPos[1], 1.5, 0, 0.35);
    BodyInfoInit(&(car->carBody[1]), 2.5, 2, 1.3, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[1], 0, 0, 0.7);
    BodyInfoInit(&(car->carBody[2]), 1, 2, 0.5, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[2], -1.75, 0, 0.35);

    BodyInfoInit(&(car->carBody[3]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[3], 1.5, 1.05, 0.35);
    BodyInfoInit(&(car->carBody[4]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[4], 1.5, -1.05, 0.35);
    BodyInfoInit(&(car->carBody[5]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[5], -1.5, 1.05, 0.35);
    BodyInfoInit(&(car->carBody[6]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[6], -1.5, -1.05, 0.35);

    VectorSet3(car->pos, 0, 0, 0);
}

void InitBus(Car *car)
{
    car->turn = 0;
    car->visiable = 0;
    car->acc = 0.35;
    car->maxSpeed = 1.5;
    car->slowSpeed = 0.5;
    car->oriCrashDetecter = newDirectedLine(0, 0, 5, 0);
    car->oriSlowDetecter = newDirectedLine(0, 0, 10, 0);
    car->oriCrashbody[0] = newDirectedLine(4, 1, -4, 1);
    car->oriCrashbody[1] = newDirectedLine(-4, 1, -4, -1);
    car->oriCrashbody[2] = newDirectedLine(-4, -1, 4, -1);
    car->oriCrashbody[3] = newDirectedLine(4, -1, 4, 1);

    car->color = 8;
    car->angle = 0;
    car->dis = 0;
    BodyInfoInit(&(car->carBody[0]), 1, 2, 2, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[0], 3.5, 0, 1.1);
    BodyInfoInit(&(car->carBody[1]), 6, 2, 2, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[1], 0, 0, 1.1);
    BodyInfoInit(&(car->carBody[2]), 1, 2, 2, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[2], -3.5, 0, 1.1);

    BodyInfoInit(&(car->carBody[3]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[3], 3.5, 1.05, 0.35);
    BodyInfoInit(&(car->carBody[4]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[4], 3.5, -1.05, 0.35);
    BodyInfoInit(&(car->carBody[5]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[5], -3.5, 1.05, 0.35);
    BodyInfoInit(&(car->carBody[6]), 0.7, 0.1, 0.7, 0, 0, 0, 0, 0, 0);
    VectorSet3(car->carBodyRelaPos[6], -3.5, -1.05, 0.35);

    VectorSet3(car->pos, 0, 0, 0);
}

void MoveCar(Car *car, float x, float y, float angle, coordinateSystem *coordinate)
{
    int i, j;
    car->pos[0] = x;
    car->pos[1] = y;
    car->pos[2] = 0;
    for(i = 0; i < 7; i++)
    {
        Spin(&(car->carBody[i]), -car->angle);
        SpinPoint(car->carBodyRelaPos[i], -car->angle);
        Spin(&(car->carBody[i]), angle);
        SpinPoint(car->carBodyRelaPos[i], angle);
        Translation(&(car->carBody[i]), car->pos[0] + car->carBodyRelaPos[i][0], car->pos[1] + car->carBodyRelaPos[i][1], car->pos[2] + car->carBodyRelaPos[i][2]);
        for(j = 0; j < 8; j++)
        {
            VectorSet(car->carBody[i].finalCoordinate[j], 0, 0, 0, 0);
            CoordinateChange(car->carBody[i].originCoordinate[j], coordinate->change, car->carBody[i].finalCoordinate[j]);
        }
        VectorSet(car->carBody[i].finalCentrePosition, 0, 0, 0, 0);
        car->carBody[i].centrePosition[3] = 1;
        CoordinateChange(car->carBody[i].centrePosition, coordinate->change, car->carBody[i].finalCentrePosition);
    }

    SpinPoint_Point(&(car->oriCrashDetecter.end), -car->angle);
    SpinPoint_Point(&(car->oriCrashDetecter.end), angle);
    car->crashDetecter.end.x = car->oriCrashDetecter.end.x + car->pos[0];
    car->crashDetecter.start.x = car->oriCrashDetecter.start.x + car->pos[0];
    car->crashDetecter.end.y = car->oriCrashDetecter.end.y + car->pos[1];
    car->crashDetecter.start.y = car->oriCrashDetecter.start.y + car->pos[1];

    SpinPoint_Point(&(car->oriSlowDetecter.end), -car->angle);
    SpinPoint_Point(&(car->oriSlowDetecter.end), angle);
    car->slowDetecter.end.x = car->oriSlowDetecter.end.x + car->pos[0];
    car->slowDetecter.start.x = car->oriSlowDetecter.start.x + car->pos[0];
    car->slowDetecter.end.y = car->oriSlowDetecter.end.y + car->pos[1];
    car->slowDetecter.start.y = car->oriSlowDetecter.start.y + car->pos[1];

    for(i = 0; i < 4; i++)
    {
        SpinPoint_Point(&(car->oriCrashbody[i].end), -car->angle);
        SpinPoint_Point(&(car->oriCrashbody[i].end), angle);
        SpinPoint_Point(&(car->oriCrashbody[i].start), -car->angle);
        SpinPoint_Point(&(car->oriCrashbody[i].start), angle);
        car->crashbody[i].end.x = car->oriCrashbody[i].end.x + car->pos[0];
        car->crashbody[i].start.x = car->oriCrashbody[i].start.x + car->pos[0];
        car->crashbody[i].end.y = car->oriCrashbody[i].end.y + car->pos[1];
        car->crashbody[i].start.y = car->oriCrashbody[i].start.y + car->pos[1];
    }

    car->angle = angle;
}

void DrawCar(Car *car, coordinateSystem *coordinate)
{
    int i, j;
    int did[10] = {0}, didid;
    bodyInfo temp;
    for(i = 0; i < 7; i++)
    {
        temp.finalCentrePosition[2] = -1200000;
        for(j = 0; j < 7; j++)
        {
            if(did[j] == 0)
            {
                if(temp.finalCentrePosition[2] < car->carBody[j].finalCentrePosition[2])
                {
                    didid = j;
                    temp = car->carBody[j];
                }
            }
        }
        if(didid >= 3) ConnectDots(&temp, coordinate, 0, 15);
        else ConnectDots(&temp, coordinate, car->color, 15);
        did[didid] = 1;
    }
}

void VectorSet3(float v[], float a, float b, float c)
{
    v[0] = a;
    v[1] = b;
    v[2] = c;
}

void SpinPoint_Point(Point *p, float angle)
{
	int i;
	float temp[2];

    temp[0] = p->x;
    temp[1] = p->y;

	p->x = cos(angle * M_PI / 180) * temp[0] + (-1) * sin(angle * M_PI / 180) * temp[1];
	p->y = sin(angle * M_PI / 180) * temp[0] + cos(angle * M_PI / 180) * temp[1];
}

extern DirectedLine RGL[4];
extern Car car1[12];

void RunCar(Car car[], int carnum, DirectedLine *startLine[], coordinateSystem *coordinate)
{
    int i, j, k, state, branchNum;
    Point pos;
    for(i = 0; i < carnum; i++)
    {
        if(car[i].visiable == 0)
        {
            k = rand() % 20;
            if(k == 0)
            {
                car[i].nowLine = startLine[rand() % 7];

                pos = posToPoint(car[i].nowLine, car[i].dis);
                MoveCar(&car[i], pos.x, pos.y
                , 180.0 / M_PI * atan2(car[i].nowLine->end.y - car[i].nowLine->start.y
                , car[i].nowLine->end.x - car[i].nowLine->start.x), coordinate);


                state = 0;
                for(j = 0; j < carnum; j++)
                {
                    if(i == j || car1[j].visiable == 0) continue;
                    if(JudgeCarCrash(&(car[i].crashDetecter), &car1[j]))
                    {
                        state = 1;
                        break;
                    }
                }

                if(state == 0)
                {
                    if(rand() % 2 == 0)
                    {
                        InitCar(&car[i]);
                    }
                    else
                    {
                        InitBus(&car[i]);
                    }
                    car[i].visiable = 1;
                    car[i].turn = 0;
                    car[i].color = rand() % 14 + 1;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }

        state = 0;

        for(j = 0; j < carnum; j++)
        {
            if(i == j || car1[j].visiable == 0) continue;
            if(JudgeCarCrash(&(car[i].slowDetecter), &car1[j]))
            {
                if(state == 0)
                {
                    state = 1;
                }
            }
            if(JudgeCarCrash(&(car[i].crashDetecter), &car1[j]))
            {
                state = 2;
                break;
            }
        }

        if(car[i].turn != 3)
        {
            for(j = 0; j < 16; j++)
            {
                if(JudgeCrash(&(car[i].slowDetecter), &RGL[j]))
                {
                    if(state == 0)
                    {
                        state = 1;
                    }
                }
                if(JudgeCrash(&(car[i].crashDetecter), &RGL[j]))
                {
                    state = 2;
                    break;
                }
            }
        }
        

        if(state == 0 && car[i].speed < car[i].maxSpeed)
        {
            car[i].speed += car[i].acc;
        }
        else if(state == 1 && car[i].speed > car[i].slowSpeed)
        {
            car[i].speed -= car[i].acc;
        }else if(state == 2)
        {
            car[i].speed -= 2 * car[i].acc;
            if(car[i].speed < -0.1 * car[i].slowSpeed)
            {
                car[i].speed = -0.1 * car[i].slowSpeed;
            }
        }

        car[i].dis += car[i].speed;

        //carflow[0].carnum++;

        if(car[i].dis > car[i].nowLine->lenth)
        {
            car[i].dis = car[i].dis - car[i].nowLine->lenth;
            
            for(j = 0; j < 4; j++)
            {
                for(k = 0; k < 12; k++)
                {
                    if(car[i].nowLine->end.x == carflow[j].road[k]->end.x
                    && car[i].nowLine->end.y == carflow[j].road[k]->end.y)
                    {
                        carflow[j].carnum++;
                        break;
                    }
                }
            }

            if(car[i].turn == -1)
            {
                car[i].visiable = 0;
                continue;
            }
            else
            {
                if(car[i].turn == 1)
                {
                    car[i].nowLine = car[i].nowLine->straight;
                }
                else if(car[i].turn == 2)
                {
                    car[i].nowLine = car[i].nowLine->left;
                }
                else if(car[i].turn == 3)
                {
                    car[i].nowLine = car[i].nowLine->right;
                }
                car[i].turn = 0;
            }
        }

        if(car[i].turn == 0)
        {
            branchNum = 0;
            if(car[i].nowLine->straight != NULL) branchNum++;
            if(car[i].nowLine->right != NULL) branchNum++;
            if(car[i].nowLine->left != NULL) branchNum++;
            
            if(branchNum == 0)
            {
                car[i].turn = -1;
            }
            else 
            {
                k = rand() % branchNum;
                if(car[i].nowLine->straight != NULL)
                {
                    if(k == 0) car[i].turn = 1;
                    k--;
                }
                if(car[i].nowLine->left != NULL)
                {
                    if(k == 0) car[i].turn = 2;
                    k--;
                }
                if(car[i].nowLine->right != NULL)
                {
                    if(k == 0) car[i].turn = 3;
                    k--;
                }
            }
        }

        pos = posToPoint(car[i].nowLine, car[i].dis);

        MoveCar(&car[i], pos.x, pos.y
        , 180.0 / M_PI * atan2(car[i].nowLine->end.y - car[i].nowLine->start.y
        , car[i].nowLine->end.x - car[i].nowLine->start.x), coordinate);
    }
}