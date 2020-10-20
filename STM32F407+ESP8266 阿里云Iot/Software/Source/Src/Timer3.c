/*
********************************************************************************************
 版权所有 (C)，2011－2015，泉州禾逸电子有限公司
----------------------------------------------------------------------------------------
源程序文件名：　　　Timer3.c
源程序名称：　　　　定时器3处理源程序
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
#include "Timer3.h"                        // Timer3处理的头文件


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


/*==========================================================================================
                             本源程序文件内部使用的局部变量定义
==========================================================================================*/

/*
********************************************************************************************
                             　       程序指令代码清单
********************************************************************************************
*/




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




/*-------------------------------------------------*/
/*函数名：定时器3使能30s定时                       */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM3_ENABLE_30S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;      
	NVIC_InitTypeDef NVIC_InitStructure;                     
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    
	TIM_DeInit(TIM3);                                           
	TIM_TimeBaseInitStructure.TIM_Period = 60000-1; 	      
	TIM_TimeBaseInitStructure.TIM_Prescaler=42000-1;            
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;   
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);        
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                 
	TIM_Cmd(TIM3,ENABLE);                                        
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;               
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;           
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;              
	NVIC_Init(&NVIC_InitStructure);                               
}


/*-------------------------------------------------*/
/*函数名：定时器3使能2s定时                        */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM3_ENABLE_2S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;      
	NVIC_InitTypeDef NVIC_InitStructure;                         
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);          
	TIM_DeInit(TIM3);                                            
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1; 	      
	TIM_TimeBaseInitStructure.TIM_Prescaler=8400-1;               
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;    
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);         
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                  
	TIM_Cmd(TIM3,ENABLE);                                          
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;       
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;            
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                             
}




