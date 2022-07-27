#include "TextEdit.h"
#include <stdlib.h>
#include <graphics.h>
#include <bios.h>

TextEdit *NewTextEdit(int left, int top, int size, int maxLenth)
{
    TextEdit *textEdit = (TextEdit*)malloc(sizeof(TextEdit));
    textEdit->left = left;
    textEdit->top = top;
	textEdit->size = size;
    textEdit->maxLenth = maxLenth;
    textEdit->onFocus = 0;
    textEdit->text = (char*)malloc(sizeof(char) * (maxLenth + 1));
    textEdit->textIterator = textEdit->text;
	textEdit->text[0] = '\0';
    return textEdit;
}

void TextEdit_Init(TextEdit *textEdit)
{
	//设置文本框颜色
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	//绘制文本框
    bar(textEdit->left, textEdit->top, textEdit->left + textEdit->size - 1, textEdit->top + 9);
}

void TextEdit_Update(TextEdit *textEdit)
{
	int letter;
	if(textEdit->onFocus == 1)//如果处于被编辑状态
	{
		if(bioskey(1))//如果已经按下按键
		{
			letter = bioskey(0);//读取该按键
			if(letter == 0x0e08)//如果按下的时backspace键
			{
				if(textEdit->textIterator > textEdit->text)//如果字符串不为空
				{
					TextEdit_Init(textEdit);
					textEdit->textIterator--;
					*(textEdit->textIterator) = '\0';//删除一个字符
					outtextxy(textEdit->left + 2, textEdit->top + 2, textEdit->text);//绘制文字
				}
			}
			else if(textEdit->textIterator - textEdit->text < textEdit->maxLenth)//未超出最大长度
			{
				*(textEdit->textIterator) = letter;
				(textEdit->textIterator)++;
				*(textEdit->textIterator) = '\0';
				outtextxy(textEdit->left + 2, textEdit->top + 2, textEdit->text);//绘制文字
			}
		}
	}
	else
	{
		if(bioskey(1))//如果已经按下按键
		{
			letter = bioskey(0);
		}
	}
}

void DeleteTextEdit(TextEdit *textEdit)
{
	//先删除文本
    free(textEdit->text);
    //再删除textEdit
	free(textEdit);
}