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
	int funcJudge; //�жϴ�����һ�ֺ���ָ�� ��1�򴫵��������ı���2�򴫵����������ı��� 
	int flag;//��һ�㺯��״̬ 
	void (*pFun1)(MouseState*, TextEdit*);//��Ҫ�����ı���İ�ť�ĺ���ָ�� 
	void (*pFun2)(MouseState*);//���������ı���İ�ť�ĺ���ָ�� 
} Button;

//��¼���水ť��ʼ�� 
void ButtonAllInit1(Button button[]);

//���ڽ��水ť��ʼ�� 
void ButtonAllInit2(Button button[]);

//ע����水ť��ʼ�� 
void ButtonAllInit3(Button button[]);

//��ʼ���ý��水ť��ʼ�� 
void ButtonAllInit5(Button button[]);

//�����水ť��ʼ�� 
void ButtonAllInit6(Button button[]);

//��ʷ��¼���水ť��ʼ�� 
void ButtonAllInit7(Button button[]); 

//ģ����水ť��ʼ��
void ButtonAllInit8(Button button[]); 

void ButtonStateJudge(Button button[], int num, MouseState *mouse, TextEdit *textEdit);

void DrawButton(Button *button);

void ButtonInit(Button *button, int length, int width, int cenX, int cenY, char text[], void (*fun1)(MouseState*, TextEdit*), void (*fun2)(MouseState*), int funcJudge);

void ButtonStateChange(Button *but, MouseState *mp, TextEdit *textEdit);

void Draw();
#endif
