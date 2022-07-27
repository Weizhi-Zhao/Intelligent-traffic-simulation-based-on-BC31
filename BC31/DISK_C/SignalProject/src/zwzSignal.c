#include "zwzSignal.h"
#include <stdlib.h>
#include <string.h>

Signal *newSignal(char *signalText, void *parament, void (*deleteParament)(void *))
{
    Signal *signal = (Signal*)malloc(sizeof(Signal));
    signal->signalText = (char*)malloc((strlen(signalText) + 1) * sizeof(char));
    strcpy(signal->signalText, signalText);
    signal->parameter = parament;
    signal->deleteParament = deleteParament;
    return signal;
}

void deleteSignal(void *signal)
{
    Signal *s = signal;
    free(s->signalText);//先删除信号文本
    s->deleteParament(s->parameter);//删除参数
    free(s);//再删除信号
}