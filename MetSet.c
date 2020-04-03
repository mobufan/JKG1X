/******************** (C) COPYRIGHT  杭州浙宝微电脑技术有限公司 **************
 * 文件名  ：TM1629B.c
 * 描述    ：TM1629 B的驱动函数
 * 实验平台：X963MV1
 * 库版本  ：V1.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 淘宝    ：
 * 修改时间 ：2012-10-20
 * 注意    ：TM1629B 不是C 不是D
  X963MV1 硬件连接
    |--------------------|
    |  DIO-PC1          |
    |  CLK-PC2          |
    |  STB-PC3          |
    |--------------------|

*******************************************************************************/

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "MetSet.h"

/* 自定义新类型 */

/* 自定义宏 */


/* 全局变量定义 */



/*******************************************************************************
 * 名称: delay_xus
 * 功能: 1个小型的延时程序
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void delay_xus(void)
{
    unsigned char i;
    for(i = 0; i < 20; i++)
        asm("nop");
}


/*******************************************************************************
 * 名称: MemoryCopy
 * 功能: 复制数据
 * 形参: 无
 * 返回: 无
 * 说明: 1 pDst 目标地址, pSrc 源地址
 ******************************************************************************/
void MemoryCopy(unsigned char *pDst, unsigned char *pSrc, unsigned short wSize)
{
    while(wSize--)
    {
        *pDst = *pSrc;
        pDst++, pSrc++;
    }
}


/*******************************************************************************
 * 名称: MemoryClear
 * 功能: 清除指针指向的数据
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void MemoryClear(unsigned char *pMemory, unsigned short wCountWord)
{
    while(wCountWord--) *pMemory++ = 0;
}


/*******************************************************************************
 * 名称: Memoryfill
 * 功能: 用某种数据填充目标ram
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void MemoryFill(unsigned char *Data_Ptr,unsigned int Len,unsigned char byte)
{
        while( Len>0 )
        {
            *Data_Ptr = byte;
            Data_Ptr ++;
            Len--;
        }
}

/*******************************************************************************
 * 名称: Memory compare
 * 功能: 数据比较
 * 形参: 无
 * 返回: 0 全部相同 1,-1有不相同
 * 说明: 无
 ******************************************************************************/
int  MemComp(unsigned char *Data1,unsigned char *Data2,int Len)
{
     Data1 += Len-1;
     Data2 += Len-1;
     while(Len>0)
     {
         if( (*Data1) > (*Data2) )  return 1;
         if( (*Data1) < (*Data2) )  return -1;
         Len--;
         Data1--;
         Data2--;
     }  
     return 0; 
}

// 手动切除一个电容
void HandCutCap(void)
{
	INT16U wTemp = 0;

	wTemp |= F_DELC3;
	ActUseCutCap(wTemp,TRUE);
}

// 手动投入一个电容
void HandUseCap(void)
{
	INT16U wTemp = 0;

	wTemp |= F_SELC3;
	ActUseCutCap(wTemp,TRUE);
}


// 温度的范围是
// -199 到999
// 显示为-19.9 到99.9
// 动作设置值为-19 到99
// 显示为-19 到99
// 回差值为1 到20
// 显示为1 到20

// 湿度的范围是
// 0 到999
// 显示为0 到99
// 动作设置值为0 到99
// 显示为0 到99
// 回差值为1 到20
// 显示为1 到20

