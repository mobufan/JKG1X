/*************** (C) COPYRIGHT ����������������������޹�˾ ******************
 * �ļ���  ��xxxx.c
 * ����    ��xxxxxx  �޹�����������
 * ʵ��ƽ̨��xxxxxxxx
 * ��汾  ��V2.1.0
 * ����    ��Ī��  QQ��29577332
 * ����    ��
 * �޸�ʱ�� ��xxxx-xx-xx
*******************************************************************************/



/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "CapTask.h"

/* �Զ��������� */

/* �Զ���� */

// ���ݵ��������
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

/* ȫ�ֱ������� */

/*******************************************************************************
 * ����: CapOutCon
 * ����: ���ݵ�ǰ����״̬,�����CPU ����Ӧ�ܽ��ϡ�
 * �β�: ��
 * ����: ��
 * ˵��: 1 ֱ�ӵ�Ӳ�������
         2 ��������Ҫ����Ӧ�� port�ĳ�ʼ�����̡�
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
* �� �� ��: FindCap_FrontUse
* ��������: �ж��ǰ�ĵ�����
* ����˵��: �жϿ���ʹ�û��г��ĵ��������ǰ��
* ���ú���: ��
* ȫ�ֱ���: DM.sCapPara[i].cCapKind
* �� ��: cCapkind   ���ݵ�����
                 cJudge �ж�������(��Ͷ�� or ���г�)
* �� ��:  number(1 - 12) 0 ��ʾû�н��
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� ����
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
				i = 100;								// �˳�ѭ��
			}
	}
	return number;
}

/*********************************************************************
*
* �� �� ��: FindCap_LowUse
* ��������: �ж�ʹ�ô������ٵĵ�����
* ����˵��: �жϿ���ʹ�û��г��ĵ�������ʹ�ô������ٵ�
* ���ú���: ��
* ȫ�ֱ���: DM.sCapPara[i].cCapKind
* �� ��: cCapkind   ���ݵ�����
                 cJudge �ж�������(��Ͷ�� or ���г�)
* �� ��:  number(1 - 12) 0 ��ʾû�н��
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� ����
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

// �Ƿ����������������Ͷ��
static INT8U Judge_CUseOk(unsigned char cCapKind)
{
	if(C3_KIND == cCapKind)
	{
		// ��ѹ�����ù���
		if(DM.sStateSet.cOverVAlarm)		return FALSE;

		// Ƿѹ�����ù���
		if(DM.sStateSet.cLowUAlarm)			return FALSE;

		// û���������ù���	

		if(DM.sStateSet.cNoIAlarm)			return FALSE;

		// С���������ù���
		if(DM.sStateSet.cLowIAlarm)			return FALSE;

		return TRUE;				// û���������
	}

	return TRUE;
}

/*********************************************************************
*
* �� �� ��: Judge_CState
* ��������: ���ݵ�ʹ��״̬���ж�
* ����˵��: �жϵ����ǿ���ʹ��  ���� �����г�
* ���ú���: ��
* ȫ�ֱ���: DM.sCapPara[i].cCapKind
* �� ��: cCapkind   ���ݵ�����
                 cJudge �ж�������(��Ͷ or ����)
* �� ��: true or false
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� ����
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
					if(0 == DM.sCapPara[i].cCapCool)		// δ��ȴ�ĵ���Ҳ������
						return	TRUE;
		}
	}
	
	return FALSE;
}


/*********************************************************************
*
* �� �� ��: ActUseCutCap
* ��������: ������������Ե���������Ͷ��
* ����˵��: 
* ���ú���: ��
* ȫ�ֱ���:  
* �� ��:
		// 1 wCapCon;			���ݵĿ��ƽ��

* �� ��:  cResult		true or false
		�ж��� ���� true
		�޶��� ���� false
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� ����
***********************************************************************/
INT8U ActUseCutCap(const INT16U wCapCon,const INT8U cMust)
{
	INT8U i;
	INT8U cResult;
	INT8U j;


	cResult = FALSE;

	if(wCapCon&F_DELC3)								// Ҫ��c3
	{
		j = FindCap_FrontUse(C3_KIND,CUSE_STATE);		// ע������j�Ľ����1-12
		if((j < 13)&&( j > 0))
		{
			j--;
			DM.sCapPara[j].cCapSatae = CFREE_STATE;	// �г���Ӧ��c3
			DM.sCapPara[j].cCapCool = CCOOL_TIME;		// ������ȴ
			DM.sCapPara[j].wCapUseNum++;
			if(DM.sCapPara[j].wCapUseNum > 200)		// ����һ������200�� ������һ��
			{
				for(i=0;i<12;i++)
					DM.sCapPara[i].wCapUseNum = 0;		
			}

			return TRUE;								// �п���   �ͷ���
		}
	}

	if(wCapCon&F_SELC3)								// ҪͶc3
	{
		j = FindCap_LowUse(C3_KIND,CFREE_STATE);

		if((j < 13)&&( j > 0))
		{
			j--;
			DM.sCapPara[j].cCapSatae = CUSE_STATE;

			DM.sCapPara[j].wCapUseNum++;
			if(DM.sCapPara[j].wCapUseNum > 200)		// ����һ������200�� ������һ��
			{
				for(i=0;i<12;i++)
					DM.sCapPara[i].wCapUseNum = 0;		
			}
			return TRUE;								// �п�Ͷ �ͷ���
		}
	}

    return cResult;
}


