#ifndef __ZWZSIGNAL__
#define __ZWZSIGNAL__

typedef struct
{
    //信号的文本信息，若有人接受该信号，那么它们的文本信息应相同
    char *signalText;

    //信号的参数，可以指向一个int或结构体
    void *parameter;

    //删除参数的和函数
    void (*deleteParament)(void *);
} Signal;

//新建信号
Signal *newSignal(char *signalText, void *parameter, void (*deleteParament)(void *));

//删除信号
void deleteSignal(void *signal);

#endif