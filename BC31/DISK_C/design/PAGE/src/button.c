#include "includeall.h"

//登录界面 
void ButtonAllInit1(Button button[])
{
	ButtonInit(&(button[0]), 60, 50, 220, 400, "注册", Useless1, PageRegister, 2);
	ButtonInit(&(button[1]), 60, 50, 420, 400, "登录", LoginOK, Useless2, 1);
	ButtonInit(&(button[2]), 60, 50, 580, 450, "关于", Useless1, PageAbout, 2); 
	ButtonInit(&(button[3]), 60, 50, 60, 450, "退出", Useless1, Exit, 2);
}

//关于界面 
void ButtonAllInit2(Button button[])
{
	ButtonInit(&(button[0]), 60, 50, 60, 450, "返回", Useless1, ChangeFlag, 2); 
}

//注册界面 
void ButtonAllInit3(Button button[])
{
	ButtonInit(&(button[0]), 60, 50, 60, 450, "返回", Useless1, ChangeFlag, 2);
	ButtonInit(&(button[1]), 60, 50, 580, 450, "确定", RegisterOK, Useless2, 1);
} 

//初始设置界面
void ButtonAllInit5(Button button[])
{
	ButtonInit(&(button[0]), 135, 50, 540, 450, "进入模拟", ThreeDInit, Useless2, 1);
	ButtonInit(&(button[1]), 60, 50, 60, 450, "返回", Useless1, ChangeFlag, 2);
}

//主界面
void ButtonAllInit6(Button button[])
{
	ButtonInit(&(button[0]), 135, 50, 320, 160, "开始模拟", Useless1, PageOriginSettings, 2);
	ButtonInit(&(button[1]), 135, 50, 320, 220, "历史记录", Useless1, PageHistory, 2);
	ButtonInit(&(button[2]), 135, 50, 320, 280, "退出登录", Useless1, ChangeFlag, 2); 
	ButtonInit(&(button[3]), 135, 50, 320, 340, "退出系统", Useless1, Exit, 2);
}

//历史记录界面 
void ButtonAllInit7(Button button[])
{
	ButtonInit(&(button[0]), 60, 50, 60, 450, "返回", Useless1, ChangeFlag, 2);
	ButtonInit(&(button[1]), 60, 50, 570, 145, "选择", Useless1, ChangeFlag3, 2);
	ButtonInit(&(button[2]), 60, 50, 570, 205, "选择", Useless1, ChangeFlag4, 2);
	ButtonInit(&(button[3]), 60, 50, 570, 265, "选择", Useless1, ChangeFlag5, 2);
	ButtonInit(&(button[4]), 60, 50, 570, 325, "选择", Useless1, ChangeFlag6, 2);
}

//模拟界面按钮初始化
void ButtonAllInit8(Button button[])
{
	ButtonInit(&(button[0]), 135, 50, 540, 450, "结束模拟", Useless1, ChangeFlag, 2);
}

void ButtonInit(Button *button, int length, int width, int cenX, int cenY, char text[], void (*fun1)(MouseState*, TextEdit*), void (*fun2)(MouseState*), int funcJudge)
{
	button->centrePosi[0] = cenX; button->centrePosi[1] = cenY;
	button->length = length; button->width = width;
	button->text = text;
	button->state = 0;
	button->funcJudge = funcJudge;
	button->flag = 0; 
	
	if(button->funcJudge == 2)
	{
		button->pFun2 = fun2;
		button->pFun1 = Useless1;
	}
	else
	{
		button->pFun1 = fun1;
		button->pFun2 = Useless2;
	}
	
	DrawButton(button);
}

