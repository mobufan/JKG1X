/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� **************
 * �ļ���  ��led.h
 * ����    ��LED����⺯��
 * ʵ��ƽ̨�����STM8������
 * ��汾  ��V2.1.0
 * ����    �����  QQ��779814207
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 * �޸�ʱ�� ��2012-10-20

  ���STM8������Ӳ������
    |--------------------|
    |  LED1-PD0          |
    |  LED2-PD1          |
    |  LED3-PD2          |
    |  LED4-PD3          |
    |--------------------|
* ע��:
* 1

*******************************************************************************/
#ifndef __MAIN_H
#define __MAIN_H

/* �Զ����������� */
typedef unsigned char     BOOLEAN;
typedef unsigned char     INT8U;                    /* Unsigned  8 bit quantity                            */
typedef signed   char      INT8S;                    /* Signed    8 bit quantity                            */
typedef unsigned int       INT16U;                   /* Unsigned 16 bit quantity                            */
typedef signed   int        INT16S;                   /* Signed   16 bit quantity                            */
typedef unsigned long    INT32U;                   /* Unsigned 32 bit quantity                            */
typedef signed   long     INT32S;                   /* Signed   32 bit quantity                            */
typedef float                 FP32;                     /* Single precision floating point                     */


/* �Զ��峣����ͱ��ʽ�� */

#define BIT0    0x01          /* BIT0  = (1<<1)  = 0b00000001 */
#define BIT1    0x02          /* BIT1  = (1<<2)  = 0b00000010 */
#define BIT2    0x04          /* BIT2  = (1<<3)  = 0b00000100 */
#define BIT3    0x08          /* BIT3  = (1<<4)  = 0b00001000 */
#define BIT4    0x10          /* BIT4  = (1<<5)  = 0b00010000 */
#define BIT5    0x20          /* BIT5  = (1<<6)  = 0b00100000 */
#define BIT6    0x40          /* BIT6  = (1<<7)  = 0b01000000 */
#define BIT7    0x80          /* BIT7  = (1<<8)  = 0b10000000 */


#define   checkbit(var,bit)  (var & (0x01 << (bit)))
#define   setbit(var,bit)    (var |= (0x01 << (bit)))
#define   clrbit(var,bit)    (var &= (~(0x01 << (bit))))


#define debugled   // ����ʹ��
#define debugAD     // ����ʹ��

#define	AUTOSTATE	0x01				// �Զ�״̬
#define	HANDSTATE	0x02				// �ֶ�״̬
//#define	SETSTATE	0x03				// �趨״̬
//#define	ADJSTATE	0x04				// У׼״̬
#define	OTHERSTATE	0x05			    //  ������ʾ״̬


/* ����ϵͳͷ�ļ� */
#include <math.h>

/* �����Զ���ͷ�ļ� */
#include "sysclock.h"
#include "tim1.h"
#include "stm8s_it.h"
#include "tm1629b.h"
#include "Iwdg.h"
#include "LedDisplay.h"
#include "metset.h"
#include "AD.h"
#include "AssistModule.h"
#include "CapTask.h"
#include "Config.h"

/* �Զ����������� */


#define CAPNUMBER_MAX   12
#define CAPNUMBER_MIN   1
#define ACTDELAY_MAX    120
#define ACTDELAY_MIN    10
#define PFTH_MAX        99
#define PFTH_MIN        90
#define OVERV_MAX       20
#define OVERV_MIN       5
#define LIMITI_MAX      10
#define LIMITI_MIN      0
#define PFREPAIR_MAX    10
#define PFREPAIR_MIN    0

struct CAP
{
	INT8U	cCapSize;					// �������� 1 - 200	 Kvar
	INT8U	cCapKind;					// �������� 0 ��ʾû��,1 - �ֲ�3-����;0x11 ��ʾA ��ֲ� ;0x21��ʾB ��ֲ�
	INT8U	cCapCool;					// ���ݵ���ȴʱ�� ;0 ��ʾ�Ѿ���ȴ ��ʱ����Ͷ��
	INT8U	cCapSatae;					// ��������״̬ 1 ��ʾ��Ͷ�� 0 ��ʾ���г�
	INT16U	wCapUseNum;				// �õ�������ʹ�ô���
};

