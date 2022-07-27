#ifndef __Mouse1_H__
#define __Mouse1_H__

typedef struct
{
	int mouseX;
	int mouseY;
	int mouseS;
	void *buffer;
	int mouseClick;
	int flag;//0Ϊѭ��̬��1Ϊ����̬��2Ϊ�ػ�̬ 
} MouseState;

int Max(int a, int b);


int Min(int a, int b);


void MouseInit(MouseState *mouse);//��ʼ�� 


void MouseShape(int mouseX, int mouseY, int mouseS);//��֪�����״ 


void RegsRead(MouseState *mouse);//�õ���ǰ���λ�� 


void NewMouse(MouseState *mouse);//�������״̬ 


void SaveBackImage(MouseState *mouse);//������걳��λͼ 


void ClearMouse(int originMouseX, int originMouseY, MouseState *mouse);//���ԭ����� 


void DrawMouse(MouseState *mouse);//����� 


void MouseClick(MouseState *mouse);

#endif