static void Config2BCD(void)
{

    DM.sReal.A1_Number[0] = DS_Chr_C;
    DM.sReal.A1_Number[1] = digit[SM.sConfig.c3CupNumber/10];
    DM.sReal.A1_Number[2] = digit[SM.sConfig.c3CupNumber%10];

    DM.sReal.A2_OnOffTime[0] = DS_Chr_d;
    DM.sReal.A2_OnOffTime[1] = digit[SM.sConfig.cCupDelayTime/10];
    DM.sReal.A2_OnOffTime[2] = digit[SM.sConfig.cCupDelayTime%10];

    DM.sReal.A3_PfLimit[0] = DS_Chr_L;
    DM.sReal.A3_PfLimit[1] = digit[SM.sConfig.cPfLimit/10];
    DM.sReal.A3_PfLimit[2] = digit[SM.sConfig.cPfLimit%10];

    DM.sReal.A4_OverVLimit[0] = DS_Chr_U;
    DM.sReal.A4_OverVLimit[1] = digit[SM.sConfig.wOverVoltage/10];
    DM.sReal.A4_OverVLimit[2] = digit[SM.sConfig.wOverVoltage%10];

    DM.sReal.A5_LowILimit[0] = DS_Chr_I;
    DM.sReal.A5_LowILimit[1] = digit[SM.sConfig.cLowILimit/10];
    DM.sReal.A5_LowILimit[2] = digit[SM.sConfig.cLowILimit%10];

    DM.sReal.A6_AutoOrHand[0] = DS_Chr_t;
    DM.sReal.A6_AutoOrHand[1] = DS_Chr_S;    
    DM.sReal.A6_AutoOrHand[2] = DS_Chr_t;


    DM.sReal.B1[0] = digit[DM.sElecPara.II/100];
    DM.sReal.B1[1] = digit[(DM.sElecPara.II%100)/10];
    DM.sReal.B1[2] = digit[DM.sElecPara.II%10];

    DM.sReal.B2[0] = digit[DM.sElecPara.UU/100];
    DM.sReal.B2[1] = digit[(DM.sElecPara.UU%100)/10];
    DM.sReal.B2[2] = digit[DM.sElecPara.UU%10];
    
    DM.sReal.B3[0] = digit[DM.sElecPara.Cos/100];
    DM.sReal.B3[1] = digit[(DM.sElecPara.Cos%100)/10];
    DM.sReal.B3[2] = digit[DM.sElecPara.Cos%10];

}


// 设置菜单
const INT8U CHR_NoI[][3] =
{
    DS_Chr_N,	DS_Chr_o,	DS_Chr_1,
};

// 欢迎画面
const INT8U CHR_DC[][3] =
{   
    DS_Chr_d,   DS_Chr_Neg, DS_Chr_c,
};

// 校准1出错
const INT8U CHR_A1[][3] =
{   
    DS_Chr_A,   DS_Chr_Neg, DS_Chr_1,
};
// 校准1 ok
const INT8U CHR_E1[][3] =
{   
    DS_Chr_E,   DS_Chr_Neg, DS_Chr_1,
};

// 校准2 出错
const INT8U CHR_A2[][3] =
{   
    DS_Chr_A,   DS_Chr_Neg, DS_Chr_2,
};
// 校准2 ok
const INT8U CHR_E2[][3] =
{   
    DS_Chr_E,   DS_Chr_Neg, DS_Chr_2,
};

// 校准3 出错
const INT8U CHR_A3[][3] =
{   
    DS_Chr_A,   DS_Chr_Neg, DS_Chr_3,
};
// 校准3 ok
const INT8U CHR_E3[][3] =
{   
    DS_Chr_E,   DS_Chr_Neg, DS_Chr_3,
};

static void Data2BCD(void)
{
    uint16_t wCos;
    wCos = DM.sElecPara.Cos;
    if(wCos > 100)
        wCos = 200 - wCos;
    

    if(DM.sStateSet.cNoIAlarm)
    {
        DM.sReal.Factor[0] = CHR_NoI[0][0];
        DM.sReal.Factor[1] = CHR_NoI[0][1];
        DM.sReal.Factor[2] = CHR_NoI[0][2];
    }
    else
    {
        DM.sReal.Factor[0] = digit[0]|DS_Chr_dp;
        DM.sReal.Factor[1] = digit[wCos/10];
        DM.sReal.Factor[2] = digit[wCos%10];
    }
}



// 0x1001 默认功率因素显示，根据情况显示为noU noI 
// 0x2001 电容路数
// 0x2002 投切延时
// 0x2003 pf 限值
// 0x2004 过压 限值
// 0x2005 欠流 限值
// 0x2006 手动/自动
// 0x3001 参数1 电流
// 0x3002 参数2 电压



