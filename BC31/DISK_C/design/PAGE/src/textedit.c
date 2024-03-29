#include "includeall.h"

//登录页文本框 
void TextEditAllInit1(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 170, 50, 320, 240, "用户名", 0);
	TextEditInit(&(textEdit[1]), 170, 50, 320, 320, "密码", 1);
}

//注册页文本框 
void TextEditAllInit3(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 190, 50, 480, 100, "输入新用户名", 0);
	TextEditInit(&(textEdit[1]), 190, 50, 480, 180, "输入密码", 0);
	TextEditInit(&(textEdit[2]), 190, 50, 480, 260, "输入确认密码", 0); 
}

//初始设置页文本框
void TextEditAllInit5(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 190, 50, 480, 100, "输入车辆数量", 0);
	TextEditInit(&(textEdit[1]), 190, 50, 480, 170, "输入小型车速度", 0);
	TextEditInit(&(textEdit[2]), 190, 50, 480, 240, "输入大型车速度", 0);
	TextEditInit(&(textEdit[3]), 190, 50, 480, 310, "输入红绿灯时长", 0); 
}

//设置页文本框 
void TextEditAllInit7(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 190, 50, 480, 100, "输入车辆数量", 0);
	TextEditInit(&(textEdit[1]), 190, 50, 480, 170, "输入小型车速度", 0);
	TextEditInit(&(textEdit[2]), 190, 50, 480, 240, "输入大型车速度", 0);
	TextEditInit(&(textEdit[3]), 190, 50, 480, 310, "输入红绿灯时长", 0); 
}


void TextEditInit(TextEdit *textEdit, int length, int width, int cenX, int cenY, char *originText, int password)
{
	textEdit->centrePosi[0] = cenX; textEdit->centrePosi[1] = cenY;
	textEdit->length = length; textEdit->width = width;
	textEdit->state = 0;
	textEdit->originText = originText;
	textEdit->onFocus = 0;
//	textEdit->text = malloc(sizeof(char) * 11);
	textEdit->text[0] = '\0';
	textEdit->textIterator = textEdit->text;
	textEdit->maxLength = 10;
	textEdit->password = password;
//	puthz(textEdit->centrePosi[0] - textEdit->length / 2 + textEdit->width / 5 - 16, textEdit->centrePosi[1] - 16, originText, 32, 30, LIGHTGRAY);
	
	DrawTextEdit(textEdit);
}

void TextEditStateJudge(TextEdit textEdit[], int num, MouseState *mouse)
{
	int i;
	
	for(i = 0;i < num;i++)
	{
		TextEditStateChange(&(textEdit[i]), mouse);
	}
}

void TextEditStateChange(TextEdit *textEdit, MouseState *mp)
{
	int originTextEditState; 
	originTextEditState = textEdit->state;
	if((mp->mouseX > (textEdit->centrePosi[0] - textEdit->length / 2) && mp->mouseX < (textEdit->centrePosi[0] + textEdit->length / 2) && mp->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mp->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) ||
	   mp->mouseX > (textEdit->centrePosi[0] - textEdit->length / 2 - textEdit->width / 2) && mp->mouseX < (textEdit->centrePosi[0] - textEdit->length / 2) && mp->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mp->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) && sqrt(pow(mp->mouseX - (textEdit->centrePosi[0] - textEdit->length / 2), 2) + pow(mp->mouseY - textEdit->centrePosi[1], 2)) <= textEdit->width / 2 ||
	   mp->mouseX > (textEdit->centrePosi[0] + textEdit->length / 2) && mp->mouseX < (textEdit->centrePosi[0] + textEdit->length / 2 + textEdit->width / 2) && mp->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mp->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) && sqrt(pow(mp->mouseX - (textEdit->centrePosi[0] + textEdit->length / 2), 2) + pow(mp->mouseY - textEdit->centrePosi[1], 2)) <= textEdit->width / 2) &&
	   mp->mouseClick == 0)
	{
		mp->mouseS = 2;
		textEdit->state = 1;
	}
	else if((mp->mouseX > (textEdit->centrePosi[0] - textEdit->length / 2) && mp->mouseX < (textEdit->centrePosi[0] + textEdit->length / 2) && mp->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mp->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) ||
			mp->mouseX > (textEdit->centrePosi[0] - textEdit->length / 2 - textEdit->width / 2) && mp->mouseX < (textEdit->centrePosi[0] - textEdit->length / 2) && mp->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mp->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) && sqrt(pow(mp->mouseX - (textEdit->centrePosi[0] - textEdit->length / 2), 2) + pow(mp->mouseY - textEdit->centrePosi[1], 2)) <= textEdit->width / 2 ||
			mp->mouseX > (textEdit->centrePosi[0] + textEdit->length / 2) && mp->mouseX < (textEdit->centrePosi[0] + textEdit->length / 2 + textEdit->width / 2) && mp->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mp->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) && sqrt(pow(mp->mouseX - (textEdit->centrePosi[0] + textEdit->length / 2), 2) + pow(mp->mouseY - textEdit->centrePosi[1], 2)) <= textEdit->width / 2) &&
			mp->mouseClick == 1)
	{
		mp->mouseS = 2;
		textEdit->state = 2;
		DrawTextEdit(textEdit);
//		NewMouse(mp); 
		BeginType(textEdit, mp);
	}
	else
	{
		textEdit->state = 0;
	}
	if(textEdit->state != originTextEditState)
	{
		DrawTextEdit(textEdit);
	}
}

