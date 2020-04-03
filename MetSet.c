/******************** (C) COPYRIGHT  �����㱦΢���Լ������޹�˾ **************
 * �ļ���  ��TM1629B.c
 * ����    ��TM1629 B����������
 * ʵ��ƽ̨��X963MV1
 * ��汾  ��V1.1.0
 * ����    ��Ī��  QQ��29577332
 * ����    ��
 * �Ա�    ��
 * �޸�ʱ�� ��2012-10-20
 * ע��    ��TM1629B ����C ����D
  X963MV1 Ӳ������
    |--------------------|
    |  DIO-PC1          |
    |  CLK-PC2          |
    |  STB-PC3          |
    |--------------------|

*******************************************************************************/

/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "MetSet.h"

/* �Զ��������� */

/* �Զ���� */


/* ȫ�ֱ������� */



/*******************************************************************************
 * ����: delay_xus
 * ����: 1��С�͵���ʱ����
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void delay_xus(void)
{
    unsigned char i;
    for(i = 0; i < 20; i++)
        asm("nop");
}


/*******************************************************************************
 * ����: MemoryCopy
 * ����: ��������
 * �β�: ��
 * ����: ��
 * ˵��: 1 pDst Ŀ���ַ, pSrc Դ��ַ
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
 * ����: MemoryClear
 * ����: ���ָ��ָ�������
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void MemoryClear(unsigned char *pMemory, unsigned short wCountWord)
{
    while(wCountWord--) *pMemory++ = 0;
}


/*******************************************************************************
 * ����: Memoryfill
 * ����: ��ĳ���������Ŀ��ram
 * �β�: ��
 * ����: ��
 * ˵��: ��
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
 * ����: Memory compare
 * ����: ���ݱȽ�
 * �β�: ��
 * ����: 0 ȫ����ͬ 1,-1�в���ͬ
 * ˵��: ��
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

// �ֶ��г�һ������
void HandCutCap(void)
{
	INT16U wTemp = 0;

	wTemp |= F_DELC3;
	ActUseCutCap(wTemp,TRUE);
}

// �ֶ�Ͷ��һ������
void HandUseCap(void)
{
	INT16U wTemp = 0;

	wTemp |= F_SELC3;
	ActUseCutCap(wTemp,TRUE);
}


// �¶ȵķ�Χ��
// -199 ��999
// ��ʾΪ-19.9 ��99.9
// ��������ֵΪ-19 ��99
// ��ʾΪ-19 ��99
// �ز�ֵΪ1 ��20
// ��ʾΪ1 ��20

// ʪ�ȵķ�Χ��
// 0 ��999
// ��ʾΪ0 ��99
// ��������ֵΪ0 ��99
// ��ʾΪ0 ��99
// �ز�ֵΪ1 ��20
// ��ʾΪ1 ��20

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


// ���ò˵�
const INT8U CHR_NoI[][3] =
{
    DS_Chr_N,	DS_Chr_o,	DS_Chr_1,
};

// ��ӭ����
const INT8U CHR_DC[][3] =
{   
    DS_Chr_d,   DS_Chr_Neg, DS_Chr_c,
};

// У׼1����
const INT8U CHR_A1[][3] =
{   
    DS_Chr_A,   DS_Chr_Neg, DS_Chr_1,
};
// У׼1 ok
const INT8U CHR_E1[][3] =
{   
    DS_Chr_E,   DS_Chr_Neg, DS_Chr_1,
};

// У׼2 ����
const INT8U CHR_A2[][3] =
{   
    DS_Chr_A,   DS_Chr_Neg, DS_Chr_2,
};
// У׼2 ok
const INT8U CHR_E2[][3] =
{   
    DS_Chr_E,   DS_Chr_Neg, DS_Chr_2,
};

// У׼3 ����
const INT8U CHR_A3[][3] =
{   
    DS_Chr_A,   DS_Chr_Neg, DS_Chr_3,
};
// У׼3 ok
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



// 0x1001 Ĭ�Ϲ���������ʾ�����������ʾΪnoU noI 
// 0x2001 ����·��
// 0x2002 Ͷ����ʱ
// 0x2003 pf ��ֵ
// 0x2004 ��ѹ ��ֵ
// 0x2005 Ƿ�� ��ֵ
// 0x2006 �ֶ�/�Զ�
// 0x3001 ����1 ����
// 0x3002 ����2 ��ѹ



// ���ﴦ�������ʾ�������
// ��������ʾ��������ms�ж��е���
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
        cPrt = 0x1001;      // ָ�����
    return 0;
}


static void SetMenu(uint8_t cKey)                // ���ø����û�����
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
            HandUseCap();               // Ͷһ��     
            CapOutCon();                // ���������  
        }
        else if(F_KeySub == cKey)
        {
            HandCutCap();               // ��һ��
            CapOutCon();                // ���������  
        }
    }
    break;
    default:
        break;
    }

}


/*******************************************************************************
 * ����: KeyScan
 * ����: ɨ��1629 �İ������ݲ�ת��ΪԤ���ĸ�ʽ
 * �β�: ��
 * ����: key -> ɨ������
 * ˵��: 1 setkey  ks1<>k0 key[0].3
         2 addkey  ks2<>k0 key[0].7
         3 subkey  ks3<>k0 key[1].3
 ******************************************************************************/