// 这里处理的是显示数据填充
// 真正的显示程序是在ms中断中调用
static uint8_t	DisDataFill(uint16_t	 cPrt)
{
    if(0x1001 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.Factor, 3);
    else if(0x2001 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.A1_Number, 3);
    else if(0x2002 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.A2_OnOffTime, 3);
    else if(0x2003 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.A3_PfLimit, 3);
    else if(0x2004 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.A4_OverVLimit, 3);
    else if(0x2005 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.A5_LowILimit, 3);
    else if(0x2006 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.A6_AutoOrHand, 3);
    else if(0x3001 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.B1, 3);
    else if(0x3002 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.B2, 3);
    else if(0x3003 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.B3, 3);
    else if(0x3004 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_A1, 3);
    else if(0x3005 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_E1, 3);
    else if(0x3006 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_A2, 3);
    else if(0x3007 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_E2, 3);
    else if(0x3008 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_A3, 3);
    else if(0x3009 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_E3, 3);
    else if(0x4001 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_DC, 3);
    else if(0x4002 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, (uint8_t *) &CHR_Ver, 3);
    else if(0x4003 == cPrt)
        MemoryCopy(DM.sDisMem.cDispData, DM.sReal.A1_Number, 3);
    else
        cPrt = 0x1001;      // 指针出错
    return 0;
}


static void SetMenu(uint8_t cKey)                // 设置各项用户参数
{

    
    switch(DM.sDspCtr.PagePtr & 0x000f)
    {
    case	0x0001:
    {
        if(F_KeyAdd == cKey)
        {
            if(SM.sConfig.c3CupNumber >= CAPNUMBER_MAX)
                SM.sConfig.c3CupNumber = CAPNUMBER_MAX;
            else
                SM.sConfig.c3CupNumber++;    
        }
        else if(F_KeySub == cKey)
        {
            if(SM.sConfig.c3CupNumber <= CAPNUMBER_MIN)
                SM.sConfig.c3CupNumber = CAPNUMBER_MIN;
            else
                SM.sConfig.c3CupNumber--;    
        }
    }
    break;
    case	0x0002:
    {
        if(F_KeyAdd == cKey)
        {
            
            if(SM.sConfig.cCupDelayTime >= ACTDELAY_MAX)
                SM.sConfig.cCupDelayTime = ACTDELAY_MAX;
            else
                SM.sConfig.cCupDelayTime += 10;    
        }
        else if(F_KeySub == cKey)
        {
            if(SM.sConfig.cCupDelayTime <= ACTDELAY_MIN)
                SM.sConfig.cCupDelayTime = ACTDELAY_MIN;
            else
                SM.sConfig.cCupDelayTime -= 10;
        }
    }
    break;
    case	0x0003:
    {
        if(F_KeyAdd == cKey)
        {
            if(SM.sConfig.cPfLimit >= PFTH_MAX)
                SM.sConfig.cPfLimit = PFTH_MAX;
            else
                SM.sConfig.cPfLimit++;
            
        }
        else if(F_KeySub == cKey)
        {
            
            if(SM.sConfig.cPfLimit <= PFTH_MIN)
                SM.sConfig.cPfLimit = PFTH_MIN;
            else
                SM.sConfig.cPfLimit--;
        }
    }
    break;
    case	0x0004:
    {
        if(F_KeyAdd == cKey)
        {
            if(SM.sConfig.wOverVoltage >= OVERV_MAX)
                SM.sConfig.wOverVoltage = OVERV_MAX;
            else
                SM.sConfig.wOverVoltage += 5;
        }
        else if(F_KeySub == cKey)
        {
            if(SM.sConfig.wOverVoltage <= OVERV_MIN)
                SM.sConfig.wOverVoltage = OVERV_MIN;
            else
                SM.sConfig.wOverVoltage -= 5;
        }
    }
    break;
    case	0x0005:
    {
        if(F_KeyAdd == cKey)
        {
            if(SM.sConfig.cLowILimit >= LIMITI_MAX)
                SM.sConfig.cLowILimit = LIMITI_MAX;
            else
                SM.sConfig.cLowILimit += 2;
        }
        else if(F_KeySub == cKey)
        {
            if(SM.sConfig.cLowILimit <= LIMITI_MIN)
                SM.sConfig.cLowILimit = LIMITI_MIN;
            else
                SM.sConfig.cLowILimit -= 2;
        }
    }
    break;
    case	0x0006:
    {
        if(F_KeyAdd == cKey)
        {
            HandUseCap();               // 投一个     
            CapOutCon();                // 电容器输出  
        }
        else if(F_KeySub == cKey)
        {
            HandCutCap();               // 切一个
            CapOutCon();                // 电容器输出  
        }
    }
    break;
    default:
        break;
    }

}


