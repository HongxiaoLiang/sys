/*
********************************************************************************************
 版权所有 (C)，2011－2015，泉州禾逸电子有限公司
----------------------------------------------------------------------------------------
源程序文件名：　　　Wifi.c
源程序名称：　　　　Wifi处理源程序
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
#include "Wifi.h"                        // Timer3处理的头文件
#include "DataMath.h"                    // 本程序的头部文件
#include "Usart1deal.h"                  // 串口1发送数据处理的头文件
#include "Keydeal.h"                     // 按键处理的头文件
#include "Mqtt.h"                        // Timer3处理的头文件

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
WIFI标志的全局变量声明：
--------------------------------------------------------------------------------------*/
WifiBits gbitWifi;


/*==========================================================================================
                             本源程序文件内部使用的局部变量定义
==========================================================================================*/

/*
********************************************************************************************
                             　       程序指令代码清单
********************************************************************************************
*/
/*-------------------------------------------------*/
/*函数名：初始化WiFi的复位IO                       */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void WiFiResetIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); 
	
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;      
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	RESET_IO(1);     

  gbitWifi.WifiMode = CLEAR;
}

/*-------------------------------------------------*/
/*函数名：WiFi发送设置指令                         */
/*参  数：cmd：指令                                */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
vs8  WiFiSendCmd(u8 *cmd, int timeout)
{
  Wifi_RxCounter = 0;
  MemClearSram(Wifi_RxBuf, (u8)Wifi_RxBuff_Size);

  Wifi_Printf("%s\r\n", cmd);
  while(timeout--)
  {
    Delay1ms(1000);
    if(strstr((char *)Wifi_RxBuf, "OK"))
      break;
    u1_printf("%d ",timeout);
  }
  u1_printf("\r\n");
  if(timeout <= 0)
    return 1;
  else
    return 0;
}


/*-------------------------------------------------*/
/*函数名：WiFi复位                                 */
/*参  数：timeout：超时时间（100ms的倍数）         */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
vs8  WiFiReset(int timeout)
{
	RESET_IO(0);                          
	Delay1ms(1000);                           
	RESET_IO(1);                             
	Delay1ms(1000);      
  
  while(timeout--)
  {
    Delay1ms(100);
    if(strstr((char *)Wifi_RxBuf, "ready"))
      break;
    u1_printf("%d ",timeout);
  }
  u1_printf("\r\n");
  if(timeout <= 0)
    return 1;
  else
    return 0;
}

