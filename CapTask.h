/*************** (C) COPYRIGHT 杭州中深电力技术技术有限公司 ******************
 * 文件名  ：xxxx.c
 * 描述    ：xxxxxx  无功补偿控制器
 * 实验平台：xxxxxxxx
 * 库版本  ：V2.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 修改时间 ：xxxx-xx-xx
*******************************************************************************/
#ifndef __CAPTASK_H
#define __CAPTASK_H

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "stm8s.h"
#include "main.h"

/* 自定义数据类型 */

/* 自定义常量宏和表达式宏 */


#define	C3_KIND		0x03				// 共补电容

#define	CUSE_STATE		0x01				// 电容处于使用状态
#define	CFREE_STATE	0x00				// 电容处于空闲状态
#define	CCOOL_TIME		30					// 冷却时间

#define CUTLIMIT		100		// 切除门限
#define VOVERHYSTER	    15		// 电压过压滞回 约为10V



/* 自定义数据类型 */

// 这里是用来显示的数据

/* 声明给外部使用的函数 */

/*******************************************************************************
 * 名称: CapOutCon
 * 功能: 根据当前电容状态,输出到CPU 的相应管脚上。
 * 形参: 无
 * 返回: 无
 * 说明: 1 直接的硬件输出，
         2 本函数需要有相应的 port的初始化过程。
 ******************************************************************************/
void CapOutCon(void);

/*********************************************************************
*
* 函 数 名: ActUseCutCap
* 功能描述: 根据输入参数对电容器进行投切
* 函数说明: 
* 调用函数: 无
* 全局变量:  
* 输 入:
		// 1 wCapCon;			电容的控制结果

* 返 回:  cResult		true or false
		有动作 返回 true
		无动作 返回 false
* 设 计 者：moyi 日期：2020-02-15
* 修 改 者：moyi 日期：2020-02-15
* 版 本：
***********************************************************************/
INT8U ActUseCutCap(const INT16U wCapCon,const INT8U cMust);

/*******************************************************************************
 * 名称: Cap_Task
 * 功能: 根据当前状态计算并处理 电容器的投切
 * 形参: 无
 * 返回: 无
 * 说明: 无
         1 计算本周期电容器的投切结果
         2 投切结果存 队列
         3 根据队列内容 判定是否投切
         4 执行投切
         5 每s 执行1次
 ******************************************************************************/
void Cap_Task(void);

#endif


/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/