/*******************************************************************************
 * 名称: KeyScan
 * 功能: 扫描1629 的按键数据并转换为预定的格式
 * 形参: 无
 * 返回: key -> 扫描数据
 * 说明: 1 setkey  ks1<>k0 key[0].3
         2 addkey  ks2<>k0 key[0].7
         3 subkey  ks3<>k0 key[1].3
 ******************************************************************************/
// unsigned char  s_bLastKeyState;     // 上次按键的扫描值
// unsigned char  g_bKey1Delay;        // set按键需要一个小的延时
// unsigned int  g_iNoKeyDelay;       // 无按键的返回
static unsigned char KeyScan(void)
{
    INT8U key[4];
    INT8U x = 0;
    Read_1629BKey(key);
    if(checkbit(key[0], 3))
        x |= F_KeySet;
    if(checkbit(key[0], 7))
        x |= F_KeyAdd;
    if(checkbit(key[1], 3))
        x |= F_KeySub;

    if(x == 0)
        DM.sRelayTime.cNullTime = 1;        // 无按键时开始倒计时
    
    if(DM.sRelayTime.cNullTime >= NULLTIMENUM)
    {
        x |= F_KeyNull;
        DM.sRelayTime.cNullTime = 0;
    }
    return x;
}


/*******************************************************************************
 * 名称: Key_Task
 * 功能: 根据按键的输入显示不同的菜单
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Key_Task(void)
{
    unsigned char cKeyValue;

    cKeyValue = 0;
//    keyx = 0;

//    #ifdef debugled
//    DM.sElecPara.Cos++;
//    #endif
    cKeyValue = KeyScan();
    if((DM.sDspCtr.PagePtr & 0xf000) == 0x1000)            //常规数据显示菜单
    {
        switch(cKeyValue)
        {
            case    F_KeySet:
            {
                DM.sDspCtr.PagePtr = 0x2001;
            }
            break;
            
            default:
            break;
        }
    }
    else if((DM.sDspCtr.PagePtr & 0xf000) == 0x2000)            // 设置显示菜单
    {
        switch(cKeyValue)
        {
            case    F_KeySet:
            {
                if((DM.sDspCtr.PagePtr & 0x000f) <= MAXSETMENU)
                    DM.sDspCtr.PagePtr += 1;
                if((DM.sDspCtr.PagePtr & 0x000f) > MAXSETMENU)		// 处于最后一个菜单
                {
                    DM.sDspCtr.PagePtr = AUTO_MENU;
                }
            }                
            break;
            case	F_KeyAdd:
            case	F_KeySub:
            {
                SetMenu(cKeyValue);
                DM.cSysFlg |= F_FlashNew;
            }
            break;
            default:
            break;
        }
    }
    Config2BCD();
    Data2BCD();
    DisDataFill(DM.sDspCtr.PagePtr);
}


/*******************************************************************************
 * 名称: Selfdetect
 * 功能: 根据当前参数显示
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Selfdetect(void)
{   
   Config2BCD();
   Data2BCD();
   DisDataFill(0x4001);     // 显示dc
   delayX10ms(150);
   DisDataFill(0x4002);     // 显示ver 
   delayX10ms(150);
   DisDataFill(0x4003);     // 显示电容数量
   delayX10ms(150);
   DisDataFill(0x3001);     // 显示 电流校准值
   delayX10ms(150);
   DisDataFill(0x3002);     // 显示 电压校准值
   delayX10ms(150);
}


/*******************************************************************************
 * 名称: delayX10ms
 * 功能: 按照标准10ms为格点，延时规定的时间
 * 形参: 无
 * 返回: 无
 * 说明: 1 DM.sRelayTime.wDelayTime 必须放在中断中执行--
         2 时间中断必须打开
         3 延时不能超过看门狗的动作时间
 ******************************************************************************/