void DrawButton(Button *button)
{
	if(button->state == 0)//无状态 
	{
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		bar(button->centrePosi[0] - button->length / 2, button->centrePosi[1] - button->width / 2, button->centrePosi[0] + button->length / 2, button->centrePosi[1] + button->width / 2);
		fillellipse(button->centrePosi[0] - button->length / 2, button->centrePosi[1], button->width / 2 - 1, button->width / 2 - 1);
		fillellipse(button->centrePosi[0] + button->length / 2, button->centrePosi[1], button->width / 2 - 1, button->width / 2 - 1); 
		puthz(button->centrePosi[0] - button->length / 2 + button->width / 5 - 16, button->centrePosi[1] - 16, button->text, 32, 39, BLACK);
	}
	else if(button->state == 1)//鼠标移至上方 
	{
		setcolor(LIGHTGRAY);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(button->centrePosi[0] - button->length / 2, button->centrePosi[1] - button->width / 2, button->centrePosi[0] + button->length / 2, button->centrePosi[1] + button->width / 2);
		fillellipse(button->centrePosi[0] - button->length / 2, button->centrePosi[1], button->width / 2 - 1, button->width / 2 - 1);
		fillellipse(button->centrePosi[0] + button->length / 2, button->centrePosi[1], button->width / 2 - 1, button->width / 2 - 1);
		puthz(button->centrePosi[0] - button->length / 2 + button->width / 5 - 16, button->centrePosi[1] - 16, button->text, 32, 39, BLACK);
	}
	else if(button->state == 2)//鼠标左键点击
	{
		setcolor(DARKGRAY);
		setfillstyle(SOLID_FILL, DARKGRAY);
		bar(button->centrePosi[0] - button->length / 2, button->centrePosi[1] - button->width / 2, button->centrePosi[0] + button->length / 2, button->centrePosi[1] + button->width / 2);
		fillellipse(button->centrePosi[0] - button->length / 2, button->centrePosi[1], button->width / 2 - 1, button->width / 2 - 1);
		fillellipse(button->centrePosi[0] + button->length / 2, button->centrePosi[1], button->width / 2 - 1, button->width / 2 - 1);
		puthz(button->centrePosi[0] - button->length / 2 + button->width / 5 - 16, button->centrePosi[1] - 16, button->text, 32, 39, BLACK);
	}
}

void ButtonStateJudge(Button button[], int num, MouseState *mouse, TextEdit *textEdit)
{
	int i;
	
	for(i = 0;i < num;i++)
	{
		ButtonStateChange(&(button[i]), mouse, textEdit);
	}
}

void ButtonStateChange(Button *but, MouseState *mp, TextEdit *textEdit)
{
	int originButState; 
	originButState = but->state;
	if((mp->mouseX > (but->centrePosi[0] - but->length / 2) && mp->mouseX < (but->centrePosi[0] + but->length / 2) && mp->mouseY > (but->centrePosi[1] - but->width / 2) && mp->mouseY < (but->centrePosi[1] + but->width / 2) ||
	   mp->mouseX > (but->centrePosi[0] - but->length / 2 - but->width / 2) && mp->mouseX < (but->centrePosi[0] - but->length / 2) && mp->mouseY > (but->centrePosi[1] - but->width / 2) && mp->mouseY < (but->centrePosi[1] + but->width / 2) && sqrt(pow(mp->mouseX - (but->centrePosi[0] - but->length / 2), 2) + pow(mp->mouseY - but->centrePosi[1], 2)) <= but->width / 2 ||
	   mp->mouseX > (but->centrePosi[0] + but->length / 2) && mp->mouseX < (but->centrePosi[0] + but->length / 2 + but->width / 2) && mp->mouseY > (but->centrePosi[1] - but->width / 2) && mp->mouseY < (but->centrePosi[1] + but->width / 2) && sqrt(pow(mp->mouseX - (but->centrePosi[0] + but->length / 2), 2) + pow(mp->mouseY - but->centrePosi[1], 2)) <= but->width / 2) &&
	   mp->mouseClick == 0)
	{
		mp->mouseS = 1;
		but->state = 1;
	}
	else if((mp->mouseX > (but->centrePosi[0] - but->length / 2) && mp->mouseX < (but->centrePosi[0] + but->length / 2) && mp->mouseY > (but->centrePosi[1] - but->width / 2) && mp->mouseY < (but->centrePosi[1] + but->width / 2) ||
			mp->mouseX > (but->centrePosi[0] - but->length / 2 - but->width / 2) && mp->mouseX < (but->centrePosi[0] - but->length / 2) && mp->mouseY > (but->centrePosi[1] - but->width / 2) && mp->mouseY < (but->centrePosi[1] + but->width / 2) && sqrt(pow(mp->mouseX - (but->centrePosi[0] - but->length / 2), 2) + pow(mp->mouseY - but->centrePosi[1], 2)) <= but->width / 2 ||
			mp->mouseX > (but->centrePosi[0] + but->length / 2) && mp->mouseX < (but->centrePosi[0] + but->length / 2 + but->width / 2) && mp->mouseY > (but->centrePosi[1] - but->width / 2) && mp->mouseY < (but->centrePosi[1] + but->width / 2) && sqrt(pow(mp->mouseX - (but->centrePosi[0] + but->length / 2), 2) + pow(mp->mouseY - but->centrePosi[1], 2)) <= but->width / 2) &&
			mp->mouseClick == 1)
	{
		mp->mouseClick = 0;
		mp->mouseS = 1;
		but->state = 2;
		DrawButton(but);
		delay(40);
		if(but->funcJudge == 2)
		{
			but->pFun2(mp);
		}
		else
		{
			but->pFun1(mp, textEdit);
		}
	}
	else
	{
		but->state = 0;
	}
	if(but->state != originButState)
	{
		DrawButton(but);
	}
}

void Draw()
{
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 50, 50);
}
