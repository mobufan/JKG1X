/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 **************
 * 文件名  ：led.h
 * 描述    ：LED外设库函数
 * 实验平台：风驰STM8开发板
 * 库版本  ：V2.1.0
 * 作者    ：风驰  QQ：779814207
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间 ：2012-10-20

  风驰STM8开发板硬件连接
    |--------------------|
    |  LED1-PD0          |
    |  LED2-PD1          |
    |  LED3-PD2          |
    |  LED4-PD3          |
    |--------------------|
* 注意:
* 1

*******************************************************************************/
#ifndef __MAIN_H
#define __MAIN_H

/* 自定义数据类型 */
typedef unsigned char     BOOLEAN;
typedef unsigned char     INT8U;                    /* Unsigned  8 bit quantity                            */
typedef signed   char      INT8S;                    /* Signed    8 bit quantity                            */
typedef unsigned int       INT16U;                   /* Unsigned 16 bit quantity                            */
typedef signed   int        INT16S;                   /* Signed   16 bit quantity                            */
typedef unsigned long    INT32U;                   /* Unsigned 32 bit quantity                            */
typedef signed   long     INT32S;                   /* Signed   32 bit quantity                            */
typedef float                 FP32;                     /* Single precision floating point                     */


/* 自定义常量宏和表达式宏 */

#define BIT0    0x01          /* BIT0  = (1<<1)  = 0b00000001 */
#define BIT1    0x02          /* BIT1  = (1<<2)  = 0b00000010 */
#define BIT2    0x04          /* BIT2  = (1<<3)  = 0b00000100 */
#define BIT3    0x08          /* BIT3  = (1<<4)  = 0b00001000 */
#define BIT4    0x10          /* BIT4  = (1<<5)  = 0b00010000 */
#define BIT5    0x20          /* BIT5  = (1<<6)  = 0b00100000 */
#define BIT6    0x40          /* BIT6  = (1<<7)  = 0b01000000 */
#define BIT7    0x80          /* BIT7  = (1<<8)  = 0b10000000 */


#define   checkbit(var,bit)  (var & (0x01 << (bit)))
#define   setbit(var,bit)    (var |= (0x01 << (bit)))
#define   clrbit(var,bit)    (var &= (~(0x01 << (bit))))


#define debugled   // 测试使用
#define debugAD     // 测试使用

#define	AUTOSTATE	0x01				// 自动状态
#define	HANDSTATE	0x02				// 手动状态
//#define	SETSTATE	0x03				// 设定状态
//#define	ADJSTATE	0x04				// 校准状态
#define	OTHERSTATE	0x05			    //  辅助显示状态


/* 包含系统头文件 */
#include <math.h>

/* 包含自定义头文件 */
#include "sysclock.h"
#include "tim1.h"
#include "stm8s_it.h"
#include "tm1629b.h"
#include "Iwdg.h"
#include "LedDisplay.h"
#include "metset.h"
#include "AD.h"
#include "AssistModule.h"
#include "CapTask.h"
#include "Config.h"

/* 自定义数据类型 */


#define CAPNUMBER_MAX   12
#define CAPNUMBER_MIN   1
#define ACTDELAY_MAX    120
#define ACTDELAY_MIN    10
#define PFTH_MAX        99
#define PFTH_MIN        90
#define OVERV_MAX       20
#define OVERV_MIN       5
#define LIMITI_MAX      10
#define LIMITI_MIN      0
#define PFREPAIR_MAX    10
#define PFREPAIR_MIN    0

struct CAP
{
	INT8U	cCapSize;					// 电容容量 1 - 200	 Kvar
	INT8U	cCapKind;					// 电容种类 0 表示没有,1 - 分补3-共补;0x11 表示A 相分补 ;0x21表示B 相分补
	INT8U	cCapCool;					// 电容的冷却时间 ;0 表示已经冷却 随时可以投入
	INT8U	cCapSatae;					// 电容器的状态 1 表示已投入 0 表示已切除
	INT16U	wCapUseNum;				// 该电容器的使用次数
};

#define	CapOn		0x01
#define	CapOff		0x00

#define	SETMENU	    0x01				// 设置菜单
#define	DISPMENU	0x00				// 显示菜单

struct STATE
{
	INT8U	cAutoState;					// 手动自动状态   TRUE = Auto   FALSE = Hand
	INT8U	cOverVAlarm;				// 过压报警
	INT8U	cLossCupAlarm;				// 欠补报警  全部电容已经投入但是功率因素仍然不够
	INT8U	cOverCupAlarm;				// 过补报警  全部电容已经切除但是功率因素仍然超前
	INT8U   cNoIAlarm;                  // 无电流报警
	INT8U   cLowIAlarm;                 // 小电流报警
	INT8U   cLowUAlarm;                 // 欠压报警
	
};

struct ELEC_PARA					//电参数这个是计算后的电参数 
{                          
	INT16S	UU;					    // 电压有效值(000-220)		没有小数位 // 380V 时约为630
	INT16S	II;					    // 电流有效值 5A  未加ct(0000-5000) // 5A时约为400
	INT16S  Cos;				    // 功率因素  (0000-99-1000-101-200)
	                                //           (0-0.99-1.00-0.99-200)
	                                //           (滞后 中 超前)
//	INT16S	Fraq;					// 频率(000-500)
//	INT32S	ActP[4];				// 有功功率(0000-9999)
//	INT32S 	ActS[4];				// 无功功率(0000-9999)
//	INT32S	ActQ;				// 视在功率(0000-9999)

//	INT32S   THDv[3];				// 畸变率(000-999)
//	INT32S	IICT[3];				// ct变比后的数据
};

