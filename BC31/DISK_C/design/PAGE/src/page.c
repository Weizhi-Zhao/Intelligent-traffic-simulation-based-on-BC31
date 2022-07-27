#include "includeall.h"

void Useless1(MouseState *mouse, TextEdit *textEdit)

{
	return;
}

void Useless2(MouseState *mouse)
{
	return;
}

void ChangeFlag(MouseState *mouse)
{
	mouse->flag = 1;
}

void ChangeFlag3(MouseState *mouse)
{
	mouse->flag = 3;
}

void ChangeFlag4(MouseState *mouse)
{
	mouse->flag = 4;
}

void ChangeFlag5(MouseState *mouse)
{
	mouse->flag = 5;
}

void ChangeFlag6(MouseState *mouse)
{
	mouse->flag = 6;
}

void ChangeFlag7(MouseState *mouse)
{
	mouse->flag = 7;
}

void main()
{
	MouseState *mouse = malloc(sizeof(MouseState));
    int gdriver = VGA;
    int gmode = VGAHI;
    
    initgraph(&gdriver, &gmode, "c:\\borlandc\\bgi");
    cleardevice();
    setbkcolor(BLACK);
    setfillstyle(SOLID_FILL, GREEN);
    bar(0, 0, 639, 479);
    setviewport(0, 0, 639, 479, 1);
    MouseInit(mouse);
    PageLogin(mouse);
	free(mouse);
}

void DrawBackGround()
{
	int road1[8] = {50, 479, 280, 479, 245, 360, 100, 360};
	int road2[8] = {400, 300, 490, 300, 460, 240, 430, 240};
	//草地
	setfillstyle(SOLID_FILL, GREEN); 
	bar(0, 0, 639, 479);
	//天空 
	setfillstyle(SOLID_FILL, BLUE);
	bar(0, 0, 639, 79);
	setfillstyle(SOLID_FILL, CYAN);
	bar(0, 80, 639, 159);
	setfillstyle(SOLID_FILL, LIGHTCYAN);
	bar(0, 160, 639, 239);
	//太阳 
	setcolor(LIGHTRED);
	setfillstyle(SOLID_FILL, LIGHTRED);
	fillellipse(480, 120, 50, 50);
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	fillellipse(480, 120, 40, 40);
	setlinestyle(SOLID_LINE, 0, 3);
	line(410, 120, 550, 120);
	line(480, 50, 480, 190);
	line(530, 170, 430, 70);
	line(530, 70, 430, 170);
	//云朵1
	setlinestyle(SOLID_FILL, 0, 1);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(118, 178, 213, 208);
	fillellipse(118, 178, 30, 30);
	fillellipse(213, 193, 15, 15);
	fillellipse(158, 148, 35, 35);
	fillellipse(198, 178, 20, 20);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(120, 180, 215, 210);
	fillellipse(120, 180, 30, 30);
	fillellipse(215, 195, 15, 15);
	fillellipse(160, 150, 35, 35);
	fillellipse(200, 180, 20, 20);
	//云朵2 
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(278, 88, 373, 118);
	fillellipse(278, 88, 30, 30);
	fillellipse(373, 103, 15, 15);
	fillellipse(318, 58, 35, 35);
	fillellipse(358, 88, 20, 20);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(280, 90, 375, 120);
	fillellipse(280, 90, 30, 30);
	fillellipse(375, 105, 15, 15);
	fillellipse(320, 60, 35, 35);
	fillellipse(360, 90, 20, 20);
	//道路
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, 300, 639, 360);
	fillpoly(4, road1);
	fillpoly(4, road2);
	//道路边缘
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(LIGHTGRAY);
	line(0, 360, 100, 360);
	line(100, 360, 50, 479);
	line(245, 360, 280, 479);
	line(245, 360, 639, 360);
	
	line(0, 300, 400, 300);
	line(400, 300, 430, 240);
	line(460, 240, 490, 300);
	line(490, 300, 639, 300);
	//道路上画线
	//主路 
	setcolor(WHITE);
	line(0, 330, 40, 330);
	line(70, 330, 113, 330);
	line(235, 330, 250, 330);
	line(280, 330, 320, 330);
	line(350, 330, 385, 330);
	line(505, 330, 530, 330);
	line(560, 330, 600, 330);
	line(630, 330, 639, 330);
	//左辅路 
	line(100, 360, 245, 360);
	line(100, 360, 125, 300);
	line(245, 360, 227, 300);
	
	line(160, 479, 164, 450);
	line(167, 430, 171, 400);
	line(174, 380, 177, 360);
	//右辅路 
	line(400, 300, 490, 300);
	line(400, 300, 375, 360);
	line(490, 300, 520, 360);
	
	line(445, 239, 445, 249);
	line(445, 257, 445, 269);
	line(445, 277, 445, 300);
	//红绿灯
	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, DARKGRAY);
	line(490, 300, 490, 230);
	bar(400, 200, 491, 230);
	setcolor(LIGHTGREEN);
	setfillstyle(SOLID_FILL, LIGHTGREEN);
	fillellipse(416, 215, 13, 13);
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	fillellipse(447, 215, 13, 13);
	setcolor(LIGHTRED);
	setfillstyle(SOLID_FILL, LIGHTRED);
	fillellipse(478, 215, 13, 13);
}

