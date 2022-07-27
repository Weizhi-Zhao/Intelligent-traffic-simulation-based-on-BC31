#include "includeall.h"

void RegisterOK(MouseState *mouse, TextEdit *textEdit)
{
	FILE *fp;
	char userName[12];
	
	if(strlen(textEdit[0].text) == 0 || strlen(textEdit[1].text) == 0 || strlen(textEdit[2].text) == 0) 
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 380, 679, 423); 
		puthz(320, 380, "输入不能为空！", 32, 40, WHITE);
		return;
	}
	if(strcmp(textEdit[2].text, textEdit[1].text) != 0)
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 380, 679, 423); 
		puthz(320, 380, "两次密码不一致！", 32, 40, WHITE);
		return;
	}
	else
	{
		if((fp = fopen("c:\\design\\page\\file\\accountinfo.txt", "r")) == NULL)
		{
			printf("Error on opening file!\n");
			exit(1);
		}
		while(fgets(userName, 11, fp) != NULL)
		{
			userName[strlen(userName) - 1] = '\0';
			if(strcmp(userName, textEdit[0].text) == 0)
			{
				setfillstyle(SOLID_FILL, GREEN);
				bar(320, 380, 679, 423); 
				puthz(320, 380, "用户名已存在！", 32, 40, WHITE);
				fclose(fp);
				return; 
			}
			fgets(userName, 11, fp);
		}
		fclose(fp);
		if((fp = fopen("c:\\design\\page\\file\\accountinfo.txt", "a"))== NULL)
		{
			printf("Error on opening file!\n");
			exit(1);
		}
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 380, 679, 423); 
		puthz(320, 380, "注册成功！", 32, 40, WHITE);
		fseek(fp, 0, SEEK_END);
		fputs(textEdit[0].text, fp);
		fputs("\n", fp);
		fputs(textEdit[1].text, fp);
		fputs("\n", fp);
		
		fclose(fp);
	}
}

void LoginOK(MouseState *mouse, TextEdit *textEdit)
{
	FILE *fp;
	char userName[12];
	char password[12];
	
	if(strlen(textEdit[0].text) == 0 || strlen(textEdit[1].text) == 0) 
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 420, 500, 479); 
		puthz(275, 430, "输入不能为空！", 32, 35, RED);
		return;
	}
	if((fp = fopen("c:\\design\\page\\file\\accountinfo.txt", "r")) == NULL)
	{
		printf("Error on opening file!\n");
		exit(1);
	}
	while(fgets(userName, 11, fp) != NULL)
	{
		fgets(password, 11, fp);
		userName[strlen(userName) - 1] = '\0';
		password[strlen(password) - 1] = '\0';
		if(strcmp(userName, textEdit[0].text) == 0 && strcmp(password, textEdit[1].text) == 0)
		{
			fclose(fp);
			PageMain(mouse);
			return; 
		}
	}
	fclose(fp);
	setfillstyle(SOLID_FILL, GREEN);
	bar(320, 420, 500, 479); 
	puthz(275, 430, "用户名或密码错误！", 32, 28, RED);
}
