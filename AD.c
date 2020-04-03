/******************** (C) COPYRIGHT  杭州浙宝微电脑技术有限公司 **************
 * 文件名  ：AD.c
 * 描述    ：8209C 的数据读取,校准
 * 实验平台：X963MV1
 * 库版本  ：V1.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 淘宝    ：
 * 修改时间 ：2015-10-20
 * 注意    ：RN8209C 本身是采用串口驱动的，
                        但是因为cpu只有一组串口所以本驱动是采用io模拟的方式驱动
  X963MV1 硬件连接
    |--------------------|
    |  TXD0-PB0          |
    |  RXD0-PB1          |
    |--------------------|

*******************************************************************************/



/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "AD.h"

/* 自定义新类型 */

/* 自定义宏 */

#define     _10_bit       0x400
#define     _13_bit       0x2000
#define     _23_bit       0x800000
#define     _24_bit       0x1000000
#define     _27_bit       0x8000000
#define     _28_bit       0x10000000
#define     _31_bit       0x80000000
#define     _32_bit       0xFFFFFFFF


/* 全局变量定义 */

/* 15 度 */
const float Vsin15[25]={0,0.0295,0.2872,0.5254,0.7277,0.8804,0.9731,0.9996,0.9579,0.8509,
                0.6859,0.4742,0.2302,-0.0295,-0.2872,-0.5254,-0.7277,-0.8804,-0.9731,
			   -0.9996,-0.9579,-0.8509,-0.6859,-0.4742,-0.2302};
const float Vcos15[25]={0,0.9996,0.9579,0.8509,0.6859,0.4742,0.2302,-0.0295,-0.2872,
                  -0.5254,-0.7277,-0.8804,-0.9731,-0.9996,-0.9579,-0.8509,
		   -0.6859,-0.4742,-0.2302,0.0295,0.2872,0.5254,0.7277,0.8804,0.9731};	


/* 0 度 */
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


//读入电压和电流的相位补偿系数
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
 * 名称: Compute_Task()
 * 功能: ad采样后，启动一次计算
 * 形参: 无
 * 返回: 无
 * 说明: 1 算出 电压 电流 大小
         2 算出 功率因素
 ******************************************************************************/
void Compute_Task(void)
{
    unsigned char i;
	float ampleV,ampleI;
	//pflable=0x00;//功率因数超前标志
	float cosV,sinV,cosI,sinI,sinVI,cosVI,tempCos,ampleCos;
	float VAn=0,VBn=0,IAn=0,IBn=0;

    if(FALSE == CollEnd)        // 采样未完成，直接退出
        return;

    CollEnd = FALSE;            // 采样已计算

    ReadVcosVsin(1);            // 读取相位补偿系数 15度

	for(i=1;i<25;i++)
	{
		VAn=VAn+(Vresult[i]*Vcos[i]);//电压函数傅立叶变换后得到的基波的cos相的幅值（带系数）
	    VBn=VBn+(Vresult[i]*Vsin[i]);//电压函数傅立叶变换后得到的基波的sin相的幅值（带系数）
	    IAn=IAn+(Iresult[i]*Icos[i]);//电流函数傅立叶变换后得到的基波的cos相的幅值（带系数）
	    IBn=IBn+(Iresult[i]*Isin[i]);//电流函数傅立叶变换后得到的基波的sin相的幅值（带系数）
	}

	ampleV=sqrt(VAn*VAn+VBn*VBn);
	ampleI=sqrt(IAn*IAn+IBn*IBn);
		 
	cosV=VBn/ampleV;//电压相角的cos值乘上系数100
	sinV=VAn/ampleV;//电压相角的sin值
	cosI=IBn/ampleI;//电流相角的cos值
	sinI=IAn/ampleI;//电流相角的sin值
	sinVI=(sinV*cosI-cosV*sinI);
	cosVI=(cosV*cosI+sinV*sinI);
	if(sinVI >= 0)
	{
	    tempCos = sinVI;
	 	if(cosVI > 0)
	 		tempCos = 2 - tempCos;		//滞后	
//	 		DM.sElecPara.Cos = sinVI;
	 	else
           tempCos = tempCos;		//超前
//            DM.sElecPara.Cos = -sinVI;
	}
	else 
	{
	    tempCos = 0 - sinVI;
	    if(cosVI > 0)
//		    DM.sElecPara.Cos = 0-sinVI;
	 		tempCos = tempCos;		//超前
        else
//            DM.sElecPara.Cos = sinVI;
			tempCos = 2 - tempCos;		//滞后
	 } 
	DM.sElecTemp.TCos[9] = tempCos*1000;

	DM.sElecTemp.TUU[9] = (ampleV);			// 电压有效值(0000-2200)	单位0.1V
	DM.sElecTemp.TII[9] = (ampleI);			// 电流有效值 (0000-5000)	单位0.001As   未计算ct 

// 平均值计算	
	ampleI = 0;
	ampleV = 0;
	ampleCos = 0;
	for(i=0;i<10;i++)						// 算个平均值
	{
		ampleI = ampleI + DM.sElecTemp.TII[i];
		ampleV = ampleV + DM.sElecTemp.TUU[i];
		ampleCos = ampleCos + DM.sElecTemp.TCos[i];
	}
    

    DM.sElecPara.UU = (ampleV + 5)/10;  // 3位数 4舍5入
    DM.sElecPara.II = (ampleI + 5)/10;  
	DM.sElecPara.Cos = (ampleCos + 5)/10;

    CollEnd = FALSE;            // 清除采样完成标志位，开始采样
}

/*******************************************************************************
 * 名称: ADC_Config()
 * 功能: 内部 adc 模块 初始化
 * 形参: 无
 * 返回: 无
 * 说明: 
        1 单次触发模式
        2 分频系数2
        3 数据右对齐
        4 AIN2=In AIN3=Un
 ******************************************************************************/
void ADC_Init(void)
{
    // ADC1 单次转换模式 通道2 分频系数2 数据右对齐 关闭施密特触发器
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_2, ADC1_PRESSEL_FCPU_D2, \
                  ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL2, DISABLE);
    
    // ADC1 单次转换模式 通道3 分频系数2 数据右对齐 关闭施密特触发器
    ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_3, ADC1_PRESSEL_FCPU_D2, \
                  ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL3, DISABLE);
    ADC1_Cmd(ENABLE);
}


/*******************************************************************************
 * 名称: Start_Ad_Task()
 * 功能: 启动一次ad转换
 * 形参: 无
 * 返回: 无
 * 说明: 
        1 每s采集一次
 ******************************************************************************/
void Start_Ad_Task(void)
{
    ADC_Init();
    CollEnd = FALSE;
    k = 1;    
}



/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/