// unsigned char  s_bLastKeyState;     // �ϴΰ�����ɨ��ֵ
// unsigned char  g_bKey1Delay;        // set������Ҫһ��С����ʱ
// unsigned int  g_iNoKeyDelay;       // �ް����ķ���
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
        DM.sRelayTime.cNullTime = 1;        // �ް���ʱ��ʼ����ʱ
    
    if(DM.sRelayTime.cNullTime >= NULLTIMENUM)
    {
        x |= F_KeyNull;
        DM.sRelayTime.cNullTime = 0;
    }
    return x;
}


/*******************************************************************************
 * ����: Key_Task
 * ����: ���ݰ�����������ʾ��ͬ�Ĳ˵�
 * �β�: ��
 * ����: ��
 * ˵��: ��
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
    if((DM.sDspCtr.PagePtr & 0xf000) == 0x1000)            //����������ʾ�˵�
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
    else if((DM.sDspCtr.PagePtr & 0xf000) == 0x2000)            // ������ʾ�˵�
    {
        switch(cKeyValue)
        {
            case    F_KeySet:
            {
                if((DM.sDspCtr.PagePtr & 0x000f) <= MAXSETMENU)
                    DM.sDspCtr.PagePtr += 1;
                if((DM.sDspCtr.PagePtr & 0x000f) > MAXSETMENU)		// �������һ���˵�
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
 * ����: Selfdetect
 * ����: ���ݵ�ǰ������ʾ
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void Selfdetect(void)
{   
   Config2BCD();
   Data2BCD();
   DisDataFill(0x4001);     // ��ʾdc
   delayX10ms(150);
   DisDataFill(0x4002);     // ��ʾver 
   delayX10ms(150);
   DisDataFill(0x4003);     // ��ʾ��������
   delayX10ms(150);
   DisDataFill(0x3001);     // ��ʾ ����У׼ֵ
   delayX10ms(150);
   DisDataFill(0x3002);     // ��ʾ ��ѹУ׼ֵ
   delayX10ms(150);
}


/*******************************************************************************
 * ����: delayX10ms
 * ����: ���ձ�׼10msΪ��㣬��ʱ�涨��ʱ��
 * �β�: ��
 * ����: ��
 * ˵��: 1 DM.sRelayTime.wDelayTime ��������ж���ִ��--
         2 ʱ���жϱ����
         3 ��ʱ���ܳ������Ź��Ķ���ʱ��
 ******************************************************************************/
void delayX10ms(unsigned int time)

{
    DM.sRelayTime.wDelayTime = time;
    while (DM.sRelayTime.wDelayTime);
}


/*******************************************************************************
 * ����: AutoAdjust
 * ����: �Զ�У׼ U I PF
 * �β�: ��
 * ����: ��
 * ˵��: ��
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
            ReadVcosVsin(0);                // ��������ʱ����0��
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


/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/

