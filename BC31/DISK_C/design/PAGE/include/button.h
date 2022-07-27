#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "includeall.h"

typedef struct
{
	int length;
	int width;
	int centrePosi[2];
	char *text;
	int state;
	int funcJudge; //判断传递哪一种函数指针 （1则传递需连接文本框，2则传递无需连接文本框） 
	int flag;//上一层函数状态 
	void (*pFun1)(MouseState*, TextEdit*);//需要连接文本框的按钮的函数指针 
	void (*pFun2)(MouseState*);//无需连接文本框的按钮的函数指针 
} Button;

//登录界面按钮初始化 
void ButtonAllInit1(Button button[]);

//关于界面按钮初始化 
void ButtonAllInit2(Button button[]);

//注册界面按钮初始化 
void ButtonAllInit3(Button button[]);

//初始设置界面按钮初始化 
void ButtonAllInit5(Button button[]);

//主界面按钮初始化 
void ButtonAllInit6(Button button[]);

//历史记录界面按钮初始化 
void ButtonAllInit7(Button button[]); 

//模拟界面按钮初始化
void ButtonAllInit8(Button button[]); 

void ButtonStateJudge(Button button[], int num, MouseState *mouse, TextEdit *textEdit);

void DrawButton(Button *button);

void ButtonInit(Button *button, int length, int width, int cenX, int cenY, char text[], void (*fun1)(MouseState*, TextEdit*), void (*fun2)(MouseState*), int funcJudge);

void ButtonStateChange(Button *but, MouseState *mp, TextEdit *textEdit);

void Draw();
#endif
