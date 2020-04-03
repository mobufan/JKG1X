/******************** (C) COPYRIGHT  �����㱦΢���Լ������޹�˾ **************
 * �ļ���  ��AD.c
 * ����    ��8209C �����ݶ�ȡ,У׼
 * ʵ��ƽ̨��X963MV1
 * ��汾  ��V1.1.0
 * ����    ��Ī��  QQ��29577332
 * ����    ��
 * �Ա�    ��
 * �޸�ʱ�� ��2015-10-20
 * ע��    ��RN8209C �����ǲ��ô��������ģ�
                        ������Ϊcpuֻ��һ�鴮�����Ա������ǲ���ioģ��ķ�ʽ����
  X963MV1 Ӳ������
    |--------------------|
    |  TXD0-PB0          |
    |  RXD0-PB1          |
    |--------------------|

*******************************************************************************/



/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "AD.h"

/* �Զ��������� */

/* �Զ���� */

#define     _10_bit       0x400
#define     _13_bit       0x2000
#define     _23_bit       0x800000
#define     _24_bit       0x1000000
#define     _27_bit       0x8000000
#define     _28_bit       0x10000000
#define     _31_bit       0x80000000
#define     _32_bit       0xFFFFFFFF


/* ȫ�ֱ������� */

/* 15 �� */
const float Vsin15[25]={0,0.0295,0.2872,0.5254,0.7277,0.8804,0.9731,0.9996,0.9579,0.8509,
                0.6859,0.4742,0.2302,-0.0295,-0.2872,-0.5254,-0.7277,-0.8804,-0.9731,
			   -0.9996,-0.9579,-0.8509,-0.6859,-0.4742,-0.2302};
const float Vcos15[25]={0,0.9996,0.9579,0.8509,0.6859,0.4742,0.2302,-0.0295,-0.2872,
                  -0.5254,-0.7277,-0.8804,-0.9731,-0.9996,-0.9579,-0.8509,
		   -0.6859,-0.4742,-0.2302,0.0295,0.2872,0.5254,0.7277,0.8804,0.9731};	


/* 0 �� */
const float Isin[25]={0,0,0.2588,0.5000,0.7071,0.8660,0.9659,1.0000,0.9659,0.8660,
                   0.7071,0.5000,0.2588,0,-0.2588,-0.5000,-0.7071,-0.8660,-0.9659,
				   -1.0000,-0.9659,-0.8660,-0.7071,-0.5000,-0.2588};
const float Icos[25]={0,1.0000,0.9659,0.8660,0.7071,0.5000,0.2588,0,-0.2588,
                   -0.5000,-0.7071,-0.8660,-0.9659,-1.0000,-0.9659,-0.8660,
				   -0.7071,-0.5000,-0.2588,0,0.2588,0.5000,0.7071,0.8660,0.9659};

INT8U k=0;
//INT8U h=0;
INT8U CollEnd = 0;

int Vresult[26];
int Iresult[26];
float Vcos[25];
float Vsin[25];


//�����ѹ�͵�������λ����ϵ��
void ReadVcosVsin(unsigned char VcossinSel)
{
	unsigned char i;
	if(VcossinSel == 0)
		for(i=0;i<25;i++)
			Vcos[i] = Vcos15[i],Vsin[i] = Vsin15[i];			//moyi modify 04.10
//	else if(VcossinSel == 1)
//		for(i=0;i<25;i++)
//			Vcos[i] = Vcos1[i],Vsin[i] = Vsin1[i];
//	else if(VcossinSel == 2)
//		for(i=0;i<25;i++)
//			Vcos[i] = Vcos15[i],Vsin[i] = Vsin15[i];
//	else if(VcossinSel == 3)
//		for(i=0;i<25;i++)
//			Vcos[i] = Vcos4[i],Vsin[i] = Vsin4[i];
//	else if(VcossinSel == 4)
//		for(i=0;i<25;i++)
//			Vcos[i] = Vcos6[i],Vsin[i] = Vsin6[i];
	else 
		for(i=0;i<25;i++)
			Vcos[i] = Vcos15[i],Vsin[i] = Vsin15[i];			//moyi modify 04.10
}


/*******************************************************************************
 * ����: Compute_Task()
 * ����: ad����������һ�μ���
 * �β�: ��
 * ����: ��
 * ˵��: 1 ��� ��ѹ ���� ��С
         2 ��� ��������
 ******************************************************************************/
