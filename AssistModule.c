/******************** (C) COPYRIGHT  杭州浙宝微电脑技术有限公司 **************
 * 文件名  ：AssistModule.c
 * 描述    ：辅助模块的功能 1开入2开出3变送
 * 实验平台：X963MV1
 * 库版本  ：V1.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 淘宝    ：
 * 修改时间 ：2015-08-13
 * 注意    ：1 

  X963MV1 硬件连接
*******************************************************************************/
/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "AssistModule.h"

/* 自定义新类型 */

/* 自定义宏 */


/* 全局变量定义 */




/*******************************************************************************
 * 名称: RunTestLed
 * 功能: 根据设定值驱动测试用led
 * 形参:
 * 返回: 1 true led已经正常驱动
         2 false 设定值已经到底 
 * 说明: 1
  ******************************************************************************/
void RunTestLed_Task(void)
{
}



/*******************************************************************************
 * 名称: Get_VerAndFunction
 * 功能: 获取当前软件的功能号和版本号
 * 形参: 无
 * 返回: 无
 * 说明: 无
         1 功能号4 表示 数显多功能表 有可能是96 也可能是72 也可能是42
         2 软件版本号 为系统生成
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
 * 名称: AssistMod_Init
 * 功能: 辅助模块初始化 1继电器 2测试灯
 * 形参:
 * 返回: 无
 * 说明: 1
  ******************************************************************************/
void AssistMod_Init(void)
{
//        unsigned char temp = 0;
        //gpio 初始化
        // 继电器输出
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

        // 测试点输入

        
        GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);

        // 测试点输出
//        #ifdef debugAD
//        GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_SLOW);
//        #else
//        GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
//        #endif


        // 方波输入 PB0<=I, PB1<=U
        GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_PU_NO_IT);
        GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);
        
}


// PA3 PB0 PB1 PB6 PB7 PC6 PC7 PD0 PD7 PE3 PG0 PG1
// 空闲gpio初始化
// emc 要求空余管脚 设置为输出低电平

/*******************************************************************************
 * 名称: NullIO_Init
 * 功能: 空闲gpio初始化
 * 形参: 
 * 返回: 无
 * 说明: 1 PA1-3 PB4-7 PC1-6 PD0 
 *       2 PE3 5 6 7
  ******************************************************************************/
void NullIO_Init(void)
{
    //GpioA 初始化
    GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOA,GPIO_PIN_1);
    GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOA,GPIO_PIN_2);
    GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOA,GPIO_PIN_3);

    //GpioB 初始化
    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_4);
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_5);
    GPIO_Init(GPIOB, GPIO_PIN_6, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_6);
    GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOB,GPIO_PIN_7);

    //GpioC 初始化
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

    //GpioD 初始化
    GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOD,GPIO_PIN_0);

    //GpioE 初始化
    GPIO_Init(GPIOE, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOE,GPIO_PIN_5);
    GPIO_Init(GPIOE, GPIO_PIN_6, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOE,GPIO_PIN_6);
    GPIO_Init(GPIOE, GPIO_PIN_7, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_WriteLow(GPIOE,GPIO_PIN_7);
}


/*******************************************************************************
 * 名称: SaveFlash
 * 功能: 保存仪表的相关数据到ee中
 * 形参: 无
 * 返回: 无
 * 说明: 1
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
 * 名称: 检验系统 的参数存储区是否有误
 * 功能: 检验系统 的1个参数存储区是否有误并返回正确的参数区
 * 形参: 无
 * 返回: True(eeprom1区),False(常数区)
 * 说明: true 表示 1区正常
         false 表示 需要使用常数区
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
    return TRUE;       // 要求读取eeprom 区参数

}



/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/

