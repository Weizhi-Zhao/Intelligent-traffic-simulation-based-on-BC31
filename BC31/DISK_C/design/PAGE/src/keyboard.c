#include "keyboard.h"
#include "queue.h"
#include "zwzSignal.h"
#include <alloc.h>
#include <stdlib.h>

void detectKeyBoard(Queue *signalQueue)
{
	int *key;
	Signal *keyboardSignal;

	//如果已经按下按键
	if(bioskey(1))
	{
		//为信号的参数新开空间
		key = (int*)malloc(sizeof(int));
		//读取该按键
		*key = bioskey(0);
		//创建新信号
		keyboardSignal = newSignal("keyboard", key, free);
		//把信号放进信号队列
		queuePush(signalQueue, keyboardSignal);
	}
}

int keyToLetter(int key)
{
	//只取后8位
	return key & 0x00ff;
}
