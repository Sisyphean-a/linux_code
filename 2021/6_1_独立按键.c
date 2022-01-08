#include<reg52.h>

/*宏定义*/
#define const_voice_short 40//蜂鸣器短叫的时间
#define const_key_time1 30//按键去抖动延时的时间
#define const_key_time2 30

/*函数预加载*/
void initial_myself();//第一区，初始化单片机
void initial_peripheral();//第二区，初始化外围
void delay_long(unsigned int uiDelaylong);//时间函数
void T0_time();//定时中断函数
void key_service();//按键服务的应用程序
void key_scan();//按键扫描函数

/*位定义*/
sbit key_sr1=P0^0;//矩阵按键的位定义，
sbit key_sr2=P0^1;
sbit key_gnd_dr=P0^4;//模拟按键的接地端，从而让矩阵按键实现独立按键的功能
sbit beep_dr_=P2^7;//蜂鸣器的驱动IO口

/*全局定义*/
unsigned char ucKeySec=0;//被触发的按键编号
unsigned char ucKeyStartFlag1=0;//启动定时中断计数的开关
unsigned char unKeyTimeCnt1=0;//按键去抖动延时计数器
unsigned int uiKeyLock1=0;//按键触发后自锁的变量标志
unsigned char ucKeyStartFlag2=0;
unsigned int uiKeyTimeCnt2=0;
unsigned char unKeyLock2=0;
unsigned int uiVoiceCnt=0;//蜂鸣器鸣叫的持续时间计数器

/*主函数，程序入口*/
void main()
{
	initial_myself();//第一区
	delay_long(100);//延时
	initial_peripheral();//第二区
	while(1)
	{
		key_scan();//按键扫描函数
		key_service();//按键服务的应用程序
	}
}

void key_scan()
{
	if(key_sr1==1)//高电平，说明按键未按下
	{
		ucKeyLock1=0;//自锁标志清零
		ucKeyStartFlag1=0;//计数器停止
		uiKeyTimeCnt1=0;//按键去抖动延时计数器清零，很巧妙
	}
	else if(ucKeyLock1==0)//按键按下且是第一次按下
	{
		ucKeyStartFlag1=1;//打开计数器
		if(uiKeyTimeCnt1>const_key_time1)//排除抖动
		{
			ucKeyStartFlag1=0;//关闭计数器
			uiKeyTimeCnt1=0;//清零去抖计数器
			ucKeyLock1=1;//打开自锁
			ucKeySec=1;//触发一号按键
		}
	}
	if(key_sr2==1)//高电平，说明按键未按下
	{
		ucKeyLock2=0;//自锁标志清零
		ucKeyStartFlag2=0;//计数器停止
		uiKeyTimeCnt2=0;//按键去抖动延时计数器清零，很巧妙
	}
	else if(ucKeyLock2==0)//按键按下且是第一次按下
	{
		ucKeyStartFlag2=1;//打开计数器
		if(uiKeyTimeCnt2>const_key_time1)//排除抖动
		{
			ucKeyStartFlag2=0;//关闭计数器
			uiKeyTimeCnt2=0;//清零去抖计数器
			ucKeyLock2=1;//打开自锁
			ucKeySec=2;//触发一号按键
		}
	}	
}










