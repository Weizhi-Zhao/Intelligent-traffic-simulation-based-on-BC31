#include "includeall.h"

void ThreeDInit(MouseState *mouse, TextEdit *textEdit)
{
	FILE *fp;
	int carNum = atoi(textEdit[0].text), lightTime = atoi(textEdit[3].text);
	float carSpeed  = atof(textEdit[1].text), busSpeed = atof(textEdit[2].text);
	
	if(strlen(textEdit[0].text) == 0 || strlen(textEdit[1].text) == 0 || strlen(textEdit[2].text) == 0 || strlen(textEdit[3].text) == 0)
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 380, 679, 423); 
		puthz(320, 380, "输入不能为空！", 32, 40, WHITE);
		return;
	}
	if(carNum > 12)
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 380, 679, 423); 
		puthz(320, 380, "车辆最多十二辆！", 32, 40, WHITE);
		return;
	}
	if(carSpeed > 60)
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 380, 679, 423); 
		puthz(320, 380, "小型车速度最快六十千米每时！", 32, 25, WHITE);
		return;
	}
	if(busSpeed > 60)
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 380, 679, 423); 
		puthz(320, 380, "大型车速度最快六十千米每时！", 32, 25, WHITE);
		return;
	}
	if((fp = fopen("c:\\design\\page\\file\\hisinfo", "ab")) == NULL)
	{
		printf("Error on opening file!\n");
		exit(1);
	}
	fwrite(&carNum, sizeof(int), 1, fp);
	fwrite(&carSpeed, sizeof(float), 1, fp);
	fwrite(&busSpeed, sizeof(float), 1, fp);
	fwrite(&lightTime, sizeof(int), 1, fp);
	fclose(fp);
	ThreeDMain(mouse, atoi(textEdit[3].text), atoi(textEdit[0].text), atof(textEdit[1].text) / 15, atof(textEdit[2].text) / 15);
}

void ThreeDMain(MouseState *mouse, int lightTime, int carNum, float carSpeed, float busSpeed)
{
	char timeCounter[4];
    int i, j, k;
    Queue *connectionQueue = newQueue(deleteConnection);
    Queue *signalQueue = newQueue(deleteSignal);
	coordinateSystem coordinate;
    Button button[1];
    
    Connection *c = newConnection("keyboard", &coordinate, ChangeView);
    queuePush(connectionQueue, c);
    c = newConnection("keyboard", &coordinate, FocusChange);
    queuePush(connectionQueue, c);
    c = newConnection("keyboard", &coordinate, ZoomInAndOut);
    queuePush(connectionQueue, c);

	for(i = 0; i < 12; i++)
	{
		InitBus(&car1[i], busSpeed);
		
		car1[i].visiable = 0;
		car1[i].dis = 0;
		car1[i].nowLine = startLine[i % 7];
		
	}
   
    CoordinateInit(&coordinate);
	coordinate.maganification = 5;
    VectorSet(coordinate.eye, 10, 10, 10, 1);
    
    CalUVN(&coordinate);
    
	GiveUnit(&coordinate);

	DrawRoad(Road);
	InitLine();
	ConnectLine();

	srand(time(0));

	InitTrafficLight(&trafficLight[0], -5, -5, RGL, lightTime);
	InitTrafficLight(&trafficLight[1], -5, 55, RGL + 4, lightTime);
	InitTrafficLight(&trafficLight[2], 55, -5, RGL + 8, lightTime);
	InitTrafficLight(&trafficLight[3], 55, 55, RGL + 12, lightTime);

	InitCarflow(&carflow[0], lineCS[0], lineCL[0], lineCR[0], 60);
	InitCarflow(&carflow[1], lineCS[1], lineCL[1], lineCR[1], 60);
	InitCarflow(&carflow[2], lineCS[2], lineCL[2], lineCR[2], 60);
	InitCarflow(&carflow[3], lineCS[3], lineCL[3], lineCR[3], 60);
	
	ButtonAllInit8(button);
	NewMouse(mouse);

    while(1)
    {
    	clearFrameBuffer();
		
		for(i = 0; i < 15; i++)
		{
			for(j = 0; j < 8; j++)
			{
				VectorSet(Road[i].finalCoordinate[j], 0, 0, 0, 0);
				CoordinateChange(Road[i].originCoordinate[j], coordinate.change, Road[i].finalCoordinate[j]);
			}
			VectorSet(Road[i].finalCentrePosition, 0, 0, 0, 0);
			Road[i].centrePosition[3] = 1;
			CoordinateChange(Road[i].centrePosition, coordinate.change, Road[i].finalCentrePosition);
		}

		for(i = 0; i < 11; i++)
		{
			for(j = 0; j < 8; j++)
			{
				VectorSet(yellowLine[i].finalCoordinate[j], 0, 0, 0, 0);
				CoordinateChange(yellowLine[i].originCoordinate[j], coordinate.change, yellowLine[i].finalCoordinate[j]);
			}
			VectorSet(yellowLine[i].finalCentrePosition, 0, 0, 0, 0);
			yellowLine[i].centrePosition[3] = 1;
			CoordinateChange(yellowLine[i].centrePosition, coordinate.change, yellowLine[i].finalCentrePosition);
		}

		SortRoad(Road);

		for(i = 0; i < 15; i++)
		{
			ConnectDots(&Road[i], &coordinate, 14, 15);
		}

		for(i = 0; i < 11; i++)
		{
			ConnectDots(&yellowLine[i], &coordinate, 7, 7);
		}

		RunCar(car1, carNum, carSpeed, busSpeed, startLine, &coordinate);

		for(i = 0; i < 12; i++)
		{
			if(car1[i].visiable)
			{
				DrawCar(&car1[i], &coordinate);
			}
		}

		for(i = 0; i < 4; i++) 
		{
			DrawTrafficLight(&trafficLight[i], &coordinate);
		}
		
		settextstyle(0, 0, 0);
	    detectKeyBoard(signalQueue);
	    showFrameBuffer();
		
		mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 2, mouse, NULL); 	
    	DrawButton(&button[0]);
		if(mouse->flag == 1)
		{
			mouse->flag = 2;
			triggerSignal(connectionQueue, signalQueue);
			break;
		}
		NewMouse(mouse);
		
		for(i = 0; i < 4; i++) 
		{
			itoa(trafficLight[i].timeCounter, timeCounter, 10);
			settextstyle(0, 0, 2);
			outtextxy(trafficLight[i].light[2].finalCentrePosition[0] * coordinate.maganification + 320
			, trafficLight[i].light[2].finalCentrePosition[1] * coordinate.maganification + 210
			, timeCounter);

			ShowCarnum(&carflow[i]
			, trafficLight[i].light[2].finalCentrePosition[0] * coordinate.maganification + 320
			, trafficLight[i].light[2].finalCentrePosition[1] * coordinate.maganification + 180);
		}
		triggerSignal(connectionQueue, signalQueue);
	}
	deleteQueue(signalQueue);
	deleteQueue(connectionQueue);
	return;
}