void Exit(MouseState *mouse)
{
	free(mouse);
	exit(0);
}

void PageLogin(MouseState *mouse)
{
	Button button[4];
	TextEdit textEdit[2];
	DrawBackGround();
	puthz(13, 13, "交通智能图形", 48, 45, WHITE);
	puthz(390, 13, "仿真系统", 48, 60, WHITE);
	ButtonAllInit1(button);
	TextEditAllInit1(textEdit);
	SaveBackImage(mouse);
	mouse->flag = 0;
	while(1)
    {
    	mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 4, mouse, textEdit); 
		if(mouse->flag == 2)
		{
			DrawBackGround();
			puthz(13, 13, "交通智能图形", 48, 45, WHITE);
			puthz(390, 13, "仿真系统", 48, 60, WHITE);
			ButtonAllInit1(button);
			TextEditAllInit1(textEdit);
			mouse->flag = 0;
		}	
    	if(bioskey(1))
    	{
    		bioskey(0);
		}
		TextEditStateJudge(textEdit, 2, mouse);
		NewMouse(mouse);
		delay(20);
	}
}

void PageAbout(MouseState *mouse)
{
	Button button[1];
	DrawBackGround();
	settextstyle(TRIPLEX_FONT, 0, 5);
	setcolor(BLACK);
	puthz(13, 13, "关于我们", 48, 45, WHITE);
	puthz(160, 120, "人工智能本硕博", 48, 45, BLACK);
	outtextxy(490, 115, "2101"); 
	puthz(160, 180, "赵为之", 48, 45, BLACK); 
	puthz(330, 180, "谷思田", 48, 45, BLACK); 
	puthz(160, 360, "智能交通图形仿真系统", 48, 45, BLACK);
	ButtonAllInit2(button);
	NewMouse(mouse);
	mouse->flag = 0;
	while(1)
    {
    	mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 1, mouse, NULL);
		if(mouse->flag == 1)
		{
			mouse->flag = 2;
			return;
		}
		NewMouse(mouse);
		delay(20);
	}
}

void PageRegister(MouseState *mouse)
{
	Button button[2];
	TextEdit textEdit[3];
	DrawBackGround();
	puthz(120, 80, "新用户名", 48, 45, BLACK);
	puthz(120, 160, "新密码", 48, 45, BLACK);
	puthz(120, 240, "确认新密码", 48, 45, BLACK);
	ButtonAllInit3(button);
	TextEditAllInit3(textEdit);
	NewMouse(mouse);
	mouse->flag = 0;
	while(1)
    {
    	mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 2, mouse, textEdit);
    	if(bioskey(1))
    	{
    		bioskey(0);
		}
		TextEditStateJudge(textEdit, 3, mouse);		
		if(mouse->flag == 1)
		{
			mouse->flag = 2;
			return;
		}
		NewMouse(mouse);
		delay(20);
	}
}

void PageMain(MouseState *mouse)
{
	Button button[4];
	DrawBackGround();
	puthz(13, 13, "交通智能图形", 48, 45, WHITE);
	puthz(390, 13, "仿真系统", 48, 60, WHITE);
	ButtonAllInit6(button);
	NewMouse(mouse);
	mouse->flag = 0;
	while(1)
    {
    	mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 4, mouse, NULL); 	
    	if(mouse->flag == 2)
    	{
    		DrawBackGround();
			puthz(13, 13, "交通智能图形", 48, 45, WHITE);
			puthz(390, 13, "仿真系统", 48, 60, WHITE);
			ButtonAllInit6(button);
			mouse->flag = 0;
		}
    	if(mouse->flag == 1)
		{
			mouse->flag = 2;
			return;
		}
		NewMouse(mouse);
		delay(20);
	}
}

void PageOriginSettings(MouseState *mouse)
{
	Button button[2];
	TextEdit textEdit[4];
	DrawBackGround();
	puthz(13, 13, "初始设置", 48, 45, WHITE);
	puthz(100, 80, "车辆数量", 48, 45, BLACK);
	puthz(100, 150, "小型车速度", 48, 45, BLACK);
	puthz(100, 220, "大型车速度", 48, 45, BLACK);
	puthz(100, 290, "红绿灯时长", 48, 45, WHITE);
	ButtonAllInit5(button);
	TextEditAllInit5(textEdit);
	NewMouse(mouse);
	mouse->flag = 0;
	while(1)
    {
    	mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 2, mouse, textEdit); 
		if(mouse->flag == 2)
    	{
    		DrawBackGround();
			puthz(13, 13, "初始设置", 48, 45, WHITE);
			puthz(100, 80, "车辆数量", 48, 45, BLACK);
			puthz(100, 150, "小型车速度", 48, 45, BLACK);
			puthz(100, 220, "大型车速度", 48, 45, BLACK);
			puthz(100, 290, "红绿灯时长", 48, 45, WHITE);
			ButtonAllInit5(button);
			TextEditAllInit5(textEdit);
			mouse->flag = 0;
		}	
    	if(bioskey(1))
    	{
    		bioskey(0);
		}
		TextEditStateJudge(textEdit, 4, mouse);
		if(mouse->flag == 1)
		{
			mouse->flag = 2;
			return;
		}
		NewMouse(mouse);
		delay(20);
	}
}