struct ELEC_TEMP						// 电气性能的中间数据 ，由这些数据的平均值算出我们需要的结果
{
	INT16S	TUU[10];					
	INT16S	TII[10];
	INT16S	TCos[10];
};

struct DISPDATE						// 这里使用来刷新的数据 注意这里是1表示亮 和实际的硬件刚好相反
{
	INT8U	cDispData[3];				//当前数码管显示数据  最终数据 [0]=左 [1]=中 [2]=右
};

struct	REAL	// 这里是显示数据;直接被送到显示缓冲
{
    INT8U 	Factor[3];		    // 功率因素 或 noI
    INT8U   A1_Number[3];       // 功率门限
    INT8U   A2_OnOffTime[3];    // 投切间隔
    INT8U   A3_PfLimit[3];      // 功率因素下限
    INT8U   A4_OverVLimit[3];   // 过压门限
    INT8U   A5_LowILimit[3];    // 欠流门限
    INT8U   A6_AutoOrHand[3];   // 手动自动
    INT8U   B1[3];              // 电压 校准值
    INT8U   B2[3];              // 电流 校准值
    INT8U   B3[3];              //  pf 校准值
};
struct	RELAYTIME		// 这里是所有需要延时的定时器倒计数器
{
	INT16U	c10msTime;			// 10ms 倒计时器
	INT8U	c10msChange;		// 10ms标志
	INT8U	cSecChange;			// 秒标志
	INT8U   c833usTime;       // 833us标志 最小时间颗粒

	INT8U	cNullTime;			// 无按键倒计时器

    INT16U   wDelayTime;         // 延时函数的计数器
};
struct	DspControl
{
      INT16U		PagePtr;		// 显示页面的指针 非常重要
};


/*
struct	KEY
{
	INT8U cLastReadKey;				//这个是读的物理值
	INT8U cRealKey;					// 这个是处理好的有效值
};
*/

// 本组特用于wConCap
// 
#define	F_SELC3		0x0010		// 须投入共补
// #define	F_SELCA	    0x0020		// 须投入分补a
//#define	F_SELCB		0x0040		// 须投入分补b
//#define	F_SELCC		0x0080		// 须投入分补c
#define	F_DELC3	    0x0001		// 须切除共补
//#define	F_DELCA	    0x0002		// 须切除分补a
//#define	F_DELCB	    0x0004		// 须切除分补b
//#define	F_DELCC	    0x0008		// 须切除分补c
#define	F_OVERV	    0x0100		// 因为过压状态而动作
#define	F_NOV		0x0200		// 因为缺相状态而动作
#define	F_LOWI		0x0400		// 因为欠流
#define	F_NOI		0x0800		// 因为无电流

// 电容的投切计算值
struct	COMCAP				
{
	INT16U	wConCap[120];			// 最近的120s 内电容的投切逻辑 每秒一次
};

typedef struct
{
	struct ELEC_PARA	sElecPara;
	struct ELEC_TEMP sElecTemp;
	struct DISPDATE	sDisMem;
	struct STATE		sStateSet;
	struct REAL		sReal;
	struct RELAYTIME	sRelayTime;
	struct DspControl	sDspCtr;
	struct CAP		sCapPara[12];		// 电容器的状态
	struct COMCAP 	sConCap;			// 电容的投切计算结果	
	unsigned char cSysFlg;              // 系统状态
} DRAM;

struct CONFIG
{
	INT16U	c3CupNumber;				//  共补电容器路数(1-12)
	INT16U	cCupDelayTime;			    //  电容器投入延时 (秒) 10-120 步长10
	INT16U	cPfLimit;					//  无功门限 80-99 步长1
	INT16U	wOverVoltage;				//  过压门限  (5-25) 步长5
	INT16U   cLowILimit;                 //  小电流门限 0-10 步长2
	INT16U   XiaoZun1;                   //  校准值1 II 取5A 时的电流值，大约400
	INT16U   XiaoZun2;                   //  校准值2 UU 取380/220 时的电流值, 大约630
	INT16U   XiaoZun3;                   //  校准值3 pf 取
};
typedef struct
{
	struct	CONFIG	sConfig;				// 这些参数需要保存到eeprom
}SRAM;


// 本枚举仅仅是定义一个0-max的变量
// 用来说明平时运行的函数分别是什么，并没有什么含义
typedef enum _TASK_LIST
{
    TASK_ADC,
    TASK_RELAY_ACT,
    TASK_RELAYOUT,
    TASK_KEY,
    TASK_FLASHLED,
    TASK_IWDG,
    TASK_TESTLED,
    TASK_MAX
} TASK_LIST;

typedef struct _TASK_COMPONENTS
{
    uint8_t Run;                  // 任务运行标志: 0 不运行 1运行
    uint8_t Stop;                 // 任务关闭标志: 0 正常 1 关闭
    uint16_t Timer;                // 计时器 只是计时器，可以赋一个初值，初值用来避免启动的时间
    uint16_t ItvTime;              // 任务间隔时间
    void (*TaskHook)(void);     // 需要运行的任务函数
} TASK_COMPONENTS;

/* 声明给外部使用的变量 */
extern SRAM SM;     // 配置文件
extern DRAM DM;     //不需要初始化的，或初始化为0的变量
extern unsigned char ReloadIWdog;       // 喂狗寄存器
extern TASK_COMPONENTS TaskComps[];

/* 声明给外部使用的函数 */

/*******************************************************************************
 * 名称: TaskRemarks
 * 功能: 任务标志处理
 * 形参: 无
 * 返回: 无
 * 说明: 1 专门处理任务的标志位
         2 本函数 每个时间颗粒执行1次
 ******************************************************************************/
void TaskRemarks(void);

#endif

/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/

