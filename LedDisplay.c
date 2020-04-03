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
#include "LedDisplay.h"

/* �Զ��������� */

/* �Զ���� */



//ָʾ��



const uint8_t digit[] =
{
    sega | segb | segc | segd | sege | segf,
    segb | segc,
    sega | segb | segd | sege | segg,
    sega | segb | segc | segd | segg,
    segb | segc | segf | segg,
    sega | segc | segd | segf | segg,
    sega | segc | segd | sege | segf | segg,
    sega | segb | segc,
    sega | segb | segc | segd | sege | segf | segg,
    sega | segb | segc | segd | segf | segg,
    sega | segb | segc | sege | segf | segg,
    segc | segd | sege | segf | segg,
    segd | sege | segg,
    segb | segc | segd | sege | segg,
    sega | segd | sege | segf | segg,
    sega | sege | segf | segg,
    0
};

//==============================================
//��ѯ����
//================================================================
// ������ʾ�ķ���

const uint8_t Fuction = 0x40;                      // ������ܱ���
const uint8_t Version = 0x60;                      // ����汾��
const uint8_t CHR_Ver[][3] =                       //������ʱ����ʾ��˾��Ϣ��
{
    DS_Chr_u,      DS_Chr_6,       DS_Chr_0,       // v0.60
};


//--------------------------д��һ���ֽ�(8bit) ��led_ic �������--------------------------

/*******************************************************************************
 * ����: ReFlash_LED
 * ����: ����DM.sDisMem.cDispData �е�����ת���������1629����ʾ
 * �β�: ��
 * ����: ��
 * ˵��: 1 ��ʾled
         2 ��ʾ�����
         3 ����ת����Ҫ��ϸ�˶�ԭ��ͼ��1629˵����
 ******************************************************************************/
void ReFlash_LED(void)                // led ��˸����
{
    INT8U Dis1629Mem[8][2];
    INT8U i,j;

    for(i = 0; i < 8; i++)
        for(j = 0; j < 2; j++)
            Dis1629Mem[i][j] = 0;

#ifdef debugled
//    DM.sStateSet.cNoIAlarm = TRUE;
//    DM.sStateSet.cOverVAlarm = TRUE;
//    DM.sDisMem.cDispData[0] = digit[1];
//    DM.sDisMem.cDispData[1] = digit[2];
//    DM.sDisMem.cDispData[2] = digit[3];
#endif

    for(i = 0; i < 8; i++)
    {   
        if(checkbit(DM.sDisMem.cDispData[2], i))
            setbit(Dis1629Mem[i][0], 4);
        else
            clrbit(Dis1629Mem[i][0], 4);
        if(checkbit(DM.sDisMem.cDispData[1], i))
            setbit(Dis1629Mem[i][0], 5);
        else
            clrbit(Dis1629Mem[i][0], 5);
        if(checkbit(DM.sDisMem.cDispData[0], i))
            setbit(Dis1629Mem[i][0], 6);
        else
            clrbit(Dis1629Mem[i][0], 6);
    }
    if( (TRUE == DM.sStateSet.cNoIAlarm)||
        (TRUE == DM.sStateSet.cLowIAlarm)
        )
        setbit(Dis1629Mem[7][0], 3);
    if(TRUE == DM.sStateSet.cOverVAlarm)
        setbit(Dis1629Mem[3][0], 3);
    if(TRUE == DM.sStateSet.cLossCupAlarm)
        setbit(Dis1629Mem[2][0], 3);
    if(TRUE == DM.sStateSet.cOverCupAlarm)
        setbit(Dis1629Mem[4][0], 3);

    ReFlash_1629B(Dis1629Mem[0], 3, ENABLE);
}


//--------------------------ת����ʾ���� �������--------------------------


void     DispVer(void)     //��ʾ ��˾  ����İ汾����Ϣ
{

}


/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/



