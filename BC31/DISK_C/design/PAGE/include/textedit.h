#ifndef __TextEdit__
#define __TextEdit__

//记录文本编辑框的各项属性
typedef struct
{
    int length;
    int width;
    int maxLength;
    int centrePosi[2];
    int onFocus;//是否处在被编辑状态
    int state;
    int password;
    char *originText;
    char text[11];//文本
    char *textIterator;//文本迭代器
} TextEdit;

//创建新TextEdit
void TextEditInit(TextEdit *textEdit, int length, int width, int cenX, int cenY, char originText[], int password);


void TextEditStateJudge(TextEdit textEdit[], int num, MouseState *mouse);


void TextEditStateChange(TextEdit *textEdit, MouseState *mp);


void DrawTextEdit(TextEdit *textEdit);

//��¼ҳ�ı��� 
void TextEditAllInit1(TextEdit *textEdit);

//ע��ҳ�ı���
void TextEditAllInit3(TextEdit *textEdit); 

//��ʼ����ҳ�ı��� 
void TextEditAllInit5(TextEdit *textEdit);

//����ҳ�ı���
void TextEditAllInit7(TextEdit *textEdit);


void BeginType(TextEdit *textEdit, MouseState *mouse);


//此函数放在主循环中，用于检测键盘，若在被编辑状态有字符输入则更新文本编辑框
void TextEdit_Update(TextEdit *textEdit);

#endif