void PageSettings(MouseState *mouse)
{
	Button button[2];
	TextEdit textEdit[4];
	DrawBackGround();
	puthz(13, 13, "修改模拟设置", 48, 45, WHITE);
	puthz(100, 80, "车辆数量", 48, 45, BLACK);
	puthz(100, 150, "小型车速度", 48, 45, BLACK);
	puthz(100, 220, "大型车速度", 48, 45, BLACK);
	puthz(100, 290, "红绿灯时长", 48, 45, WHITE);
	ButtonAllInit7(button);
	TextEditAllInit7(textEdit);
	NewMouse(mouse);
	while(1)
    {
    	mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 2, mouse, textEdit); 	
    	if(bioskey(1))
    	{
    		bioskey(0);
		}
		TextEditStateJudge(textEdit, 4, mouse);
		if(mouse->flag == 1)
		{
			mouse->flag = 0;
			return;
		}
		NewMouse(mouse);
		delay(20);
	}
}

void PageHistory(MouseState *mouse)
{
	FILE *fp;
	int i;
	char *text;
	int carNum[4] = {0};
	float carSpeed[4] = {0};
	float busSpeed[4] = {0};
	int lightTime[4] = {0};
	Button button[5];
	
	if((fp = fopen("c:\\design\\page\\file\\hisinfo", "r")) == NULL)
	{
		printf("Error on opening file!\n");
		exit(1);
	}
	DrawBackGround();
	puthz(13, 13, "历史记录", 48, 45, WHITE);
	
	i = 0;
	while(fread(&carNum[i], sizeof(int), 1, fp) != 0)
	{
		fread(&carSpeed[i], sizeof(float), 1, fp);
		fread(&busSpeed[i], sizeof(float), 1, fp);
		fread(&lightTime[i], sizeof(int), 1, fp);
		i++;
		if(i == 4) i = 0;
	}
	setfillstyle(SOLID_FILL, LIGHTCYAN);
	bar(0, 65, 639, 380);
	puthz(10, 80, "车辆数量", 32, 30, BLACK);
	puthz(140, 80, "小型车速", 32, 30, BLACK);
	puthz(280, 80, "大型车速", 32, 30, BLACK);
	puthz(430, 80, "灯周期", 32, 30, BLACK);
	setcolor(BLACK);
	settextstyle(TRIPLEX_FONT, 0, 5);
	for(i = 0;i < 4;i++)
	{
		if(carNum[i] == 0)
		{
			break;
		}
		outtextxy(50, 120 + i * 60, itoa(carNum[i], text, 10));
		outtextxy(190, 120 + i * 60, itoa((int)carSpeed[i], text, 10));
		outtextxy(330, 120 + i * 60, itoa((int)busSpeed[i], text, 10));
		outtextxy(450, 120 + i * 60, itoa(lightTime[i], text, 10));
	}
	ButtonAllInit7(button);
	NewMouse(mouse);
	while(1)
    {
    	mouse->mouseS = 0;
    	ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
    	ButtonStateJudge(button, 5, mouse, NULL); 	
    	if(mouse->flag == 2)
    	{
    		DrawBackGround();
			setfillstyle(SOLID_FILL, LIGHTCYAN);
			bar(0, 65, 639, 380);
			puthz(10, 80, "车辆数量", 32, 30, BLACK);
			puthz(140, 80, "小型车速", 32, 30, BLACK);
			puthz(280, 80, "大型车速", 32, 30, BLACK);
			puthz(430, 80, "灯周期", 32, 30, BLACK);
			setcolor(BLACK);
			settextstyle(TRIPLEX_FONT, 0, 5);
			for(i = 0;i < 4;i++)
			{
				if(carNum[i] == 0)
				{
					break;
				}
				outtextxy(50, 120 + i * 60, itoa(carNum[i], text, 10));
				outtextxy(190, 120 + i * 60, itoa((int)carSpeed[i], text, 10));
				outtextxy(330, 120 + i * 60, itoa((int)busSpeed[i], text, 10));
				outtextxy(450, 120 + i * 60, itoa(lightTime[i], text, 10));
			}
			ButtonAllInit7(button);
			mouse->flag = 0;
		}	
    	if(bioskey(1))
    	{
    		bioskey(0);
		}
		
		if(mouse->flag != 0 && mouse->flag != 1)
		{
			i = mouse->flag;
			mouse->flag = 0;
			ThreeDMain(mouse, lightTime[i - 3], carNum[i - 3], carSpeed[i - 3] / 15, busSpeed[i - 3] / 15);
		}
		if(mouse->flag == 1)
		{
			mouse->flag = 2;
			return;
		}
		NewMouse(mouse);
		delay(20);
	}
}
