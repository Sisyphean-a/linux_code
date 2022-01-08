#include<REG52.H>

/*全局变量声明*/
#define const_time_05s 222//0.5s的时间需要的定时中断次数
#define const_time_1s  444
#define const_time_3s 1333
#define const_time_6s 2664

#define const_voice_short 40//蜂鸣器短叫的持续时间
#define const_voice_long 200

/*函数预加载*/
void initial_myself();//第一区，初始化单片机内部寄存器
void initial_peripheral();//第二区，初始化非即时的外围芯片或者模块
void delay_long(unsigned int uiDelaylong);//延时函数
void led_flicker();//第三区，小灯主程序
void alarm_run();//第三区，蜂鸣器主程序
void T0_time();//定时中断函数

/*引脚声明*/
sbit beep_dr=P2^7;//蜂鸣器的驱动IO口，dr表示输出
sbit led_dr=P3^5;//LED灯的驱动IO口

/*变量声明*/
unsigned char ucLedStep=0;//LED灯的步骤变量，uc表示类为字符，step表示这是一个步骤
unsigned int uiTimeLedCnt=0;//LED灯统计定时中断次数的延时计数器，cnt表示这是一个计数器

unsigned char ucAlarmStep=0;//报警的步骤变量
unsigned int uiTimeAlarmCnt=0;//报警统计定时中断次数的延时计数器

unsigned int uiVoiceCnt=0;//蜂鸣器鸣叫的持续时间计数器

/*主函数，程序的入口*/
void main()
{
    initial_myself();
    delay_long(100);
    initial_peripheral();
    while(1)
    {
        led_flicker();//第一个任务，led闪烁
        alarm_run();//第二个任务，蜂鸣器鸣叫
    }
}

/*第三区，任务1，闪烁灯函数*/
void led_flicker()
{
    switch(ucLedStep)
    {
        case 0:
		    if(uiTimeLedCnt>=const_time_05s)//时间到
		    {
		        uiTimeLedCnt=0;//时间计数器清零
		        led_dr=1;//开灯
		        ucLedStep=1;//切换到下一个步骤
		    }
		    break;
        case 1:
       		if(uiTimeLedCnt>=const_time_05s)
       		{
       			uiTimeLedCnt=0;
       			led_dr=0;//关灯
       			ucLedStep=0;
       		}
       		break;
    }
}

/*第三区，任务2，蜂鸣器函数*/
void alarm_run()
{
	switch(ucAlarmStep)
	{
		case 0:
			if(uiTimeAlarmCnt>=const_time_3s)//时间到
			{
				uitimeAlarmCnt=0;//时间计数器清零
				uiVoiceCnt=const_voice_short;//蜂鸣器短叫
				ucAlarmStep=1;//切换到下一个步骤
			}
			break;
		case 1:
			if(uiTimeAlarmCnt>=const_time_3s)
			{
				uiTimeAlarmCnt=0;
				uiVoiceCnt=const_voice_long;//蜂鸣器长叫
				ucAlarmStep=0;
			}
	}
}

/*定时中断函数*/
void T0_time() interrupt 1
{
	TF0=0;//清楚中断标志
	TR0=0;//关闭中断
	if(uiTimeLedCnt<0xffff)//防止uiTimeLedCnt朝范围
	{
		uiTimeLedCnt++;//LED灯的时间计数器，累加定时中断的次数
	}
	if(uiTimeAlarmCnt<0xffff)
	{
		uiTimeAlarmCnt++;//蜂鸣器的时间计数器，累加定时中断的次数
	}
	if(uiVoiceCnt!=0)
	{
		uiVoiceCnt--;//每次进入定时中断都自减1,直到等于零才停止鸣叫
		beep_dr=0;//蜂鸣器是PNP三极管控制，低电平开始鸣叫
	}
	else
	{
		;//对称，无作用
		beep_dr=1;//高电平停止鸣叫
	}
	TH0=0xf8;//重装初始值（65535-2000）=0xf82f
	TL0=0x2f;
	TR0=1;//打开中断
}

/*延时函数*/
void delay_long(unsigned int uiDelayLong)
{
	unsigned int i;
	unsigned int j;
	for(i=0;i<uiDelayLong;i++)
	{
		for(j=0;j<500;j++)
		{
			;//一个分号相当于执行一条空语句
		}
	}
}

/*第一区，初始化单片机*/
void initial_myself()
{
	beep_dr=1;//蜂鸣器初始状态为关闭
	led_dr=0;//小灯初始状态为关闭
	TMOD=0x01;//设置定时器0为工作模式1
	TH0=0xf8;//为定时器装入初始值
	TL0=0x2f;
}

/*第二区，初始化外围*/
void initial_peripheral()
{
	EA=1;//开总中断
	ET0=1;//允许定时中断
	TR0=1;//启动定时中断
}





