/*************** (C) COPYRIGHT 杭州中深电力技术技术有限公司 ******************
 * 文件名  ：xxxx.c
 * 描述    ：xxxxxx  无功补偿控制器
 * 实验平台：xxxxxxxx
 * 库版本  ：V2.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 修改时间 ：xxxx-xx-xx
*******************************************************************************/



/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "CapTask.h"

/* 自定义新类型 */

/* 自定义宏 */

// 电容的输出控制
#define	USE_CAP1		(GPIO_WriteHigh(GPIOD, GPIO_PIN_7))
#define	USE_CAP2		(GPIO_WriteHigh(GPIOD, GPIO_PIN_6))
#define	USE_CAP3		(GPIO_WriteHigh(GPIOD, GPIO_PIN_5))
#define	USE_CAP4		(GPIO_WriteHigh(GPIOD, GPIO_PIN_4))
#define	USE_CAP5		(GPIO_WriteHigh(GPIOD, GPIO_PIN_3))
#define	USE_CAP6		(GPIO_WriteHigh(GPIOD, GPIO_PIN_2))
#define	USE_CAP7		(GPIO_WriteHigh(GPIOE, GPIO_PIN_0))
#define	USE_CAP8		(GPIO_WriteHigh(GPIOE, GPIO_PIN_1))
#define	USE_CAP9		(GPIO_WriteHigh(GPIOE, GPIO_PIN_2))
#define	USE_CAP10		(GPIO_WriteHigh(GPIOE, GPIO_PIN_3))
#define	USE_CAP11		(GPIO_WriteHigh(GPIOG, GPIO_PIN_1))
#define	USE_CAP12		(GPIO_WriteHigh(GPIOG, GPIO_PIN_0))

#define	CUT_CAP1		(GPIO_WriteLow(GPIOD, GPIO_PIN_7))
#define	CUT_CAP2		(GPIO_WriteLow(GPIOD, GPIO_PIN_6))
#define	CUT_CAP3		(GPIO_WriteLow(GPIOD, GPIO_PIN_5))
#define	CUT_CAP4		(GPIO_WriteLow(GPIOD, GPIO_PIN_4))
#define	CUT_CAP5		(GPIO_WriteLow(GPIOD, GPIO_PIN_3))
#define	CUT_CAP6		(GPIO_WriteLow(GPIOD, GPIO_PIN_2))
#define	CUT_CAP7		(GPIO_WriteLow(GPIOE, GPIO_PIN_0))
#define	CUT_CAP8		(GPIO_WriteLow(GPIOE, GPIO_PIN_1))
#define	CUT_CAP9		(GPIO_WriteLow(GPIOE, GPIO_PIN_2))
#define	CUT_CAP10		(GPIO_WriteLow(GPIOE, GPIO_PIN_3))
#define	CUT_CAP11		(GPIO_WriteLow(GPIOG, GPIO_PIN_1))
#define	CUT_CAP12		(GPIO_WriteLow(GPIOG, GPIO_PIN_0))

/* 全局变量定义 */

/*******************************************************************************
 * 名称: CapOutCon
 * 功能: 根据当前电容状态,输出到CPU 的相应管脚上。
 * 形参: 无
 * 返回: 无
 * 说明: 1 直接的硬件输出，
         2 本函数需要有相应的 port的初始化过程。
 ******************************************************************************/
void CapOutCon(void)
{
	if(FALSE == DM.sCapPara[0].cCapSatae)		CUT_CAP1;	
	else		USE_CAP1;
	if(FALSE == DM.sCapPara[1].cCapSatae)		CUT_CAP2;	
	else		USE_CAP2;
	if(FALSE == DM.sCapPara[2].cCapSatae)		CUT_CAP3;	
	else		USE_CAP3;
	if(FALSE == DM.sCapPara[3].cCapSatae)		CUT_CAP4;	
	else		USE_CAP4;
	if(FALSE == DM.sCapPara[4].cCapSatae)		CUT_CAP5;	
	else		USE_CAP5;
	if(FALSE == DM.sCapPara[5].cCapSatae)		CUT_CAP6;	
	else		USE_CAP6;
	if(FALSE == DM.sCapPara[6].cCapSatae)		CUT_CAP7;	
	else		USE_CAP7;
	if(FALSE == DM.sCapPara[7].cCapSatae)		CUT_CAP8;	
	else		USE_CAP8;
	if(FALSE == DM.sCapPara[8].cCapSatae)		CUT_CAP9;	
	else		USE_CAP9;
	if(FALSE == DM.sCapPara[9].cCapSatae)		CUT_CAP10;	
	else		USE_CAP10;
	if(FALSE == DM.sCapPara[10].cCapSatae)		CUT_CAP11;	
	else		USE_CAP11;
	if(FALSE == DM.sCapPara[11].cCapSatae)		CUT_CAP12;	
	else		USE_CAP12;
}

