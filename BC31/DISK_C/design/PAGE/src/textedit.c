#include "includeall.h"

//µÇÂ¼Ò³ÎÄ±¾¿ò 
void TextEditAllInit1(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 170, 50, 320, 240, "ÓÃ»§Ãû", 0);
	TextEditInit(&(textEdit[1]), 170, 50, 320, 320, "ÃÜÂë", 1);
}

//×¢²áÒ³ÎÄ±¾¿ò 
void TextEditAllInit3(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 190, 50, 480, 100, "ÊäÈëÐÂÓÃ»§Ãû", 0);
	TextEditInit(&(textEdit[1]), 190, 50, 480, 180, "ÊäÈëÃÜÂë", 0);
	TextEditInit(&(textEdit[2]), 190, 50, 480, 260, "ÊäÈëÈ·ÈÏÃÜÂë", 0); 
}

//³õÊ¼ÉèÖÃÒ³ÎÄ±¾¿ò
void TextEditAllInit5(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 190, 50, 480, 100, "ÊäÈë³µÁ¾ÊýÁ¿", 0);
	TextEditInit(&(textEdit[1]), 190, 50, 480, 170, "ÊäÈëÐ¡ÐÍ³µËÙ¶È", 0);
	TextEditInit(&(textEdit[2]), 190, 50, 480, 240, "ÊäÈë´óÐÍ³µËÙ¶È", 0);
	TextEditInit(&(textEdit[3]), 190, 50, 480, 310, "ÊäÈëºìÂÌµÆÊ±³¤", 0); 
}

//ÉèÖÃÒ³ÎÄ±¾¿ò 
void TextEditAllInit7(TextEdit *textEdit)
{
	TextEditInit(&(textEdit[0]), 190, 50, 480, 100, "ÊäÈë³µÁ¾ÊýÁ¿", 0);
	TextEditInit(&(textEdit[1]), 190, 50, 480, 170, "ÊäÈëÐ¡ÐÍ³µËÙ¶È", 0);
	TextEditInit(&(textEdit[2]), 190, 50, 480, 240, "ÊäÈë´óÐÍ³µËÙ¶È", 0);
	TextEditInit(&(textEdit[3]), 190, 50, 480, 310, "ÊäÈëºìÂÌµÆÊ±³¤", 0); 
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
	if(textEdit->state == 0 && textEdit->text[0] == '\0')//Êó±êÒÆ¿ªÇÒÎÞÎÄ×Ö 
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
	else if(textEdit->state == 1 && textEdit->text[0] == '\0')//Êó±êÍ£ÁôÔÚÉÏ·½ÇÒÎÞÎÄ×Ö 
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
	else if(textEdit->state == 1 && textEdit->text[0] != '\0')//Êó±êÍ£ÁôÔÚÉÏ·½ÇÒÓÐÎÄ×Ö 
	{
		setcolor(DARKGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
	}
	else if(textEdit->state == 2 && textEdit->text[0] == '\0')//Êó±êµã»÷ÇÒÎÞÎÄ×Ö 
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
	else if(textEdit->state == 2 && textEdit->text[0] != '\0')//Êó±êµã»÷ÇÒÓÐÎÄ×Ö 
	{
		setcolor(DARKGRAY);
		setlinestyle(SOLID_LINE, 0, 3);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] - textEdit->width / 2 - 2);
		line(textEdit->centrePosi[0] - textEdit->length / 2 - 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2, textEdit->centrePosi[0] + textEdit->length / 2 + 2, textEdit->centrePosi[1] + textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], 90, 270, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
		ellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], 270, 450, textEdit->width / 2 + 2, textEdit->width / 2 + 2);
	}
	else if(textEdit->state == 0 && textEdit->text[0] != '\0')//Êó±êÒÆ¿ªÇÒÓÐÎÄ×Ö 
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
		if(bioskey(1))//æ¿¡å‚›ç‰å®¸èŒ¬ç²¡éŽ¸å¤‰ç¬…éŽ¸å¤æ•­
		{
			letter = bioskey(0);//ç’‡è¯²å½‡ç’‡ãƒ¦å¯œé–¿?
			if(letter == 0x0e08)//æ¿¡å‚›ç‰éŽ¸å¤‰ç¬…é¨å‹¬æ¤‚backspaceé–¿?
			{
				if(textEdit->textIterator > textEdit->text)//æ¿¡å‚›ç‰ç€›æ¥ƒîƒæ¶“è¹­ç¬‰æ¶“è™¹â”–
				{
					fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
					fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
					bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
					textEdit->textIterator--;
					*(textEdit->textIterator) = '\0';//é’çŠ»æ«Žæ¶“â‚¬æ¶“î„ç“§ç»—?
					if(textEdit->text[0] != '\0' && textEdit->password == 0)
					{
						outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, strcat(textEdit->text, "|"));//ç¼æ¨ºåŸ—é‚å›§ç“§
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
			else if(letter != 0x1c0d && letter != 0x0e08 && strlen(textEdit->text) < textEdit->maxLength)//éˆî‡ç§´é‘çƒ˜æ¸¶æ¾¶Ñ‡æš±æ´?
			{
				fillellipse(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
				fillellipse(textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1], textEdit->width / 2 + 1, textEdit->width / 2 + 1);
				bar(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2, textEdit->centrePosi[0] + textEdit->length / 2, textEdit->centrePosi[1] + textEdit->width / 2);
				*(textEdit->textIterator) = letter;
				(textEdit->textIterator)++;
				*(textEdit->textIterator) = '\0';
				if(textEdit->password == 0)
				{
					outtextxy(textEdit->centrePosi[0] - textEdit->length / 2, textEdit->centrePosi[1] - textEdit->width / 2 + 2, strcat(textEdit->text, "|"));//ç¼æ¨ºåŸ—é‚å›§ç“§
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
			//ÈôÔÚÍâ²¿°´ÏÂÊó±ê×ó¼ü»ò»Ø³µ 
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