void DrawTextEdit(TextEdit *textEdit)
{
	if(textEdit->state == 0 && textEdit->text[0] == '\0')//鼠标移开且无文字 
	{
		setcolor(LIGHTGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
		fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 - 1, textEdit->width / 2 - 1);
		fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 - 1, textEdit->width / 2 - 1); 
		
		puthz(textEdit->centrePosi[0] - textEdit->length / 2 + textEdit->width / 5 - 16, textEdit->centrePosi[1] - 16, textEdit->originText, 32, 30, LIGHTGRAY);
	}
	else if(textEdit->state == 1 && textEdit->text[0] == '\0')//鼠标停留在上方且无文字 
	{
		setcolor(DARKGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
		fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 - 1, textEdit->width / 2 - 1);
		fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 - 1, textEdit->width / 2 - 1);
		puthz(textEdit->centrePosi[0] - textEdit->length / 2 + textEdit->width / 5 - 16, textEdit->centrePosi[1] - 16, textEdit->originText, 32, 30, LIGHTGRAY);
	}
	else if(textEdit->state == 1 && textEdit->text[0] != '\0')//鼠标停留在上方且有文字 
	{
		setcolor(DARKGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
	}
	else if(textEdit->state == 2 && textEdit->text[0] == '\0')//鼠标点击且无文字 
	{
		setcolor(DARKGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
		fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 - 1, textEdit->width / 2 - 1);
		fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 - 1, textEdit->width / 2 - 1);
	}
	else if(textEdit->state == 2 && textEdit->text[0] != '\0')//鼠标点击且有文字 
	{
		setcolor(DARKGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
	}
	else if(textEdit->state == 0 && textEdit->text[0] != '\0')//鼠标移开且有文字 
	{
		setcolor(LIGHTGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
	}
}

void BeginType(TextEdit *textEdit, MouseState *mouse)
{
	int letter, i;
	char *password;
	strcpy(password, "\0");
	settextstyle(TRIPLEX_FONT, 0, 4);
	setfillstyle(SOLID_FILL, WHITE);
	setcolor(WHITE);
	NewMouse(mouse);//
	mouse->flag = 0;
	while(1)
	{
		ClearMouse(mouse->mouseX, mouse->mouseY, mouse);
		if(bioskey(1))//婵″倹鐏夊鑼病閹稿绗呴幐澶愭暛
		{
			letter = bioskey(0);//鐠囪褰囩拠銉﹀瘻闁�?
			if(letter == 0x0e08)//婵″倹鐏夐幐澶夌瑓閻ㄥ嫭妞俠ackspace闁�?
			{
				if(textEdit->textIterator > textEdit->text)//婵″倹鐏夌�涙顑佹稉韫瑝娑撹櫣鈹�
				{
					fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
					fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
					bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
					textEdit->textIterator--;
					*(textEdit->textIterator) = '\0';//閸掔娀娅庢稉鈧稉顏勭摟缁�?
					if(textEdit->text[0] != '\0' && textEdit->password == 0)
					{
						outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, strcat(textEdit->text, "|"));//缂佹ê鍩楅弬鍥х摟
					}
					else if(textEdit->text[0] != '\0' && textEdit->password != 0)
					{
						for(i = 0;i < strlen(textEdit->text);i++)
						{
							strcat(password, "*");
						}
						outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, strcat(password, "|"));
						strcpy(password, "\0");
					}
				}
			}
			else if(letter != 0x1c0d && letter != 0x0e08 && strlen(textEdit->text) < textEdit->maxLength)//閺堫亣绉撮崙鐑樻付婢堆囨毐鎼�?
			{
				fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
				fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
				bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
				*(textEdit->textIterator) = letter;
				(textEdit->textIterator)++;
				*(textEdit->textIterator) = '\0';
				if(textEdit->password == 0)
				{
					outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, strcat(textEdit->text, "|"));//缂佹ê鍩楅弬鍥х摟
				}
				else if(textEdit->password != 0)
				{
					for(i = 0;i < strlen(textEdit->text);i++)
					{
						strcat(password, "*");
					}
					outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, strcat(password, "|"));
					strcpy(password, "\0");
				}
			}
			//若在外部按下鼠标左键或回车 
		   	else if(letter == 0x1c0d)
		   	{
	   			textEdit->state = 0;
				DrawTextEdit(textEdit);
				fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
				fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
				bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
				textEdit->textIterator[0] = '\0';
				if(textEdit->password == 0)
				{
					outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, textEdit->text);
				}
				else if(textEdit->password != 0)
				{
					for(i = 0;i < strlen(textEdit->text);i++)
					{
						strcat(password, "*");
					}
					outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, password);
					strcpy(password, "\0");
				}