/*********************************************************************
*
* 函 数 名: FindCap_FrontUse
* 功能描述: 判断最靠前的电容器
* 函数说明: 判断可以使用或切除的电容器中最靠前的
* 调用函数: 无
* 全局变量: DM.sCapPara[i].cCapKind
* 输 入: cCapkind   电容的种类
                 cJudge 判定的条件(已投入 or 已切除)
* 返 回:  number(1 - 12) 0 表示没有结果
* 设 计 者：moyi 日期：2020-02-15
* 修 改 者：moyi 日期：2020-02-15
* 版 本：
***********************************************************************/

static INT8U FindCap_FrontUse(const unsigned char  cCapKind,const unsigned char cJudge)
{
	INT8U i;
	INT8U number;
//	INT8U x;

	number = 0;
//	x = 255;
	for(i=0;i<12;i++)
	{	
		if(cCapKind == DM.sCapPara[i].cCapKind)
			if(cJudge == DM.sCapPara[i].cCapSatae)
			{
				number = i+1;
				i = 100;								// 退出循环
			}
	}
	return number;
}

/*********************************************************************
*
* 函 数 名: FindCap_LowUse
* 功能描述: 判断使用次数最少的电容器
* 函数说明: 判断可以使用或切除的电容器中使用次数最少的
* 调用函数: 无
* 全局变量: DM.sCapPara[i].cCapKind
* 输 入: cCapkind   电容的种类
                 cJudge 判定的条件(已投入 or 已切除)
* 返 回:  number(1 - 12) 0 表示没有结果
* 设 计 者：moyi 日期：2020-02-15
* 修 改 者：moyi 日期：2020-02-15
* 版 本：
***********************************************************************/

static INT8U FindCap_LowUse(const unsigned char  cCapKind,const unsigned char cJudge)
{
	INT8U i;
	INT8U number;
	INT8U x;

	number = 0;
	x = 255;
	for(i=0;i<12;i++)
	{	
		if(cCapKind == DM.sCapPara[i].cCapKind)
			if(cJudge == DM.sCapPara[i].cCapSatae)
				if(DM.sCapPara[i].wCapUseNum < x)
				{
					number = i+1;
					x = DM.sCapPara[i].wCapUseNum;
				}
	}

	return number;
	
}

// 是否有特殊情况不允许投入
static INT8U Judge_CUseOk(unsigned char cCapKind)
{
	if(C3_KIND == cCapKind)
	{
		// 过压不许用共补
		if(DM.sStateSet.cOverVAlarm)		return FALSE;

		// 欠压不许用共补
		if(DM.sStateSet.cLowUAlarm)			return FALSE;

		// 没电流不许用共补	

		if(DM.sStateSet.cNoIAlarm)			return FALSE;

		// 小电流不许用共补
		if(DM.sStateSet.cLowIAlarm)			return FALSE;

		return TRUE;				// 没有以上情况
	}

	return TRUE;
}

