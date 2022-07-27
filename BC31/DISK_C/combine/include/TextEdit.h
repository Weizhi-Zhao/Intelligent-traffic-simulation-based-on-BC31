#ifndef __TextEdit__
#define __TextEdit__

//记录文本编辑框的各项属性
typedef struct
{
    //size:文本框长度
    int left, top, size;
    int onFocus;//是否处在被编辑状态
    int maxLenth;//最大字符数量
    char *text;//文本
    char *textIterator;//文本迭代器
} TextEdit;

//创建新TextEdit
TextEdit *NewTextEdit(int left, int top, int size, int maxLenth);

//初始化TextEdit
void TextEdit_Init(TextEdit *textEdit);

//此函数放在主循环中，用于检测键盘，若在被编辑状态有字符输入则更新文本编辑框
void TextEdit_Update(TextEdit *textEdit);

//删除文本编辑框
void DeleteTextEdit(TextEdit *textEdit);

#endif