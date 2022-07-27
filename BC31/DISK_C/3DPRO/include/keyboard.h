#ifndef __KeyBoard__
#define __KeyBoard__

#include "queue.h"
#include "zwzSignal.h"

//检测按键，若按下按键则向信号队列发送信号，信号名为"keyboard"
void detectKeyBoard(Queue *signalQueue);

//把按键转换成字母
int keyToLetter(int key);

#endif