/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 **************
 * 文件名  ：tim2.h
 * 描述    ：TIM2定时、PWM功能设置函数库
 * 实验平台：风驰STM8开发板
 * 库版本  ：V2.1.0
 * 作者    ：风驰  QQ：779814207
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 *修改时间 ：2012-11-12

  风驰STM8开发板硬件连接
    |-------------------------|
    |  蜂鸣器 - PD4(TIM2_CH1) |
    |  LED4-PD3(TIM2_CH2)     |
    |-------------------------|

*******************************************************************************/
#ifndef __TIM2_H
#define __TIM2_H

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "stm8s.h"
#include "main.h"

/* 自定义数据类型 */

/* 自定义常量宏和表达式宏 */
#define PWM        0
#define BaseTime   1
#define TIM2_Mode  PWM		/* 要测试TIM2的哪种模式 */


/* 声明给外部使用的变量 */

/* 声明给外部使用的函数 */

/*******************************************************************************
 * 名称: Tim2_Timer_Init
 * 功能: TIM2定时器初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Tim2_Timer_Init(void);

/*******************************************************************************
 * 名称: Tim2_Stop
 * 功能: TIM2定时器计数器关闭
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Tim2_Stop(void);

/*******************************************************************************
 * 名称: Tim2_Start
 * 功能: TIM2定时器计数器开启
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Tim2_Start(void);


/*******************************************************************************
 * 名称: TC2_Switch
 * 功能: TIM2定时器使能开关
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void TC2_Switch(uint8_t flag, uint32_t baud, uint8_t oper_mode);


/*******************************************************************************
 * 名称: Delay_ms
 * 功能: 延时函数
 * 形参: n10ms -> 以ms为间隔进行延时
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Delay_ms(u16 nms);


#endif


/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/