/*-------------------------------------------------*/
/*函数名：WiFi加入路由器指令                       */
/*参  数：timeout：超时时间（1s的倍数）            */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
vs8 WiFiJoinAP(int timeout)
{
	Wifi_RxCounter=0;            
  
  MemClearSram(Wifi_RxBuf, (u8)Wifi_RxBuff_Size);
  
	Wifi_Printf("AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASS);
	while(timeout--)
  {                          
		Delay1ms(1000);                      
		if(strstr((char *)Wifi_RxBuf, "WIFI GOT IP\r\n\r\nOK"))
			break;       						 
		u1_printf("%d ",timeout);                
	}
	u1_printf("\r\n");                          
	if(timeout<=0)
    return 1;                        
	return 0;                                    
}


/*-------------------------------------------------*/
/*函数名：连接TCP服务器，并进入透传模式            */
/*参  数：timeout： 超时时间（100ms的倍数）        */
/*返回值：0：正确  其他：错误                      */
/*-------------------------------------------------*/
vs8 WiFiConnectServer(int timeout)
{
  Wifi_RxCounter = 0; 

  MemClearSram(Wifi_RxBuf, (u8)Wifi_RxBuff_Size);

  /* 连接服务器 */
  Wifi_Printf("AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", gstvUserNet.ServerIp, gstvUserNet.ServerPort);  
  while(timeout--)
  {
    Delay1ms(200);
    if(strstr((char *)Wifi_RxBuf, "CONNECT"))
      break;
    if(strstr((char *)Wifi_RxBuf, "CLOSED"))
      return 1;
    if(strstr((char *)Wifi_RxBuf, "ALREADY CONNECTED"))
      return 2;
    u1_printf("%d", timeout);
  }
  u1_printf("\r\n");

  if(timeout <= 0)
    return 3;
  else
  {
    timeout = 50;
    u1_printf("连接服务器成功，准备进入透传\r\n");
    Wifi_RxCounter = 0; 
    MemClearSram(Wifi_RxBuf, (u8)Wifi_RxBuff_Size);
    Wifi_Printf("AT+CIPSEND\r\n");  // 发送进入透传指令
    while(timeout--)
    {
      Delay1ms(200);
      if(strstr((char *)Wifi_RxBuf,"\r\nOK\r\n\r\n>"))
        break;
      u1_printf("%d", timeout);
    }
    if(timeout <= 0)
      return 4;
  }

  return 0;  // 成功
}

/*-------------------------------------------------*/
/*函数名：WiFi_Smartconfig                         */
/*参  数：timeout：超时时间（1s的倍数）            */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
vs8  WiFiSmartconfig(int timeout)
{
  Wifi_RxCounter = 0; 
  MemClearSram(Wifi_RxBuf, (u8)Wifi_RxBuff_Size);

  while(timeout--)
  {
    Delay1ms(1000);
    if(strstr((char *)Wifi_RxBuf,"connected"))
      break;
    u1_printf("%d", timeout);
  }
  u1_printf("\r\n");

  if(timeout <= 0)
    return 1;

  return 0;
}


/*-------------------------------------------------*/
/*函数名：等待加入路由器                           */
/*参  数：timeout：超时时间（1s的倍数）            */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
vs8  WiFiWaitAP(int timeout)
{
  while(timeout--)
  {
    Delay1ms(1000);
    if(strstr((char *)Wifi_RxBuf,"WIFI GOT IP"))
      break;
    u1_printf("%d", timeout);
  }
  u1_printf("\r\n");

  if(timeout <= 0)
    return 1;

  return 0;
}

/*-------------------------------------------------*/
/*函数名：WiFi连接服务器                           */
/*参  数：无                                       */
/*返回值：0：正确   其他：错误                     */
/*-------------------------------------------------*/
vs8 WifiConnectIoTServer(void)
{
	u1_printf("准备复位模块\r\n");              

//	if(WiFiReset(50))                               //复位，100ms超时单位，总计5s超时时间
//  {                              
//		u1_printf("复位失败，准备重启\r\n");           
//		return 1;                                     
//	}
//  else 
//    u1_printf("复位成功\r\n");                
	
	u1_printf("准备设置STA模式\r\n");              
	if(WiFiSendCmd("AT+CWMODE=1",50))                //设置STA模式，100ms超时单位，总计5s超时时间
  {                
		u1_printf("设置STA模式失败，准备重启\r\n");     
		return 2;                                      
	}
  else
    u1_printf("设置STA模式成功\r\n");         
	
	if(gbitWifi.WifiMode == CLEAR)                        //如果联网模式=0：SSID和密码写在程序里 
  {                                     
		u1_printf("准备取消自动连接\r\n");              
		if(WiFiSendCmd("AT+CWAUTOCONN=0",50))          //取消自动连接，100ms超时单位，总计5s超时时间
    {            
			u1_printf("取消自动连接失败，准备重启\r\n"); 
			return 3;                                    
		}
    else 
      u1_printf("取消自动连接成功\r\n");         
				
		u1_printf("准备连接路由器\r\n");                
		if(WiFiJoinAP(30))                              //连接路由器,1s超时单位，总计30s超时时间
//    {                             
//			u1_printf("连接路由器失败，准备重启\r\n");     
//			return 4;                                     
//		}
//    else
      u1_printf("连接路由器成功\r\n");            
	}
  else          //如果联网模式=1：Smartconfig方式,用APP发送
  {                                                
		if(KEY2_IN_STA==0)                                //如果此时K2是按下的
    {                                    
			u1_printf("准备设置自动连接\r\n");            
			if(WiFiSendCmd("AT+CWAUTOCONN=1",50))         //设置自动连接，100ms超时单位，总计5s超时时间
      {          
				u1_printf("设置自动连接失败，准备重启\r\n");  
				return 3;                                     
			}
      else
			  u1_printf("设置自动连接成功\r\n");           
			
			u1_printf("准备开启Smartconfig\r\n");             
			if(WiFiSendCmd("AT+CWSTARTSMART",50))        //开启Smartconfig，100ms超时单位，总计5s超时时间
      {          
				u1_printf("开启Smartconfig失败，准备重启\r\n");
				return 4;                                    
			}
      else 
        u1_printf("开启Smartconfig成功\r\n");      

			u1_printf("请使用APP软件传输密码\r\n");            
			if(WiFiSmartconfig(60))                       //APP软件传输密码，1s超时单位，总计60s超时时间
      {                         
				u1_printf("传输密码失败，准备重启\r\n");     
				return 5;                                     
			}
      else
        u1_printf("传输密码成功\r\n");            

			u1_printf("准备关闭Smartconfig\r\n");            
			if(WiFiSendCmd("AT+CWSTOPSMART",50))           //关闭Smartconfig，100ms超时单位，总计5s超时时间
      {            
				u1_printf("关闭Smartconfig失败，准备重启\r\n");
				return 6;                                      
			}
      else 
        u1_printf("关闭Smartconfig成功\r\n");       
		}
    else
    {                                                 
			u1_printf("等待连接路由器\r\n");                  
			if(WiFiWaitAP(30))                            //等待连接路由器,1s超时单位，总计30s超时时间
      {                               
				u1_printf("连接路由器失败，准备重启\r\n");    
				return 7;                                     
			}
      else 
        u1_printf("连接路由器成功\r\n");           
		}
	}
	
	u1_printf("准备设置透传\r\n");                    
	if(WiFiSendCmd("AT+CIPMODE=1",50))                //设置透传，100ms超时单位，总计5s超时时间
  {             
		u1_printf("设置透传失败，准备重启\r\n");      
		return 8;                                      
	}
  else 
    u1_printf("设置透传成功\r\n");             
	
	u1_printf("准备关闭多路连接\r\n");                
	if(WiFiSendCmd("AT+CIPMUX=0",50))                 //关闭多路连接，100ms超时单位，总计5s超时时间
  {               
		u1_printf("关闭多路连接失败，准备重启\r\n");   
		return 9;                                    
	}
  else
    u1_printf("关闭多路连接成功\r\n");          
	
	u1_printf("准备连接服务器\r\n");                 
	if(WiFiConnectServer(100))                       //连接服务器，100ms超时单位，总计10s超时时间
  {                      
		u1_printf("连接服务器失败，准备重启\r\n");    
		return 10;                                   
	}
  else 
    u1_printf("连接服务器成功\r\n");          
	
	return 0;          
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











