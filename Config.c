/*************** (C) COPYRIGHT ����������������������޹�˾ ******************
 * �ļ���  ��config.c
 * ����    ���޹����������� �� ���������ļ�
 * ʵ��ƽ̨��JKG
 * ��汾  ��V2.1.0
 * ����    ��Ī��  QQ��29577332
 * ����    ��
 * �޸�ʱ�� ��xxxx-xx-xx
*******************************************************************************/

/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "Config.h"

/* �Զ��������� */

/* �Զ���� */

/* ȫ�ֱ������� */

/*******************************************************************************
 * ����: Config_Task
 * ����: ���ݵ�ǰ�����źż��㲢������ǰ��״̬
 * �β�: ��
 * ����: ��
 * ˵��: ��
         1 ���㱾���ڵ�������Ͷ�н��
 ******************************************************************************/
void Config_Task(void)
{
    INT8U i;
    INT16U lTemp;

    // ���������������������
    for(i=0;i<SM.sConfig.c3CupNumber;i++)
    {
        DM.sCapPara[i].cCapKind = C3_KIND;     // ����
        DM.sCapPara[i].cCapSize = 1;        // ������������������ֱ����1
    }
    
	// ����Ͷ�д���
    // ���κ�һ������ʹ�ô�������10000��,�����

	for(i=0; i<SM.sConfig.c3CupNumber; i++)				// ����
	{
		lTemp = lTemp + DM.sCapPara[i].wCapUseNum;
	}
	if(lTemp > 10000)					// Ͷ�д�����һ���Ĵ���������
	{
		for(i=0; i<SM.sConfig.c3CupNumber; i++)
			DM.sCapPara[i].wCapUseNum = 0;
	}

    // �����ѹ��
    // x > y*1.20
	if(TRUE == DM.sStateSet.cOverVAlarm)	
	{
		if(DM.sElecPara.UU < (SM.sConfig.XiaoZun2 * (((float)(SM.sConfig.wOverVoltage+100))/100)) - VOVERHYSTER)		// �ͻ�һ��
			 DM.sStateSet.cOverVAlarm = FALSE;
	}
	else 
	{
		if(DM.sElecPara.UU > (SM.sConfig.XiaoZun2 * (((float)(SM.sConfig.wOverVoltage+100))/100)))		// ��ѹ
			DM.sStateSet.cOverVAlarm = TRUE;
	}

// Ƿѹ
	if(DM.sElecPara.UU < 400)
		DM.sStateSet.cLowUAlarm = TRUE;
	else
		DM.sStateSet.cLowUAlarm = FALSE;

// ��ǰ�ͺ�
	if(DM.sElecPara.Cos > 100)					// ��ǰ
	{
		DM.sStateSet.cOverCupAlarm = TRUE;
		DM.sStateSet.cLossCupAlarm = FALSE;
	}
	else
	{
		DM.sStateSet.cOverCupAlarm = FALSE;
		DM.sStateSet.cLossCupAlarm = TRUE;
	}

//С����
// x > y*0.02
	if(DM.sElecPara.II < (SM.sConfig.XiaoZun1 * (((float)(SM.sConfig.cLowILimit))/100)))   
		DM.sStateSet.cLowIAlarm = TRUE;
	else if(DM.sElecPara.II > (SM.sConfig.XiaoZun1 * (((float)(SM.sConfig.cLowILimit+2))/100)))
		DM.sStateSet.cLowIAlarm = FALSE;

// �޵���
	if(DM.sElecPara.II < 4)
		DM.sStateSet.cNoIAlarm = TRUE;
	else
		DM.sStateSet.cNoIAlarm = FALSE;
}



/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/



