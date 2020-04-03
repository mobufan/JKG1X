/******************** (C) COPYRIGHT  �����㱦΢���Լ������޹�˾ **************
 * �ļ���  ��AssistModule.c
 * ����    ������ģ��Ĺ��� 1����2����3����
 * ʵ��ƽ̨��X963MV1
 * ��汾  ��V1.1.0
 * ����    ��Ī��  QQ��29577332
 * ����    ��
 * �Ա�    ��
 * �޸�ʱ�� ��2015-08-13
 * ע��    ��1 

  X963MV1 Ӳ������
*******************************************************************************/
/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "AssistModule.h"

/* �Զ��������� */

/* �Զ���� */


/* ȫ�ֱ������� */




/*******************************************************************************
 * ����: RunTestLed
 * ����: �����趨ֵ����������led
 * �β�:
 * ����: 1 true led�Ѿ���������
         2 false �趨ֵ�Ѿ����� 
 * ˵��: 1
  ******************************************************************************/
void RunTestLed_Task(void)
{
}



/*******************************************************************************
 * ����: Get_VerAndFunction
 * ����: ��ȡ��ǰ����Ĺ��ܺźͰ汾��
 * �β�: ��
 * ����: ��
 * ˵��: ��
         1 ���ܺ�4 ��ʾ ���Զ๦�ܱ� �п�����96 Ҳ������72 Ҳ������42
         2 ����汾�� Ϊϵͳ����
 ******************************************************************************/
static unsigned int Get_VerAndFunction(void)

{
    unsigned int number;

    number = Fuction;
    number = number<<8;
    number = number|Version;
    return number;
}

/*******************************************************************************
 * ����: AssistMod_Init
 * ����: ����ģ���ʼ�� 1�̵��� 2���Ե�
 * �β�:
 * ����: ��
 * ˵��: 1
  ******************************************************************************/
void AssistMod_Init(void)
{
//        unsigned char temp = 0;
        //gpio ��ʼ��
        // �̵������
        GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOD, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_WriteLow(GPIOD, GPIO_PIN_2);
        GPIO_WriteLow(GPIOD, GPIO_PIN_3);
        GPIO_WriteLow(GPIOD, GPIO_PIN_4);
        GPIO_WriteLow(GPIOD, GPIO_PIN_5);
        GPIO_WriteLow(GPIOD, GPIO_PIN_6);
        GPIO_WriteLow(GPIOD, GPIO_PIN_7);

        GPIO_Init(GPIOE, GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOE, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOE, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOE, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_WriteLow(GPIOE, GPIO_PIN_0);
        GPIO_WriteLow(GPIOE, GPIO_PIN_1);
        GPIO_WriteLow(GPIOE, GPIO_PIN_2);
        GPIO_WriteLow(GPIOE, GPIO_PIN_3);

        GPIO_Init(GPIOG, GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_Init(GPIOG, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_SLOW);
        GPIO_WriteLow(GPIOG, GPIO_PIN_0);
        GPIO_WriteLow(GPIOG, GPIO_PIN_1);

        // ���Ե�����

        
        GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);

        // ���Ե����
//        #ifdef debugAD
//        GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_SLOW);
//        #else
//        GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
//        #endif


        // �������� PB0<=I, PB1<=U
        GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_PU_NO_IT);
        GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);
        
}


// PA3 PB0 PB1 PB6 PB7 PC6 PC7 PD0 PD7 PE3 PG0 PG1
// ����gpio��ʼ��
// emc Ҫ�����ܽ� ����Ϊ����͵�ƽ

/*******************************************************************************
 * ����: NullIO_Init
 * ����: ����gpio��ʼ��
 * �β�: 
 * ����: ��
 * ˵��: 1 PA1-3 PB4-7 PC1-6 PD0 
 *       2 PE3 5 6 7
  ******************************************************************************/
void NullIO_Init(void)
{
    //GpioA ��ʼ��
    GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOA,GPIO_PIN_1);
    GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOA,GPIO_PIN_2);
    GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOA,GPIO_PIN_3);

    //GpioB ��ʼ��
    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_4);
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_5);
    GPIO_Init(GPIOB, GPIO_PIN_6, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_6);
    GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_7);

    //GpioC ��ʼ��
    GPIO_Init(GPIOC, GPIO_PIN_1, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOC,GPIO_PIN_1);
    GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOC,GPIO_PIN_2);
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOC,GPIO_PIN_3);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOC,GPIO_PIN_4);
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOC,GPIO_PIN_5);
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOC,GPIO_PIN_6);

    //GpioD ��ʼ��
    GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOD,GPIO_PIN_0);

    //GpioE ��ʼ��
    GPIO_Init(GPIOE, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOE,GPIO_PIN_5);
    GPIO_Init(GPIOE, GPIO_PIN_6, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOE,GPIO_PIN_6);
    GPIO_Init(GPIOE, GPIO_PIN_7, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOE,GPIO_PIN_7);
}


/*******************************************************************************
 * ����: SaveFlash
 * ����: �����Ǳ��������ݵ�ee��
 * �β�: ��
 * ����: ��
 * ˵��: 1
 ******************************************************************************/
void SaveFlash(void)
{
    unsigned char i;
    unsigned char *pSM;
    unsigned int addr = 0x4000;

    FLASH_DeInit();
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    pSM = (unsigned char *)&SM.sConfig;
    for(i = 0; i < sizeof(SM.sConfig); i++)
    {
        FLASH_ProgramByte(addr, *pSM);
        addr++;
        pSM++;
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}


/*******************************************************************************
 * ����: ����ϵͳ �Ĳ����洢���Ƿ�����
 * ����: ����ϵͳ ��1�������洢���Ƿ����󲢷�����ȷ�Ĳ�����
 * �β�: ��
 * ����: True(eeprom1��),False(������)
 * ˵��: true ��ʾ 1������
         false ��ʾ ��Ҫʹ�ó�����
 ******************************************************************************/
unsigned char CheckSysEePara(void)
{
    unsigned char *pSM, i;
    unsigned int addr = 0x4000;
    pSM = (unsigned char *)&SM.sConfig;
    for(i = 0; i < sizeof(SM.sConfig); i++)
    {
        *pSM = FLASH_ReadByte(addr);
        addr++;
        pSM++;
    }
    if((SM.sConfig.c3CupNumber > CAPNUMBER_MAX) || (SM.sConfig.c3CupNumber < CAPNUMBER_MIN))   return FALSE;
    if((SM.sConfig.cCupDelayTime > ACTDELAY_MAX) || (SM.sConfig.cCupDelayTime < ACTDELAY_MIN))   return FALSE;
    if((SM.sConfig.cPfLimit > PFTH_MAX) || (SM.sConfig.cPfLimit < PFTH_MIN))   return FALSE;
    if((SM.sConfig.wOverVoltage > OVERV_MAX) || (SM.sConfig.wOverVoltage < OVERV_MIN))   return FALSE;
    if(SM.sConfig.cLowILimit > LIMITI_MAX )   return FALSE;
    return TRUE;       // Ҫ���ȡeeprom ������

}



/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/

