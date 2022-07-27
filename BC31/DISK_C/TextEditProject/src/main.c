#include "TEXTEDIT.H"
#include "Mouse.h"
#include <graphics.h>
#include <string.h>
#include <stdlib.h>

void main()
{
	int driver = VGA;
	int mode = VGAHI;
	TextEdit *textEdit = NewTextEdit(100, 100, 200, 20);
	MouseState *mouse = (MouseState*)malloc(sizeof(MouseState));
	initgraph(&driver, &mode, "C:\\BORLANDC\\BGI");
	setbkcolor(BLACK);
	setviewport(0, 0, 640, 480, 1);
	TextEdit_Init(textEdit);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	setcolor(BLACK);
	MouseInit(mouse);
	
	while(1)
	{
		NewMouse(mouse);
		TextEdit_Update(textEdit);
		if(mouse->mouseClick == 1)
		{
			if(textEdit->left <= mouse->mouseX && mouse->mouseX <= textEdit->left + textEdit->size
			&& textEdit->top <= mouse->mouseY && mouse->mouseY <= textEdit->top + 9)
			{
				textEdit->onFocus = 1;
			}
			else
			{
				textEdit->onFocus = 0;
			}
		}
		if(strcmp(textEdit->text, "exit") == 0)
		{
			break;
		}
	}
	DeleteTextEdit(textEdit);
}