//				NewMouse(mouse, mouse->mouseS);
				break;
			}	
		}
		if(!(mouse->mouseX > (textEdit->centrePosi[0] - textEdit->length / 2) && mouse->mouseX < (textEdit->centrePosi[0] + textEdit->length / 2) && mouse->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mouse->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) ||
			mouse->mouseX > (textEdit->centrePosi[0] - textEdit->length / 2 - textEdit->width / 2) && mouse->mouseX < (textEdit->centrePosi[0] - textEdit->length / 2) && mouse->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mouse->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) && sqrt(pow(mouse->mouseX - (textEdit->centrePosi[0] - textEdit->length / 2), 2) + pow(mouse->mouseY - textEdit->centrePosi[1], 2)) <= textEdit->width / 2 ||
	 		mouse->mouseX > (textEdit->centrePosi[0] + textEdit->length / 2) && mouse->mouseX < (textEdit->centrePosi[0] + textEdit->length / 2 + textEdit->width / 2) && mouse->mouseY > (textEdit->centrePosi[1] - textEdit->width / 2) && mouse->mouseY < (textEdit->centrePosi[1] + textEdit->width / 2) && sqrt(pow(mouse->mouseX - (textEdit->centrePosi[0] + textEdit->length / 2), 2) + pow(mouse->mouseY - textEdit->centrePosi[1], 2)) <= textEdit->width / 2) &&
	  		mouse->mouseClick == 1)
	   	{
			textEdit->state = 0;	
			DrawTextEdit(textEdit);
			fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
			fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
			bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
			textEdit->textIterator[0] = '\0';
			if(textEdit->password == 0)
			{
				outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, textEdit->text);
			}
			else if(textEdit->password != 0)
			{
				for(i = 0;i < strlen(textEdit->text);i++)
				{
					strcat(password, "*");
				}
				outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, password);
				strcpy(password, "\0");
			}
//			NewMouse(mouse, mouse->mouseS);
			break;
		}
	   	NewMouse(mouse);
	  	delay(20);
	}
}
