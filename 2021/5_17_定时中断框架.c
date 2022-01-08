#include<REG52.H>

#define const_time_level 200//上限阀值

void initial_myself();
void initial_peripheral();
void delay_long(unsigned int uiDelaylong);
void led_filcker();
void T0_time();

sbit led_dr=P3^5;

unsigned char ucLedStep=0;//步骤变量
unsigned int uiTimeCnt=0;//统计定时中断次数的延时计数器

void main()
{
    initial_myself();
    delay_long(100);
    initial_perpheral();
    while(1)
    {
        led_flicker();
    }
}

void led_flicker()
{
    switch(ucLedStep)
    {
        case 0:
            if(uiTimeCnt>=const_time_level)
            {
                ET0=0;//禁止定时中断
                uiTimeCnt=0;//时间计数器清零
                ET0=1;//开启定时中断
                led_dr=1;//点亮小灯
                ucLedStep=1;//切换到下一个步骤
            }
        case 1:
            if(uiTimeCnt>=const_time_level)
            {
                ET0=0;
                uiTimeCnt=0;
                ET0=1;
                led_dr=0;
                ucLedStep=0;
            }
        break;
    }
}

void T0_time() interrupt 1
{
    TF0=0;//清除中断标志，或者描述为中断清零
    TR0=0;//关中断
    if(uiTimeCnt<0xffff)//防止uiTimeCnt超范围
    {
        uiTimeCnt++;//累加定时中断的次数
    }
    TH0=0xf8;
    TL0=0x2f;//重装初始值
    TR0=1;//开中断
}

void delay_long(unsigned int uiDelayLong)
{
    unsigned int i;
    unsigned int j;
    for(i=9;i<uiDelayLong;i++)
    {
        for(j=0;j<500;j++)
        {
            ;
        }
    }
}

void initial_myself()
{
    TMOD=0x01;//设置定时器 0 为工作方式 1
    TH0=0xf8;
    TL0=0x2f;
    led_dr=0;
}

void initial_peripheral()
{
    EA=1;//开总中断
    ET0=1;//允许定时中断
    TR0=1;//启动定时中断
}






