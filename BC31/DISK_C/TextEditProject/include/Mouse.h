#ifndef __Mouse__
#define __Mouse__

typedef struct
{
	int mouseX;
	int mouseY;
	int mouseS;
	//int mouseExist;
	void *buffer;
	int mouseClick;
} MouseState;

void MouseInit(MouseState *mouse);//初始化 
void MouseShape(int mouseX, int mouseY, int mouseS);//告知鼠标形状 
void RegsRead(MouseState *mouse);//得到当前鼠标位置 
void NewMouse(MouseState *mouse);//更新鼠标状态 
void SaveBackImage(MouseState *mouse);//保存鼠标背景位图 
void ClearMouse(int originMouseX, int originMouseY, MouseState *mouse);//清除原有鼠标 
void DrawMouse(MouseState *mouse);//画鼠标 
void MouseClick(MouseState *mouse);


#endif