#define	CapOn		0x01
#define	CapOff		0x00

#define	SETMENU	    0x01				// ���ò˵�
#define	DISPMENU	0x00				// ��ʾ�˵�

struct STATE
{
	INT8U	cAutoState;					// �ֶ��Զ�״̬   TRUE = Auto   FALSE = Hand
	INT8U	cOverVAlarm;				// ��ѹ����
	INT8U	cLossCupAlarm;				// Ƿ������  ȫ�������Ѿ�Ͷ�뵫�ǹ���������Ȼ����
	INT8U	cOverCupAlarm;				// ��������  ȫ�������Ѿ��г����ǹ���������Ȼ��ǰ
	INT8U   cNoIAlarm;                  // �޵�������
	INT8U   cLowIAlarm;                 // С��������
	INT8U   cLowUAlarm;                 // Ƿѹ����
	
};

struct ELEC_PARA					//���������Ǽ����ĵ���� 
{                          
	INT16S	UU;					    // ��ѹ��Чֵ(000-220)		û��С��λ // 380V ʱԼΪ630
	INT16S	II;					    // ������Чֵ 5A  δ��ct(0000-5000) // 5AʱԼΪ400
	INT16S  Cos;				    // ��������  (0000-99-1000-101-200)
	                                //           (0-0.99-1.00-0.99-200)
	                                //           (�ͺ� �� ��ǰ)
//	INT16S	Fraq;					// Ƶ��(000-500)
//	INT32S	ActP[4];				// �й�����(0000-9999)
//	INT32S 	ActS[4];				// �޹�����(0000-9999)
//	INT32S	ActQ;				// ���ڹ���(0000-9999)

//	INT32S   THDv[3];				// ������(000-999)
//	INT32S	IICT[3];				// ct��Ⱥ������
};

struct ELEC_TEMP						// �������ܵ��м����� ������Щ���ݵ�ƽ��ֵ���������Ҫ�Ľ��
{
	INT16S	TUU[10];					
	INT16S	TII[10];
	INT16S	TCos[10];
};

struct DISPDATE						// ����ʹ����ˢ�µ����� ע��������1��ʾ�� ��ʵ�ʵ�Ӳ���պ��෴
{
	INT8U	cDispData[3];				//��ǰ�������ʾ����  �������� [0]=�� [1]=�� [2]=��
};

struct	REAL	// ��������ʾ����;ֱ�ӱ��͵���ʾ����
{
    INT8U 	Factor[3];		    // �������� �� noI
    INT8U   A1_Number[3];       // ��������
    INT8U   A2_OnOffTime[3];    // Ͷ�м��
    INT8U   A3_PfLimit[3];      // ������������
    INT8U   A4_OverVLimit[3];   // ��ѹ����
    INT8U   A5_LowILimit[3];    // Ƿ������
    INT8U   A6_AutoOrHand[3];   // �ֶ��Զ�
    INT8U   B1[3];              // ��ѹ У׼ֵ
    INT8U   B2[3];              // ���� У׼ֵ
    INT8U   B3[3];              //  pf У׼ֵ
};
struct	RELAYTIME		// ������������Ҫ��ʱ�Ķ�ʱ����������
{
	INT16U	c10msTime;			// 10ms ����ʱ��
	INT8U	c10msChange;		// 10ms��־
	INT8U	cSecChange;			// ���־
	INT8U   c833usTime;       // 833us��־ ��Сʱ�����

	INT8U	cNullTime;			// �ް�������ʱ��

    INT16U   wDelayTime;         // ��ʱ�����ļ�����
};
struct	DspControl
{
      INT16U		PagePtr;		// ��ʾҳ���ָ�� �ǳ���Ҫ
};


/*
struct	KEY
{
	INT8U cLastReadKey;				//����Ƕ�������ֵ
	INT8U cRealKey;					// ����Ǵ���õ���Чֵ
};
*/