/*********************************************************************
*
* 函 数 名: Judge_CState
* 功能描述: 电容的使用状态的判断
* 函数说明: 判断电容是可以使用  还是 可以切除
* 调用函数: 无
* 全局变量: DM.sCapPara[i].cCapKind
* 输 入: cCapkind   电容的种类
                 cJudge 判定的条件(可投 or 可切)
* 返 回: true or false
* 设 计 者：moyi 日期：2020-02-15
* 修 改 者：moyi 日期：2020-02-15
* 版 本：
***********************************************************************/
static INT8U Judge_CState(unsigned char  cCapKind,unsigned char cJudge)
{
	INT8U i;

	if(CUSE_STATE == cJudge)
	{
		for(i=0;i<12;i++)
		{	
			if(cCapKind == DM.sCapPara[i].cCapKind)
				if(cJudge == DM.sCapPara[i].cCapSatae)
					return	TRUE;
		}
	}
	else if(CFREE_STATE == cJudge)
	{
		for(i=0;i<12;i++)
		{	
			if(cCapKind == DM.sCapPara[i].cCapKind)
				if(cJudge == DM.sCapPara[i].cCapSatae)
					if(0 == DM.sCapPara[i].cCapCool)		// 未冷却的电容也不能用
						return	TRUE;
		}
	}
	
	return FALSE;
}


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
INT8U ActUseCutCap(const INT16U wCapCon,const INT8U cMust)
{
	INT8U i;
	INT8U cResult;
	INT8U j;


	cResult = FALSE;

	if(wCapCon&F_DELC3)								// 要切c3
	{
		j = FindCap_FrontUse(C3_KIND,CUSE_STATE);		// 注意这里j的结果是1-12
		if((j < 13)&&( j > 0))
		{
			j--;
			DM.sCapPara[j].cCapSatae = CFREE_STATE;	// 切除相应的c3
			DM.sCapPara[j].cCapCool = CCOOL_TIME;		// 开启冷却
			DM.sCapPara[j].wCapUseNum++;
			if(DM.sCapPara[j].wCapUseNum > 200)		// 任意一个大于200次 就清零一次
			{
				for(i=0;i<12;i++)
					DM.sCapPara[i].wCapUseNum = 0;		
			}

			return TRUE;								// 有可切   就返回
		}
	}

	if(wCapCon&F_SELC3)								// 要投c3
	{
		j = FindCap_LowUse(C3_KIND,CFREE_STATE);

		if((j < 13)&&( j > 0))
		{
			j--;
			DM.sCapPara[j].cCapSatae = CUSE_STATE;

			DM.sCapPara[j].wCapUseNum++;
			if(DM.sCapPara[j].wCapUseNum > 200)		// 任意一个大于200次 就清零一次
			{
				for(i=0;i<12;i++)
					DM.sCapPara[i].wCapUseNum = 0;		
			}
			return TRUE;								// 有可投 就返回
		}
	}

    return cResult;
}


/*********************************************************************
*
* 函 数 名: Com_RIC
* 功能描述: 根据外界情况判定电容的投 or 切
* 函数说明: 描述了电容的投切策略
* 调用函数: Judge_CState{}
* 全局变量:  
		        3 SM.sConfig.cPfLimit;			//  功率因素门限
				4 SM.sConfig.c3Limit;			//	共补门限
* 输 入:
		// 1 总的功率因素wCos;
                 
* 返 回: 无
               全局变量	wResult
* 设 计 者：moyi 日期：2020-02-15
* 修 改 者：moyi 日期：2020-02-15
* 版 本：
***********************************************************************/