void delayX10ms(unsigned int time)

{
    DM.sRelayTime.wDelayTime = time;
    while (DM.sRelayTime.wDelayTime);
}


/*******************************************************************************
 * 名称: AutoAdjust
 * 功能: 自动校准 U I PF
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void AutoAdjust(void)
{
    unsigned char ckey;
    unsigned char i,j,p;
    ckey = 0x0;

    for(i=0; i<2; i++)
    {
        delayX10ms(50);
        DM.sStateSet.cNoIAlarm = TRUE;
        DM.sStateSet.cOverVAlarm = TRUE;
        Data2BCD();
        Config2BCD();
        DisDataFill(0x3001);
        if(RESET == GPIO_ReadInputPin(GPIOC, GPIO_PIN_7))
        {
            ckey == 0x55;
            break;
        }
        delayX10ms(50);
        DM.sStateSet.cNoIAlarm = FALSE;
        DM.sStateSet.cOverVAlarm = FALSE;
        Data2BCD();
        Config2BCD();
        DisDataFill(0x3001);
    }
    ckey = 0x55;
    if(ckey == 0x55)
    {
        ckey = 0x00;
        for(i=0; i<3 ;i++)
        {
            delayX10ms(50);
            DM.sStateSet.cLossCupAlarm = TRUE;
            DM.sStateSet.cOverVAlarm = TRUE;
            Data2BCD();
            Config2BCD();
            DisDataFill(0x3001);
            delayX10ms(50);
            DM.sStateSet.cLossCupAlarm = FALSE;
            DM.sStateSet.cOverVAlarm = FALSE;
            Data2BCD();
            Config2BCD();
            DisDataFill(0x3001);
        }
        j = 3;
        while(j--)
        {
            ReadVcosVsin(0);                // 补偿计算时采用0度
			for(p=0;p<15;p++)
			{ 
				Start_Ad_Task();			
	     		delayX10ms(5);
                Compute_Task();
			}
            Config2BCD();
            Data2BCD();

            if((DM.sElecPara.II > 300)&&(DM.sElecPara.II < 500))
                SM.sConfig.XiaoZun1 = DM.sElecPara.II;
            else
                break;
            if((DM.sElecPara.UU > 500)&&(DM.sElecPara.UU < 700))
                SM.sConfig.XiaoZun2 = DM.sElecPara.UU;
            else
                break;
            if((DM.sElecPara.Cos >= 78)&&(DM.sElecPara.Cos < 83))
                SM.sConfig.XiaoZun3 = DM.sElecPara.Cos;
            else
                break;
            
            DisDataFill(0x3001);
            delayX10ms(100);
            DisDataFill(0x3002);
            delayX10ms(100);
            DisDataFill(0x3003);

            disableInterrupts();
            SaveFlash();
            enableInterrupts();
        }
        j = 2;
        while(j--)
        {
            unsigned char *pSM;
            unsigned int addr = 0x4000;
            pSM = (unsigned char *)&SM.sConfig;
            for(i = 0; i < sizeof(SM.sConfig); i++)
            {
                *pSM = FLASH_ReadByte(addr);
                addr++;
                pSM++;
            }
            if(DM.sElecPara.II == SM.sConfig.XiaoZun1)
                DisDataFill(0x3004);                        // A1 
            else
                DisDataFill(0x3005);                        // E1
            delayX10ms(50);
            if(DM.sElecPara.UU == SM.sConfig.XiaoZun2)
                DisDataFill(0x3006);                        // A2
            else
                DisDataFill(0x3007);                        // E2
            delayX10ms(50);
            if(DM.sElecPara.Cos == SM.sConfig.XiaoZun3)
                DisDataFill(0x3008);                        // A3
            else
                DisDataFill(0x3009);                        // E3
            delayX10ms(50);
        }
    }
}


/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/

