/*************** (C) COPYRIGHT 杭州中深电力技术技术有限公司 ******************
 * 文件名  ：config.c
 * 描述    ：无功补偿控制器 的 控制配置文件
 * 实验平台：JKG
 * 库版本  ：V2.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 修改时间 ：xxxx-xx-xx
*******************************************************************************/

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "Config.h"

/* 自定义新类型 */

/* 自定义宏 */

/* 全局变量定义 */

/*******************************************************************************
 * 名称: Config_Task
 * 功能: 根据当前电力信号计算并处理，当前的状态
 * 形参: 无
 * 返回: 无
 * 说明: 无
         1 计算本周期电容器的投切结果
 ******************************************************************************/
void Config_Task(void)
{
    INT8U i;
    INT16U lTemp;

    // 电容器的容量和类型填充
    for(i=0;i<SM.sConfig.c3CupNumber;i++)
    {
        DM.sCapPara[i].cCapKind = C3_KIND;     // 共补
        DM.sCapPara[i].cCapSize = 1;        // 共补程序无需容量，直接填1
    }
    
	// 电容投切次数
    // 如任何一个电容使用次数超过10000次,就清空

	for(i=0; i<SM.sConfig.c3CupNumber; i++)				// 共补
	{
		lTemp = lTemp + DM.sCapPara[i].wCapUseNum;
	}
	if(lTemp > 10000)					// 投切次数到一定的次数就清零
	{
		for(i=0; i<SM.sConfig.c3CupNumber; i++)
			DM.sCapPara[i].wCapUseNum = 0;
	}

    // 计算过压点
    // x > y*1.20
	if(TRUE == DM.sStateSet.cOverVAlarm)	
	{
		if(DM.sElecPara.UU < (SM.sConfig.XiaoZun2 * (((float)(SM.sConfig.wOverVoltage+100))/100)) - VOVERHYSTER)		// 滞回一下
			 DM.sStateSet.cOverVAlarm = FALSE;
	}
	else 
	{
		if(DM.sElecPara.UU > (SM.sConfig.XiaoZun2 * (((float)(SM.sConfig.wOverVoltage+100))/100)))		// 过压
			DM.sStateSet.cOverVAlarm = TRUE;
	}

// 欠压
	if(DM.sElecPara.UU < 400)
		DM.sStateSet.cLowUAlarm = TRUE;
	else
		DM.sStateSet.cLowUAlarm = FALSE;

// 超前滞后
	if(DM.sElecPara.Cos > 100)					// 超前
	{
		DM.sStateSet.cOverCupAlarm = TRUE;
		DM.sStateSet.cLossCupAlarm = FALSE;
	}
	else
	{
		DM.sStateSet.cOverCupAlarm = FALSE;
		DM.sStateSet.cLossCupAlarm = TRUE;
	}

//小电流
// x > y*0.02
	if(DM.sElecPara.II < (SM.sConfig.XiaoZun1 * (((float)(SM.sConfig.cLowILimit))/100)))   
		DM.sStateSet.cLowIAlarm = TRUE;
	else if(DM.sElecPara.II > (SM.sConfig.XiaoZun1 * (((float)(SM.sConfig.cLowILimit+2))/100)))
		DM.sStateSet.cLowIAlarm = FALSE;

// 无电流
	if(DM.sElecPara.II < 4)
		DM.sStateSet.cNoIAlarm = TRUE;
	else
		DM.sStateSet.cNoIAlarm = FALSE;
}



/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/



