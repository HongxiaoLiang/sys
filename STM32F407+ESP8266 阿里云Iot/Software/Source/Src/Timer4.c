/*
********************************************************************************************
 版权所有 (C)，2011－2015，泉州禾逸电子有限公司
----------------------------------------------------------------------------------------
源程序文件名：　　　Timer4.c
源程序名称：　　　　定时器4处理源程序
程序版本：　　      1.0
程序功能：
　　　　
程序说明：
　　　　
主要函数列表：　　　
　　　　

链接子程序文件：　　
　　　　

编译工具软件：      

编作者：            
编制日期：          
----------------------------------------------------------------------------------------
适用器件芯片类型：  
器件芯片时钟频率：  任意
存储器模式：        大存储器模式
外部扩展存储器大小：0【字节】
调用堆栈大小：      0 【字节】
数据堆栈大小：      0 【字节】
----------------------------------------------------------------------------------------
源程序版本历史：
年月日  〖〗 -------- 版本 1.0 ：原始版本
********************************************************************************************
*/

/*==========================================================================================
                                        调试开关声明
==========================================================================================*/
//#define DEBUG


/*==========================================================================================
　　　　　　　　　　　　　　        本源程序包括的头文件
建议：包含本项目的文件使用 #include "文件名.扩展名" ，
　　　包含系统库的文件使用 #include <文件名.扩展名> 。
==========================================================================================*/
#include "Timer4.h"                        // Timer4处理的头文件


/*==========================================================================================
下面这三条指令是用于区分编译系统为 C++ 或 C 的预处理指令。
"__cplusplus" 为 C++ 预处理器名字，这三条指令表明接在其下面的那些指令为 C 程序特征。
==========================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================================
                            本源程序文件内部使用的字符化常数定义
==========================================================================================*/

/*--------------------------------------------------------------------------------------
的字符化常数定义：
--------------------------------------------------------------------------------------*/
//#define		Debug				// 调试开关

/*==========================================================================================
                             本源程序文件内部使用的函数原型声明
==========================================================================================*/


/*==========================================================================================
                       本源程序文件内部使用的局部常量、字符化常数定义
==========================================================================================*/

/*--------------------------------------------------------------------------------------
的局部常量、字符化常数定义：
--------------------------------------------------------------------------------------*/




/*==========================================================================================
                                        全局常量定义
==========================================================================================*/


/*==========================================================================================
                                        全局变量定义
==========================================================================================*/
/*--------------------------------------------------------------------------------------
定时器4标志的全局常量声明：
--------------------------------------------------------------------------------------*/
Timer4Bits gbitTimer4;


/*==========================================================================================
                             本源程序文件内部使用的局部变量定义
==========================================================================================*/

/*
********************************************************************************************
                             　       程序指令代码清单
********************************************************************************************
*/
/*--------------------------------------------------------------------------------------
函数名称：    初始化定时器4
函数功能：    本函数用于初始化定时器4
函数入口参数：没有
函数返回值：  没有
调用函数：　　１．
　　　　　　　　　
备注：        本函数仅在主函数中调用一次即可。
--------------------------------------------------------------------------------------*/
void Timer4_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;            //定义一个设置定时器的变量
	NVIC_InitTypeDef         NVIC_InitStructure;                          //定义一个设置中断的变量
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);           //使能TIM4时钟	

  TIM_TimeBaseInitStructure.TIM_Period        = arr; 	              //设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler     = psc;                  //设置定时器预分频数
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //1分频
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);            //设置TIM4
	
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);                    //清除溢出中断标志位
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);                      //使能TIM4溢出中断    
	TIM_Cmd(TIM4, DISABLE);                                        //先关闭TIM4                          
	
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM4_IRQn;                 //设置TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;              //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;                 //中断通道使能
	NVIC_Init(&NVIC_InitStructure);                               //设置中断
}







/*==========================================================================================
下面这三条指令是用于与上面三条区分编译系统为 C++ 或 C 的预处理指令相对应。用于指定
 extern "C" 链接指示符作用域，此处的"}"与上面的"{"相对应，为链接指示符作用结束符。
==========================================================================================*/
#ifdef __cplusplus
}
#endif


/*
********************************************************************************************
                                 本Ｃ语言源程序文件到此结束
********************************************************************************************
*/