static INT16U Com_RIC( INT16U wCos)
{
	INT16U	wResult;					// 返回值
	INT16U	wPfLimit = 90;				// 临时的无功门限值		
//	INT8U	iTemp;					// 临时值
//	float		f3CLimit;				// 临时的共补门限

// 返回值清零
	wResult = 0;

// 补偿门限计算

///////////////////////////
	// 过压切除  缺相不动作

	// 没有分补要切了
	if(	TRUE == DM.sStateSet.cOverVAlarm)						// 任意一路有过压无压
	{
		if(TRUE == Judge_CState(C3_KIND,CUSE_STATE))			// 共补电容处于使用状态
		{
			wResult |= F_OVERV;								// 切除原因为过压
			wResult |= F_DELC3;							//  切除一个共补
			return wResult;
		}
	}

///////////////////////////
	// 无电流切除
	if(	TRUE == DM.sStateSet.cNoIAlarm	)
	{
		if(TRUE == Judge_CState(C3_KIND,CUSE_STATE))			// 共补电容处于使用状态
		{
			wResult |= F_NOI;							// 切除原因为无流		
			wResult |= F_DELC3;					//  切除一个共补
			return wResult;
		}
	}
	
//////////////////////////
	//欠电流封锁
	if(	TRUE == DM.sStateSet.cLowIAlarm	)  	
	{
		wResult |= F_LOWI;						// 欠电流封锁
		return wResult;
	}
	
///////////////////////////	
	// 共补投入
	if(TRUE == Judge_CState(C3_KIND, CFREE_STATE))		// 共补电容可以使用
		if(Judge_CUseOk(C3_KIND))
		if(wCos < wPfLimit)								// 共补q门限
	{
		wResult |= F_SELC3;						//投入一个共补
		return wResult;
	}

////////////////////////////	
// 共补切除
// 条件1
	if(TRUE == Judge_CState(C3_KIND, CUSE_STATE))		// 共补可以切除
		if(	wCos > CUTLIMIT)
		{
			wResult |= F_DELC3;						//  切除一个共补
			return wResult;
		}
	return wResult;
}

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
void Cap_Task(void)
{
	INT8U i;
//	INT8U cTempConCap[3];
	INT16U wTempResult;
	INT8U cTempDelay;
	INT8U j;
	INT16U x;

// 赋初值
	wTempResult = 0;

	if(	(AUTOSTATE == DM.sStateSet.cAutoState)||
		(OTHERSTATE == DM.sStateSet.cAutoState)
		)														// 辅助显示状态和自动状态才判断	
	{
		wTempResult = wTempResult;		
	}
	else															// 手动 设置及校准状态不考虑投切的事情
	{
		return ;
	}

	cTempDelay = SM.sConfig.cCupDelayTime;
	wTempResult = Com_RIC(DM.sElecPara.Cos);				// 用实时值计算 

// 判断结果填充
// x[0] 表示最近的1s 
// x[120] 表示 120s 前

// 数据相后移动一位 第一位被清空
	for(i=cTempDelay-1; i > 0; i--)
	{
		DM.sConCap.wConCap[i] = DM.sConCap.wConCap[i-1];					
	}
	DM.sConCap.wConCap[0] = wTempResult;

// end

	if(	(DM.sConCap.wConCap[0] & F_OVERV)&&
		(DM.sConCap.wConCap[1] & F_OVERV)&&
		(DM.sConCap.wConCap[2] & F_OVERV)&&
		(DM.sConCap.wConCap[3] & F_OVERV)&&
		(DM.sConCap.wConCap[4] & F_OVERV)
		)														// 连续5s过压			
	{
		if(TRUE == ActUseCutCap(DM.sConCap.wConCap[0],TRUE))		// 做动作   直接切除
		{
			for(i=0;i<cTempDelay;i++)
			{
				DM.sConCap.wConCap[i] = 0;						// 如果动作做了,清空结果区
			}
			CapOutCon();										// 电容做动作
		}
		return;													// 过压期间不考虑其它动作
	}

	if(DM.sConCap.wConCap[0] == DM.sConCap.wConCap[cTempDelay - 1])		// 第1s 和 最后1s 的结果相同
	{
		if(0 == DM.sConCap.wConCap[0])		//无动作
			return;		
		j = 0;
		for(i=0;i<cTempDelay;i++)
		{
			if(DM.sConCap.wConCap[0] == DM.sConCap.wConCap[i])
			{
				j++;
			}
		}
// 这时x表示允许抖动的次数 
		if(cTempDelay <= 10)				x = 1;
		else if(cTempDelay <= 20)			x = 2;
		else if(cTempDelay <= 30)			x = 3;
		else if(cTempDelay <= 60)			x = 4;
		else 							x = 5;
		
		if((cTempDelay - j) <= x)
		{
			if(TRUE == ActUseCutCap(DM.sConCap.wConCap[0],FALSE))	// 做动作 切除或投入 不一定有合适的投入
			{
				for(i=0;i<cTempDelay;i++)
				{
					DM.sConCap.wConCap[i] = 0;


					// 如果动作做了,清空结果区
				}
				CapOutCon();										// 电容器输出
			}
		}
	}

// 其它情况暂不处理
}




/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/



