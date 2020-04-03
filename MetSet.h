/******************** (C) COPYRIGHT  �����㱦΢���Լ������޹�˾ **************
 * �ļ���  ��TM1629B.c
 * ����    ��TM1629 B����������
 * ʵ��ƽ̨��X963MV1
 * ��汾  ��V1.1.0
 * ����    ��Ī��  QQ��29577332
 * ����    ��
 * �Ա�    ��
 * �޸�ʱ�� ��2012-10-20

  X963MV1 Ӳ������
    |--------------------|
    |  DIO-PC1          |
    |  CLK-PC2          |
    |  STB-PC3          |
    |--------------------|

*******************************************************************************/

#ifndef __METSET_H
#define __METSET_H

/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "stm8s.h"
#include "main.h"

/* �Զ����������� */

/* �Զ��峣����ͱ��ʽ�� */


#define	NULLTIMENUM		100             // �ް������� 100*keyscan()����

//metstatus register flags define
#define  F_Ger   0x01    //�Ǳ��������Ĳ�����ʾ״̬
#define  F_Set   0x02    //�Ǳ��ڲ˵�����״̬
//#define  F_Adj   0x04    //��ʾ�Ǳ���У׼״̬
//#define  F_Fls       0x08    //��ʾ�Ǳ�����˸�ı����ݵ�״̬
//#define  F_Quk       0x10    //��ʾ�Ǳ�����ʾ�汾��Ƶ�ʵ�״̬

// DM.ReChc7302 ��7302��У׼
#define  F_ReChk         0x80    // ��ʾ�Ǳ�����λ������У׼ �� ���ù�7302���� ��Ҫ�������� 7302

//KeyFlg  register flags define
#define         F_KeySet        BIT0
#define         F_KeyAdd        BIT1
#define         F_KeySub        BIT2
#define         F_KeyNull       BIT3

// Ĭ��ҳ��
#define AUTO_MENU		0x1001				//�Զ��˵�


//FlashFlg  register flags define
#define         F_FlashNew      0x01    //����flash���ݵı�־

//ĳЩ�����ҳ���ַ
#define   VolPage       0           // ������ѹ��ʾ
#define   DIOPage   63
#define   VERPage   74          // �汾��

#define   LEDType       1
#if       LEDType == 0
#define   sega          0x01
#define   segb          0x04
#define   segc          0x10
#define   segd          0x40
#define   sege          0x80
#define   segf          0x02
#define   segg          0x08
#define   segh          0x20
#elif     LEDType  == 1
#define   sega          0x01
#define   segb          0x02
#define   segc          0x04
#define   segd          0x08
#define   sege          0x10
#define   segf          0x20
#define   segg          0x40
#define   segh          0x80
#endif

#define DS_Chr_0     sega|segb|segc|segd|sege|segf
#define DS_Chr_1     segb|segc
#define DS_Chr_2     sega|segb|segd|sege|segg
#define DS_Chr_3     sega|segb|segc|segd|segg
#define DS_Chr_4     segb|segc|segf|segg
#define DS_Chr_5     sega|segc|segd|segf|segg
#define DS_Chr_6     sega|segc|segd|sege|segf|segg
#define DS_Chr_7     sega|segb|segc
#define DS_Chr_8     sega|segb|segc|segd|sege|segf|segg
#define DS_Chr_9     sega|segb|segc|segd|segf|segg
#define DS_Chr_A     sega|segb|segc|sege|segf|segg
#define DS_Chr_b     segc|segd|sege|segf|segg
#define DS_Chr_C     sega|segd|sege|segf
#define DS_Chr_d     segb|segc|segd|sege|segg
#define DS_Chr_E     sega|segd|sege|segf|segg
#define DS_Chr_F     sega|sege|segf|segg

#define DS_Chr_Neg   segg
#define DS_Chr__     segg
#define DS_Chr_c     segd|sege|segg
#define DS_Chr_h     segc|sege|segf|segg
#define DS_Chr_H     segc|sege|segf|segg|segb
#define DS_Chr_J     segb|segc|segd
#define DS_Chr_K     segd|sege|segf|segg
#define DS_Chr_L     segd|sege|segf
#define DS_Chr_N     sega|segb|segc|sege|segf
#define DS_Chr_n     segc|sege|segg
#define DS_Chr_o     segc|segd|sege|segg
#define DS_Chr_P     sega|segb|sege|segf|segg
#define DS_Chr_q     sega|segb|segc|segf|segg
#define DS_Chr_r     sege|segg
#define DS_Chr_S     sega|segc|segd|segf|segg
#define DS_Chr_t     segd|sege|segf|segg
#define DS_Chr_I     segb|segc
#define DS_Chr_i     sege
#define DS_Chr_U     segb|segc|segd|sege|segf
#define DS_Chr_y     segb|segc|segd|segf|segg
#define DS_Chr_Z     sega|segb|segd|sege|segg
#define DS_Chr_u     segc|segd|sege
#define DS_Chr_0_    sega|segb|segc|segd|sege|segf|segh
#define DS_Chr_X1   sega|segd|sege|segf         // ���⹫˾��־
#define DS_Chr_X2   sega|segd|segg
#define DS_Chr_X3   sega|segd|segg
#define DS_Chr_X4   sega|segb|segc|segd
#define DS_Chr_dp	((segh))



//menu
#define	MAXSETMENU	6		// ���ò˵� ���5��
#define	MAXSYSMENU	3		//  ϵͳ�˵����3��


/* �������ⲿʹ�õı��� */

/* �������ⲿʹ�õĺ��� */
/*******************************************************************************
 * ����: Key_Task
 * ����: ���ݰ�����������ʾ��ͬ�Ĳ˵�
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void Key_Task(void);

/*******************************************************************************
 * ����: Selfdetect
 * ����: ���ݵ�ǰ������ʾ
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void Selfdetect(void);

/*******************************************************************************
 * ����: delayX10ms
 * ����: ���ձ�׼10msΪ��㣬��ʱ�涨��ʱ��
 * �β�: ��
 * ����: ��
 * ˵��: 1 DM.sRelayTime.wDelayTime ��������ж���ִ��--
         2 ʱ���жϱ����
         3 ��ʱ���ܳ������Ź��Ķ���ʱ��
 ******************************************************************************/
void delayX10ms(unsigned int time);


/*******************************************************************************
 * ����: AutoAdjust
 * ����: �Զ�У׼ U I PF
 * �β�: ��
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void AutoAdjust(void);

#endif


/*************** (C) COPYRIGHT ������������������޹�˾ *****END OF FILE****/

