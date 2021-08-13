#include<REG52.H>

/*全局变量*/
#define const_voice_short 40//蜂鸣器鸣叫的时间
#define const_key_time1 500//按键去抖延时的时间
#define const_key_time2 500

/*函数预加载*/
void initial_myself();//第一区
void initial_peripheral();//第二区
void delay_long(unsigned int uiDelaylong);//延时函数
void T0_time();//定时中断函数
void key_service();//第三区，按键服务的应用程序
void key_scan();//第三区，按键扫描函数

/*位定义*/
sbit key_sr1=P0^0;//对应按键的S1键
sbit key_sr2=P0^1;
sbit key_gnd_dr=P0^4;//模拟独立按键的地GND，因此必须一直输出低电平
sbit beep_dr=P2^7;//蜂鸣器的驱动IO口

/*变量定义*/
unsigned char ucKeySec=0;//被触发的按键编号
unsigned int uiKeyTimeCnt1=0;//按键去抖动延时计数器
unsigned char ucKeyLock1=0;//按键触发后自锁的变量标记
unsigned int uiKeyTimeCnt2=0;
unsigned char unKeyLock2=0;
unsigned int uiVoiceCnt=0;//蜂鸣器鸣叫的持续时间计数器

/*主函数，程序的入口*/
void main()
{
	initial_myself();
	delay_long(100);
	initial_peripheral();
	while(1)
	{
		key_scan();//按键扫描函数
		key_service();//按键服务的应用程序
	}
}

/*第三区，按键扫描函数*/
void key_scan()
{
	if(key_sr1==1)//IO是高电平，说明S1没有被按下，这时要清零一些标志位
	{
		ucKeyLock1=0;//按键自锁标志清零
		uiKeyTimeCnt1=0;//按键去抖动延时计数器清零，很巧妙的一种去抖方式
	}
	else if(ucKeyLock1==0)//S1被按下，且是第一次被按下
	{
		++uiKeyTimeCnt1;//延时计数器
		if(uiKeyTimeCnt1>const_key_time1)//超过抖动时间，判定为按下按键
		{
			uiKeyTimeCnt1=0;//延时计数器清零
			ucKeyLock1=1;//打开按键自锁，避免一直触发
			ucKeySec=1;//触发一号键
		}
	}
	
	if(key_sr2==1)
	{
		ucKeyLock2=0;
		uiKeyTimeCnt2=0;
	}
	else if(ucKeyLock2==0)
	{
		++uiKeyTimeCnt2;
		if(uiKeyTimeCnt2>const_key_time2)
		{
			uiKeyTimeCnt2=0;
			ucKeyLock2=1;
			uckeySec=2;
		}
	}
}

/*第三区，按键服务的应用程序*/
void key_service()
{
	switch(ucKeySec)
	{
		case 1:
			uiVoiceCnt=const_voice_short;//按键声音触发，滴一声就停
			ucKeySec=0;//响应按键服务处理程序后，按键编号清零，避免重复触发
		break;
		case 2:
			uiVoiceCnt=conSt_voice_short;
			ucKeySec=0;
		break;
	}
}

/*中断函数*/
void T0_time() interrupt 1
{
	TF0=0;//清除中断
	TR0=0;//关闭中断
	if(uiVoiceCnt!=0)//判断蜂鸣器计数器是否为0
	{
		uiVoiceCnt--;//每次进入中断都自减1，直到等于0停止鸣叫
		beep_dr=0;//蜂鸣器打开
	}
	else
	{
		;
		beep_dr=1;//蜂鸣器关闭
	}
	TH0=0xf8;//重装初始值
	TL0=0x2f;
	TR0=1;//开中断
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
	key_gnd_dr=0;//独立按键的地GND，需要一直输出低电平
	beep_dr=1;//蜂鸣器关闭
	TMOD=0x01;//定时器0工作模式为模式1
	TH0=0xf8;//定时器装入初始值
	TL0=0x2f;
}

/*第二区，初始化外围*/
void initial_peripheral()
{
	EA=1;//开总中断
	ET0=1;//允许定时中断
	TR0=1;//启动定时中断
}








