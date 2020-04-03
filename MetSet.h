/******************** (C) COPYRIGHT  杭州浙宝微电脑技术有限公司 **************
 * 文件名  ：TM1629B.c
 * 描述    ：TM1629 B的驱动函数
 * 实验平台：X963MV1
 * 库版本  ：V1.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 淘宝    ：
 * 修改时间 ：2012-10-20

  X963MV1 硬件连接
    |--------------------|
    |  DIO-PC1          |
    |  CLK-PC2          |
    |  STB-PC3          |
    |--------------------|

*******************************************************************************/

#ifndef __METSET_H
#define __METSET_H

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "stm8s.h"
#include "main.h"

/* 自定义数据类型 */

/* 自定义常量宏和表达式宏 */


#define	NULLTIMENUM		100             // 无按键常数 100*keyscan()周期

//metstatus register flags define
#define  F_Ger   0x01    //仪表处于正常的测量显示状态
#define  F_Set   0x02    //仪表处于菜单设置状态
//#define  F_Adj   0x04    //表示仪表处于校准状态
//#define  F_Fls       0x08    //表示仪表处于闪烁改变数据的状态
//#define  F_Quk       0x10    //表示仪表处于显示版本和频率的状态

// DM.ReChc7302 对7302的校准
#define  F_ReChk         0x80    // 表示仪表经过上位机重新校准 或 设置过7302参数 需要重新设置 7302

//KeyFlg  register flags define
#define         F_KeySet        BIT0
#define         F_KeyAdd        BIT1
#define         F_KeySub        BIT2
#define         F_KeyNull       BIT3

// 默认页面
#define AUTO_MENU		0x1001				//自动菜单


//FlashFlg  register flags define
#define         F_FlashNew      0x01    //保存flash数据的标志

//某些特殊的页面地址
#define   VolPage       0           // 正常电压显示
#define   DIOPage   63
#define   VERPage   74          // 版本号

#define   LEDType       1
#if       LEDType == 0
#define   sega          0x01
#define   segb          0x04
#define   segc          0x10
#define   segd          0x40
#define   sege          0x80
#define   segf          0x02
#define   segg          0x08
#define   segh          0x20
#elif     LEDType  == 1
#define   sega          0x01
#define   segb          0x02
#define   segc          0x04
#define   segd          0x08
#define   sege          0x10
#define   segf          0x20
#define   segg          0x40
#define   segh          0x80
#endif

#define DS_Chr_0     sega|segb|segc|segd|sege|segf
#define DS_Chr_1     segb|segc
#define DS_Chr_2     sega|segb|segd|sege|segg
#define DS_Chr_3     sega|segb|segc|segd|segg
#define DS_Chr_4     segb|segc|segf|segg
#define DS_Chr_5     sega|segc|segd|segf|segg
#define DS_Chr_6     sega|segc|segd|sege|segf|segg
#define DS_Chr_7     sega|segb|segc
#define DS_Chr_8     sega|segb|segc|segd|sege|segf|segg
#define DS_Chr_9     sega|segb|segc|segd|segf|segg
#define DS_Chr_A     sega|segb|segc|sege|segf|segg
#define DS_Chr_b     segc|segd|sege|segf|segg
#define DS_Chr_C     sega|segd|sege|segf
#define DS_Chr_d     segb|segc|segd|sege|segg
#define DS_Chr_E     sega|segd|sege|segf|segg
#define DS_Chr_F     sega|sege|segf|segg

#define DS_Chr_Neg   segg
#define DS_Chr__     segg
#define DS_Chr_c     segd|sege|segg
#define DS_Chr_h     segc|sege|segf|segg
#define DS_Chr_H     segc|sege|segf|segg|segb
#define DS_Chr_J     segb|segc|segd
#define DS_Chr_K     segd|sege|segf|segg
#define DS_Chr_L     segd|sege|segf
#define DS_Chr_N     sega|segb|segc|sege|segf
#define DS_Chr_n     segc|sege|segg
#define DS_Chr_o     segc|segd|sege|segg
#define DS_Chr_P     sega|segb|sege|segf|segg
#define DS_Chr_q     sega|segb|segc|segf|segg
#define DS_Chr_r     sege|segg
#define DS_Chr_S     sega|segc|segd|segf|segg
#define DS_Chr_t     segd|sege|segf|segg
#define DS_Chr_I     segb|segc
#define DS_Chr_i     sege
#define DS_Chr_U     segb|segc|segd|sege|segf
#define DS_Chr_y     segb|segc|segd|segf|segg
#define DS_Chr_Z     sega|segb|segd|sege|segg
#define DS_Chr_u     segc|segd|sege
#define DS_Chr_0_    sega|segb|segc|segd|sege|segf|segh
#define DS_Chr_X1   sega|segd|sege|segf         // 特殊公司标志
#define DS_Chr_X2   sega|segd|segg
#define DS_Chr_X3   sega|segd|segg
#define DS_Chr_X4   sega|segb|segc|segd
#define DS_Chr_dp	((segh))



//menu
#define	MAXSETMENU	6		// 设置菜单 最多5个
#define	MAXSYSMENU	3		//  系统菜单最多3个


/* 声明给外部使用的变量 */

/* 声明给外部使用的函数 */
/*******************************************************************************
 * 名称: Key_Task
 * 功能: 根据按键的输入显示不同的菜单
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Key_Task(void);

/*******************************************************************************
 * 名称: Selfdetect
 * 功能: 根据当前参数显示
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Selfdetect(void);

/*******************************************************************************
 * 名称: delayX10ms
 * 功能: 按照标准10ms为格点，延时规定的时间
 * 形参: 无
 * 返回: 无
 * 说明: 1 DM.sRelayTime.wDelayTime 必须放在中断中执行--
         2 时间中断必须打开
         3 延时不能超过看门狗的动作时间
 ******************************************************************************/
void delayX10ms(unsigned int time);


/*******************************************************************************
 * 名称: AutoAdjust
 * 功能: 自动校准 U I PF
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void AutoAdjust(void);

#endif


/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/

