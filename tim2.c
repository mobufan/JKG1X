/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� **************
 * �ļ���  ��tim2.c
 * ����    ��TIM2��ʱ��PWM�������ú�����
 * ʵ��ƽ̨�����STM8������
 * ��汾  ��V2.1.0
 * ����    �����  QQ��779814207
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 *�޸�ʱ�� ��2012-11-12

  ���STM8������Ӳ������
    |-------------------------|
    |  ������ - PD4(TIM2_CH1) |
    |  LED4-PD3(TIM2_CH2)     |
    |-------------------------|

*******************************************************************************/

/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "tim2.h"
/* �Զ��������� */

/* �Զ���� */
#define HSE_CLK
//#define HSI_CLK
/* ȫ�ֱ������� */
static  u32 TimingDelay; /* ����ֵ */
/*******************************************************************************
 * ����: Tim2_Timer_Init
 * ����: TIM2��ʱ����ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: TIM2��ʱ����ʱʱ�����
         ʹ���ⲿ8MHz:
         BaseTime_Max=1/(8000000/32768)*(65535+1)=89.478s
         BaseTime_Min=1/8000000*(1+1)=0.083us
         ʹ���ڲ���16MHz
         BaseTime_Max=1/(16000000/32768)*(65535+1)=134.217s
         BaseTime_Min=1/16000000*(1+1)=0.125us
         ���ʹ���ⲿ24MHz���������#define HSE_CLK����#define HSI_CLKע������
         ���ʹ���ⲿ24MHz���������#define HSI_CLK����#define HSE_CLKע������
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
 * ����: Tim2_Stop
 * ����: TIM2��ʱ���������ر�
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void Tim2_Stop(void)
{
    TIM2_Cmd(DISABLE);
}


/*******************************************************************************
 * ����: Tim2_Start
 * ����: TIM2��ʱ������������
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void Tim2_Start(void)
{
    TIM2_Cmd(ENABLE);
}



//*******��ȡ��Ƶ����ֵ********
uint32_t GetDn(uint32_t baud)
{
    uint32_t ClkDiv = 0, dn = 0;

    ClkDiv = 8000000;
    dn = ClkDiv / baud - 1;
    return dn;
}


/*******************************************************************************
 * ����: TC2_Switch
 * ����: TIM2��ʱ��ʹ�ܿ���
 * �β�: ��
 * ����: ��
 * ˵��: ��
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
        /* Ĭ��
            TIM2_TimeBaseInit(TIM2_PRESCALER_1 ,GetDn(baud));
            TIM2_PrescalerConfig(TIM2_PRESCALER_1,TIM2_PSCRELOADMODE_IMMEDIATE);

            TIM2_ARRPreloadConfig(ENABLE);
            TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);
            TIM2_Cmd(ENABLE);
        */
        /*
        //    x = GetDn(baud);
        //    TIM2->IER = 0x00;
        //    TIM2->SR1 = 0x00;       //���ж�
        //    TIM2->PSCR = 0;             // ��Ƶϵ��
        //    TIM2->CNTRH = 0;
        //    TIM2->CNTRL = 0;
        //    TIM2->EGR = 0x01;
        //    TIM2->ARRH = (uint8_t)(x >> 8);
        //    TIM2->ARRH = (uint8_t)(x);
            TIM2->CR1 = 0x01;       // ���ж�
        //    TIM2->EGR = 0x01;
        //    while((TIM2->SR1&0x01)==0);
        //    if(TIM2->SR1)
        //        TIM2->SR1 = 0x0;
            TIM2->IER = 0x01;
            */

        //        TIM2_ITConfig(TIM2_IT_UPDATE , DISABLE);            // ���ж�
        //        TIM2_SetCounter(1);
        //        TIM2_TimeBaseInit(TIM2_PRESCALER_1 ,GetDn(baud));
        //        TIM2_GenerateEvent(TIM2_EVENTSOURCE_UPDATE);        //����һ���ж�

        //        TIM2_ClearITPendingBit(TIM2_IT_UPDATE);            // ����ж�
        //        TIM2_UpdateRequestConfig(TIM2_UPDATESOURCE_REGULAR);    //��������Դ
        //        TIM2_ARRPreloadConfig(ENABLE);

        TIM2_Cmd(ENABLE);                                               // ������ʱ��
        TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);             // ���ж�
    }
    else //disable tc2
    {
        TIM2_Cmd(DISABLE);
        TIM2_ITConfig(TIM2_IT_UPDATE , DISABLE);            // ���ж�
        TIM2_ClearITPendingBit(TIM2_IT_UPDATE);            // ����ж�
    }
    return;
}



/*******************************************************************************
 * ����: Delay_ms
 * ����: ��ʱ����
 * �β�: n10ms -> ��msΪ���������ʱ
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void Delay_ms(u16 nms)
{

    TimingDelay = nms;

    while(TimingDelay != 0)
        ;
}



/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ********************/
