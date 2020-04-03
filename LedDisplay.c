/******************** (C) COPYRIGHT  杭州浙宝微电脑技术有限公司 **************
 * 文件名  ：TM1629B.c
 * 描述    ：TM1629 B的驱动函数
 * 实验平台：X963MV1
 * 库版本  ：V1.1.0
 * 作者    ：莫易  QQ：29577332
 * 博客    ：
 * 淘宝    ：
 * 修改时间 ：2012-10-20
 * 注意    ：TM1629B 不是C 不是D
  X963MV1 硬件连接
    |--------------------|
    |  DIO-PC1          |
    |  CLK-PC2          |
    |  STB-PC3          |
    |--------------------|

*******************************************************************************/

/* 包含系统头文件 */

/* 包含自定义头文件 */
#include "LedDisplay.h"

/* 自定义新类型 */

/* 自定义宏 */



//指示灯



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
//查询符号
//================================================================
// 设置显示的符号

const uint8_t Fuction = 0x40;                      // 软件功能编码
const uint8_t Version = 0x60;                      // 软件版本号
const uint8_t CHR_Ver[][3] =                       //开机的时候，显示公司信息等
{
    DS_Chr_u,      DS_Chr_6,       DS_Chr_0,       // v0.60
};


//--------------------------写入一个字节(8bit) 到led_ic 程序结束--------------------------

/*******************************************************************************
 * 名称: ReFlash_LED
 * 功能: 根据DM.sDisMem.cDispData 中的数据转换并输出到1629上显示
 * 形参: 无
 * 返回: 无
 * 说明: 1 显示led
         2 显示数码管
         3 本处转换需要仔细核对原理图和1629说明书
 ******************************************************************************/
void ReFlash_LED(void)                // led 闪烁程序
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


//--------------------------转换显示数据 程序结束--------------------------


void     DispVer(void)     //显示 公司  程序的版本等信息
{

}


/*************** (C) COPYRIGHT 杭州中深电力技术有限公司 *****END OF FILE****/