void Compute_Task(void)
{
    unsigned char i;
	float ampleV,ampleI;
	//pflable=0x00;//����������ǰ��־
	float cosV,sinV,cosI,sinI,sinVI,cosVI,tempCos,ampleCos;
	float VAn=0,VBn=0,IAn=0,IBn=0;

    if(FALSE == CollEnd)        // ����δ��ɣ�ֱ���˳�
        return;

    CollEnd = FALSE;            // �����Ѽ���

    ReadVcosVsin(1);            // ��ȡ��λ����ϵ�� 15��

	for(i=1;i<25;i++)
	{
		VAn=VAn+(Vresult[i]*Vcos[i]);//��ѹ��������Ҷ�任��õ��Ļ�����cos��ķ�ֵ����ϵ����
	    VBn=VBn+(Vresult[i]*Vsin[i]);//��ѹ��������Ҷ�任��õ��Ļ�����sin��ķ�ֵ����ϵ����
	    IAn=IAn+(Iresult[i]*Icos[i]);//������������Ҷ�任��õ��Ļ�����cos��ķ�ֵ����ϵ����
	    IBn=IBn+(Iresult[i]*Isin[i]);//������������Ҷ�任��õ��Ļ�����sin��ķ�ֵ����ϵ����
	}

	ampleV=sqrt(VAn*VAn+VBn*VBn);
	ampleI=sqrt(IAn*IAn+IBn*IBn);
		 
	cosV=VBn/ampleV;//��ѹ��ǵ�cosֵ����ϵ��100
	sinV=VAn/ampleV;//��ѹ��ǵ�sinֵ
	cosI=IBn/ampleI;//������ǵ�cosֵ
	sinI=IAn/ampleI;//������ǵ�sinֵ
	sinVI=(sinV*cosI-cosV*sinI);
	cosVI=(cosV*cosI+sinV*sinI);
	if(sinVI >= 0)
	{
	    tempCos = sinVI;
	 	if(cosVI > 0)
	 		tempCos = 2 - tempCos;		//�ͺ�	
//	 		DM.sElecPara.Cos = sinVI;
	 	else
           tempCos = tempCos;		//��ǰ
//            DM.sElecPara.Cos = -sinVI;
	}
	else 
	{
	    tempCos = 0 - sinVI;
	    if(cosVI > 0)
//		    DM.sElecPara.Cos = 0-sinVI;
	 		tempCos = tempCos;		//��ǰ
        else
//            DM.sElecPara.Cos = sinVI;
			tempCos = 2 - tempCos;		//�ͺ�
	 } 
	DM.sElecTemp.TCos[9] = tempCos*1000;

	DM.sElecTemp.TUU[9] = (ampleV);			// ��ѹ��Чֵ(0000-2200)	��λ0.1V
	DM.sElecTemp.TII[9] = (ampleI);			// ������Чֵ (0000-5000)	��λ0.001As   δ����ct 

// ƽ��ֵ����	
	ampleI = 0;
	ampleV = 0;
	ampleCos = 0;
	for(i=0;i<10;i++)						// ���ƽ��ֵ
	{
		ampleI = ampleI + DM.sElecTemp.TII[i];
		ampleV = ampleV + DM.sElecTemp.TUU[i];
		ampleCos = ampleCos + DM.sElecTemp.TCos[i];
	}
    

    DM.sElecPara.UU = (ampleV + 5)/10;  // 3λ�� 4��5��
    DM.sElecPara.II = (ampleI + 5)/10;  
	DM.sElecPara.Cos = (ampleCos + 5)/10;

    CollEnd = FALSE;            // ���������ɱ�־λ����ʼ����
}

/*******************************************************************************
 * ����: ADC_Config()
 * ����: �ڲ� adc ģ�� ��ʼ��
 * �β�: ��
 * ����: ��
 * ˵��: 
        1 ���δ���ģʽ
        2 ��Ƶϵ��2
        3 �����Ҷ���
        4 AIN2=In AIN3=Un
 ******************************************************************************/
void ADC_Init(void)
{
    // ADC1 ����ת��ģʽ ͨ��2 ��Ƶϵ��2 �����Ҷ��� �ر�ʩ���ش�����
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_2, ADC1_PRESSEL_FCPU_D2, \
                  ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL2, DISABLE);
    
    // ADC1 ����ת��ģʽ ͨ��3 ��Ƶϵ��2 �����Ҷ��� �ر�ʩ���ش�����
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_3, ADC1_PRESSEL_FCPU_D2, \
                  ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL3, DISABLE);
    ADC1_Cmd(ENABLE);
}


/*******************************************************************************
 * ����: Start_Ad_Task()
 * ����: ����һ��adת��
 * �β�: ��
 * ����: ��
 * ˵��: 
        1 ÿs�ɼ�һ��
 ******************************************************************************/
void Start_Ad_Task(void)
{
    ADC_Init();
    CollEnd = FALSE;
    k = 1;    
}



/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/


