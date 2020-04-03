/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 **************
 * 文件名  ：tim2.c
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

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "tim2.h"
/* 自定义新类型 */

/* 自定义宏 */
#define HSE_CLK
//#define HSI_CLK
/* 全局变量定义 */
static  u32 TimingDelay; /* 计数值 */
/*******************************************************************************
 * 名称: Tim2_Timer_Init
 * 功能: TIM2定时器初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: TIM2的时基定时时间计算
         使用外部8MHz:
         BaseTime_Max=1/(8000000/32768)*(65535+1)=89.478s
         BaseTime_Min=1/8000000*(1+1)=0.083us
         使用内部部16MHz
         BaseTime_Max=1/(16000000/32768)*(65535+1)=134.217s
         BaseTime_Min=1/16000000*(1+1)=0.125us
         如果使用外部24MHz晶振则添加#define HSE_CLK，把#define HSI_CLK注释起来
         如果使用外部24MHz晶振则添加#define HSI_CLK，把#define HSE_CLK注释起来
 ******************************************************************************/
void Tim2_Timer_Init(void)
{
#ifdef HSI_CLK
    /*BaseTime=1/(16000000/16)*(999+1)=1ms*/
    TIM2_TimeBaseInit(TIM2_PRESCALER_16 , 999);
    TIM2_PrescalerConfig(TIM2_PRESCALER_16, TIM2_PSCRELOADMODE_IMMEDIATE);
#endif

#ifdef HSE_CLK
    /*BaseTime=1/(24000000/8)*(2999+1)=1ms*/
    TIM2_TimeBaseInit(TIM2_PRESCALER_1 , 1666);
    TIM2_PrescalerConfig(TIM2_PRESCALER_1, TIM2_PSCRELOADMODE_IMMEDIATE);
#endif

    TIM2_ARRPreloadConfig(DISABLE);
    TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);
    TIM2_Cmd(ENABLE);


}



/*******************************************************************************
 * 名称: Tim2_Stop
 * 功能: TIM2定时器计数器关闭
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Tim2_Stop(void)
{
    TIM2_Cmd(DISABLE);
}


/*******************************************************************************
 * 名称: Tim2_Start
 * 功能: TIM2定时器计数器开启
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Tim2_Start(void)
{
    TIM2_Cmd(ENABLE);
}



//*******获取分频计数值********
uint32_t GetDn(uint32_t baud)
{
    uint32_t ClkDiv = 0, dn = 0;

    ClkDiv = 8000000;
    dn = ClkDiv / baud - 1;
    return dn;
}


/*******************************************************************************
 * 名称: TC2_Switch
 * 功能: TIM2定时器使能开关
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void TC2_Switch(uint8_t flag, uint32_t baud, uint8_t oper_mode)
{
    //    uint32_t x;

    TC2_Mode = oper_mode;

    if(flag) //enable tc2
    {
        /*
            TIM2_ARRPreloadConfig(DISABLE);
            TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);
            #ifdef debug
            TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
            #endif
            TIM2_TimeBaseInit(TIM2_PRESCALER_1 ,GetDn(baud));
            #ifdef debug
            TIM2_SetCounter(1);
            #endif
            TIM2_PrescalerConfig(TIM2_PRESCALER_1,TIM2_PSCRELOADMODE_IMMEDIATE);
            TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);
            TIM2_Cmd(ENABLE);
        */
        /* 默认
            TIM2_TimeBaseInit(TIM2_PRESCALER_1 ,GetDn(baud));
            TIM2_PrescalerConfig(TIM2_PRESCALER_1,TIM2_PSCRELOADMODE_IMMEDIATE);

            TIM2_ARRPreloadConfig(ENABLE);
            TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);
            TIM2_Cmd(ENABLE);
        */
        /*
        //    x = GetDn(baud);
        //    TIM2->IER = 0x00;
        //    TIM2->SR1 = 0x00;       //关中断
        //    TIM2->PSCR = 0;             // 分频系数
        //    TIM2->CNTRH = 0;
        //    TIM2->CNTRL = 0;
        //    TIM2->EGR = 0x01;
        //    TIM2->ARRH = (uint8_t)(x >> 8);
        //    TIM2->ARRH = (uint8_t)(x);
            TIM2->CR1 = 0x01;       // 开中断
        //    TIM2->EGR = 0x01;
        //    while((TIM2->SR1&0x01)==0);
        //    if(TIM2->SR1)
        //        TIM2->SR1 = 0x0;
            TIM2->IER = 0x01;
            */

        //        TIM2_ITConfig(TIM2_IT_UPDATE , DISABLE);            // 关中断
        //        TIM2_SetCounter(1);
        //        TIM2_TimeBaseInit(TIM2_PRESCALER_1 ,GetDn(baud));
        //        TIM2_GenerateEvent(TIM2_EVENTSOURCE_UPDATE);        //产生一次中断

        //        TIM2_ClearITPendingBit(TIM2_IT_UPDATE);            // 清空中断
        //        TIM2_UpdateRequestConfig(TIM2_UPDATESOURCE_REGULAR);    //更新请求源
        //        TIM2_ARRPreloadConfig(ENABLE);

        TIM2_Cmd(ENABLE);                                               // 启动定时器
        TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);             // 开中断
    }
    else //disable tc2
    {
        TIM2_Cmd(DISABLE);
        TIM2_ITConfig(TIM2_IT_UPDATE , DISABLE);            // 关中断
        TIM2_ClearITPendingBit(TIM2_IT_UPDATE);            // 清空中断
    }
    return;
}



/*******************************************************************************
 * 名称: Delay_ms
 * 功能: 延时函数
 * 形参: n10ms -> 以ms为间隔进行延时
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Delay_ms(u16 nms)
{

    TimingDelay = nms;

    while(TimingDelay != 0)
        ;
}



/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ********************/