/*********************************************************************
*
* �� �� ��: Com_RIC
* ��������: �����������ж����ݵ�Ͷ or ��
* ����˵��: �����˵��ݵ�Ͷ�в���
* ���ú���: Judge_CState{}
* ȫ�ֱ���:  
		        3 SM.sConfig.cPfLimit;			//  ������������
				4 SM.sConfig.c3Limit;			//	��������
* �� ��:
		// 1 �ܵĹ�������wCos;
                 
* �� ��: ��
               ȫ�ֱ���	wResult
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� �� �ߣ�moyi ���ڣ�2020-02-15
* �� ����
***********************************************************************/

static INT16U Com_RIC( INT16U wCos)
{
	INT16U	wResult;					// ����ֵ
	INT16U	wPfLimit = 90;				// ��ʱ���޹�����ֵ		
//	INT8U	iTemp;					// ��ʱֵ
//	float		f3CLimit;				// ��ʱ�Ĺ�������

// ����ֵ����
	wResult = 0;

// �������޼���

///////////////////////////
	// ��ѹ�г�  ȱ�಻����

	// û�зֲ�Ҫ����
	if(	TRUE == DM.sStateSet.cOverVAlarm)						// ����һ·�й�ѹ��ѹ
	{
		if(TRUE == Judge_CState(C3_KIND,CUSE_STATE))			// �������ݴ���ʹ��״̬
		{
			wResult |= F_OVERV;								// �г�ԭ��Ϊ��ѹ
			wResult |= F_DELC3;							//  �г�һ������
			return wResult;
		}
	}

///////////////////////////
	// �޵����г�
	if(	TRUE == DM.sStateSet.cNoIAlarm	)
	{
		if(TRUE == Judge_CState(C3_KIND,CUSE_STATE))			// �������ݴ���ʹ��״̬
		{
			wResult |= F_NOI;							// �г�ԭ��Ϊ����		
			wResult |= F_DELC3;					//  �г�һ������
			return wResult;
		}
	}
	
//////////////////////////
	//Ƿ��������
	if(	TRUE == DM.sStateSet.cLowIAlarm	)  	
	{
		wResult |= F_LOWI;						// Ƿ��������
		return wResult;
	}
	
///////////////////////////	
	// ����Ͷ��
	if(TRUE == Judge_CState(C3_KIND, CFREE_STATE))		// �������ݿ���ʹ��
		if(Judge_CUseOk(C3_KIND))
		if(wCos < wPfLimit)								// ����q����
	{
		wResult |= F_SELC3;						//Ͷ��һ������
		return wResult;
	}

////////////////////////////	
// �����г�
// ����1
	if(TRUE == Judge_CState(C3_KIND, CUSE_STATE))		// ���������г�
		if(	wCos > CUTLIMIT)
		{
			wResult |= F_DELC3;						//  �г�һ������
			return wResult;
		}
	return wResult;
}

/*******************************************************************************
 * ����: Cap_Task
 * ����: ���ݵ�ǰ״̬���㲢���� ��������Ͷ��
 * �β�: ��
 * ����: ��
 * ˵��: ��
         1 ���㱾���ڵ�������Ͷ�н��
         2 Ͷ�н���� ����
         3 ���ݶ������� �ж��Ƿ�Ͷ��
         4 ִ��Ͷ��
         5 ÿs ִ��1��
 ******************************************************************************/
void Cap_Task(void)
{
	INT8U i;
//	INT8U cTempConCap[3];
	INT16U wTempResult;
	INT8U cTempDelay;
	INT8U j;
	INT16U x;

// ����ֵ
	wTempResult = 0;

	if(	(AUTOSTATE == DM.sStateSet.cAutoState)||
		(OTHERSTATE == DM.sStateSet.cAutoState)
		)														// ������ʾ״̬���Զ�״̬���ж�	
	{
		wTempResult = wTempResult;		
	}
	else															// �ֶ� ���ü�У׼״̬������Ͷ�е�����
	{
		return ;
	}

	cTempDelay = SM.sConfig.cCupDelayTime;
	wTempResult = Com_RIC(DM.sElecPara.Cos);				// ��ʵʱֵ���� 

// �жϽ�����
// x[0] ��ʾ�����1s 
// x[120] ��ʾ 120s ǰ

// ��������ƶ�һλ ��һλ�����
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
		)														// ����5s��ѹ			
	{
		if(TRUE == ActUseCutCap(DM.sConCap.wConCap[0],TRUE))		// ������   ֱ���г�
		{
			for(i=0;i<cTempDelay;i++)
			{
				DM.sConCap.wConCap[i] = 0;						// �����������,��ս����
			}
			CapOutCon();										// ����������
		}
		return;													// ��ѹ�ڼ䲻������������
	}

	if(DM.sConCap.wConCap[0] == DM.sConCap.wConCap[cTempDelay - 1])		// ��1s �� ���1s �Ľ����ͬ
	{
		if(0 == DM.sConCap.wConCap[0])		//�޶���
			return;		
		j = 0;
		for(i=0;i<cTempDelay;i++)
		{
			if(DM.sConCap.wConCap[0] == DM.sConCap.wConCap[i])
			{
				j++;
			}
		}
// ��ʱx��ʾ�������Ĵ��� 
		if(cTempDelay <= 10)				x = 1;
		else if(cTempDelay <= 20)			x = 2;
		else if(cTempDelay <= 30)			x = 3;
		else if(cTempDelay <= 60)			x = 4;
		else 							x = 5;
		
		if((cTempDelay - j) <= x)
		{
			if(TRUE == ActUseCutCap(DM.sConCap.wConCap[0],FALSE))	// ������ �г���Ͷ�� ��һ���к��ʵ�Ͷ��
			{
				for(i=0;i<cTempDelay;i++)
				{
					DM.sConCap.wConCap[i] = 0;


					// �����������,��ս����
				}
				CapOutCon();										// ���������
			}
		}
	}

// ��������ݲ�����
}




/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/