// ����������wConCap
// 
#define	F_SELC3		0x0010		// ��Ͷ�빲��
// #define	F_SELCA	    0x0020		// ��Ͷ��ֲ�a
//#define	F_SELCB		0x0040		// ��Ͷ��ֲ�b
//#define	F_SELCC		0x0080		// ��Ͷ��ֲ�c
#define	F_DELC3	    0x0001		// ���г�����
//#define	F_DELCA	    0x0002		// ���г��ֲ�a
//#define	F_DELCB	    0x0004		// ���г��ֲ�b
//#define	F_DELCC	    0x0008		// ���г��ֲ�c
#define	F_OVERV	    0x0100		// ��Ϊ��ѹ״̬������
#define	F_NOV		0x0200		// ��Ϊȱ��״̬������
#define	F_LOWI		0x0400		// ��ΪǷ��
#define	F_NOI		0x0800		// ��Ϊ�޵���

// ���ݵ�Ͷ�м���ֵ
struct	COMCAP				
{
	INT16U	wConCap[120];			// �����120s �ڵ��ݵ�Ͷ���߼� ÿ��һ��
};

typedef struct
{
	struct ELEC_PARA	sElecPara;
	struct ELEC_TEMP sElecTemp;
	struct DISPDATE	sDisMem;
	struct STATE		sStateSet;
	struct REAL		sReal;
	struct RELAYTIME	sRelayTime;
	struct DspControl	sDspCtr;
	struct CAP		sCapPara[12];		// ��������״̬
	struct COMCAP 	sConCap;			// ���ݵ�Ͷ�м�����	
	unsigned char cSysFlg;              // ϵͳ״̬
} DRAM;

struct CONFIG
{
	INT16U	c3CupNumber;				//  ����������·��(1-12)
	INT16U	cCupDelayTime;			    //  ������Ͷ����ʱ (��) 10-120 ����10
	INT16U	cPfLimit;					//  �޹����� 80-99 ����1
	INT16U	wOverVoltage;				//  ��ѹ����  (5-25) ����5
	INT16U   cLowILimit;                 //  С�������� 0-10 ����2
	INT16U   XiaoZun1;                   //  У׼ֵ1 II ȡ5A ʱ�ĵ���ֵ����Լ400
	INT16U   XiaoZun2;                   //  У׼ֵ2 UU ȡ380/220 ʱ�ĵ���ֵ, ��Լ630
	INT16U   XiaoZun3;                   //  У׼ֵ3 pf ȡ
};
typedef struct
{
	struct	CONFIG	sConfig;				// ��Щ������Ҫ���浽eeprom
}SRAM;


// ��ö�ٽ����Ƕ���һ��0-max�ı���
// ����˵��ƽʱ���еĺ����ֱ���ʲô����û��ʲô����
typedef enum _TASK_LIST
{
    TASK_ADC,
    TASK_RELAY_ACT,
    TASK_RELAYOUT,
    TASK_KEY,
    TASK_FLASHLED,
    TASK_IWDG,
    TASK_TESTLED,
    TASK_MAX
} TASK_LIST;

typedef struct _TASK_COMPONENTS
{
    uint8_t Run;                  // �������б�־: 0 ������ 1����
    uint8_t Stop;                 // ����رձ�־: 0 ���� 1 �ر�
    uint16_t Timer;                // ��ʱ�� ֻ�Ǽ�ʱ�������Ը�һ����ֵ����ֵ��������������ʱ��
    uint16_t ItvTime;              // ������ʱ��
    void (*TaskHook)(void);     // ��Ҫ���е�������
} TASK_COMPONENTS;

/* �������ⲿʹ�õı��� */
extern SRAM SM;     // �����ļ�
extern DRAM DM;     //����Ҫ��ʼ���ģ����ʼ��Ϊ0�ı���
extern unsigned char ReloadIWdog;       // ι���Ĵ���
extern TASK_COMPONENTS TaskComps[];

/* �������ⲿʹ�õĺ��� */

/*******************************************************************************
 * ����: TaskRemarks
 * ����: �����־����
 * �β�: ��
 * ����: ��
 * ˵��: 1 ר�Ŵ�������ı�־λ
         2 ������ ÿ��ʱ�����ִ��1��
 ******************************************************************************/
void TaskRemarks(void);

#endif

/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/

