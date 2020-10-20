/*
********************************************************************************************
 版权所有 (C)，2011－2015，泉州禾逸电子有限公司
----------------------------------------------------------------------------------------
头文件名：        　Keydeal.h
头文件名称：      　按键处理的头文件
文件版本：　　      1.0
文件功能：
　　　　本文件是对   的各硬件技术标准、电路设计结构和软件运行参数，进行定义配置的
　　头文件。
文件说明：
　　　　１．本文件中的所有标识符定义前缀字母表示意义如下：
	 	        c  ---------- 常量
　　　　　　v  ---------- 变量
			      en ---------- 枚举
　　　　　　g  ---------- 全局变量（Global）
            s  ---------- 静态变量（Static）
　　　　　　l  ---------- 局部变量（Local）
　　　　　　uc ---------- 数据类型（Unsigned Char）
　　　　　　ui ---------- 数据类型（Unsigned Word）
　　　　　　p  ---------- 指针
　　　　　　st ---------- 数据体
　　　　　　pt ---------- 指向数据体的指针
            Pre --------- 条件编译预定义
            
            stru -------- 定义数据体
            enum -------- 定义枚举
　　　　２．

主要函数列表：


编译工具软件：      ［］
链接文件：          ▲．目标器件芯片的头文件

编作者：            
编作者 E-Mail：     
编制日期：          
----------------------------------------------------------------------------------------
头文件版本历史：

********************************************************************************************
*/



/*==========================================================================================
下面两条指令是本头文件条件编译的预处理指令，用于防止本头文件被其他文件重复引用。
==========================================================================================*/
#ifndef _Key_Deal_H_                        // “_Key_Deal_H_”条件编译开始
#define _Key_Deal_H_


/*==========================================================================================
　　　　　　　　　　　　　　        本源程序包括的头文件
建议：包含本项目的文件使用 #include "文件名.扩展名" ，
　　　包含系统库的文件使用 #include <文件名.扩展名> 。
==========================================================================================*/

#include "stm32f4xx.h"                         		// 目标器件芯片的头文件
#include "sysconfig.h"                     		// 系统配置的头文件
#include "Main.h"                         		// 主程序的头文件



/*==========================================================================================
下面这三条指令是用于区分编译系统为 C++ 或 C 的预处理指令。
"__cplusplus" 为 C++ 预处理器名字，这三条指令表明接在其下面的那些指令为 C 程序特征。
==========================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif



/*==========================================================================================
                                系统运行的各类字符化常数定义
==========================================================================================*/

/*--------------------------------------------------------------------------------------
为了做到较好的软件可移植性，推荐用户在编程时使用下面定义的数据类型大小
--------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------
的字符化常数定义
--------------------------------------------------------------------------------------*/


/*==========================================================================================
                                      条件编译控制声明
==========================================================================================*/



/*--------------------------------------------------------------------------------------
声明 的条件定义：
--------------------------------------------------------------------------------------*/







/*==========================================================================================
                      各类字符化常数和硬件设计相关的输入／输出引脚定义
==========================================================================================*/

/*--------------------------------------------------------------------------------------
的输入／输出引脚定义：
--------------------------------------------------------------------------------------*/

/*==========================================================================================
                                  全局变量数据结构类型定义
==========================================================================================*/



/*==========================================================================================
                                        全局常量声明
==========================================================================================*/
#define KEY1_IN_STA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) 
#define KEY2_IN_STA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)




/*==========================================================================================
                                        全局变量声明
==========================================================================================*/

/*--------------------------------------------------------------------------------------
的全局变量声明：
--------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------
的全局变量声明：
--------------------------------------------------------------------------------------*/


/*==========================================================================================
                                 源程序文件中的函数原型声明
==========================================================================================*/
/*--------------------------------------------------------------------------------------  
 函数名称：    KEY的初始化。  
 函数功能：    本函数用于KEY的初始化操作。  
 函数入口参数 ：没有  
 函数返回值 ：  没有  
 调用函数：　　１．  
　　　　　　　　　  
 备注：       
               本函数仅在主函数中调用一次即可 。  
--------------------------------------------------------------------------------------*/  
void Key_Init(void);






/*==========================================================================================
下面这三条指令是用于与上面三条区分编译系统为 C++ 或 C 的预处理指令相对应。用于指定
 extern "C" 链接指示符作用域，此处的"}"与上面的"{"相对应，为链接指示符作用结束符。
==========================================================================================*/
#ifdef __cplusplus
}
#endif


#endif                                        // “_Key_Deal_H_”条件编译结束


/*
********************************************************************************************
                                     本头文件到此结束
********************************************************************************************
*/


