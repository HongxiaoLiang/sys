/*
******************************************************************************************
��Ȩ���� (C)��2012��2015��Ȫ�ݺ��ݵ������޹�˾ 
----------------------------------------------------------------------------------------  
 Դ�����ļ��� ��      Main.c  
 Դ�������ƣ�        �������Դ�����ļ� ����汾������      1.0  
 STM8�⺯���汾 ����  V1.1.1  
 ������ ��  
 �����������������������Դ�����ļ���  
 ����˵�� ��  
��������  
 ���빤����� ��       
 �����ӳ����ļ� ��  
 ������ ��             
 ������ E-Mail��      
 �������� ��           
----------------------------------------------------------------------------------------  
 ��������оƬ���� :    
 ����оƬʱ��Ƶ�� :   
 �洢��ģʽ��        ��洢��ģʽ �ⲿ��չ�洢����С��0 ���ֽڡ� ���ݶ�ջ��С��      32 ��?

----------------------------------------------------------------------------------------  
 Դ����汾��ʷ �� 20������ --------  
 �汾 1.0 �����а汾  
******************************************************************************************
**  
*/ 

/*
==========================================================================================
 �������� ��  
==========================================================================================
*/  

/*
==========================================================================================
 ����������������������     ��Դ���������ͷ�ļ�������Դ�����ļ�  
==========================================================================================
*/  
#include "stm32f4xx.h"                           // STM32�⺯����ͷ�ļ�       
#include "Main.h"                                // �������ͷ�ļ�     
#include "String.h"                              // �ַ���������ͷ���ļ�  
#include <stdio.h>

#include "Timer1.h"                        // Timer3�����ͷ�ļ�
#include "Timer3.h"                        // Timer3�����ͷ�ļ�
#include "Timer4.h"                        // Timer4�����ͷ�ļ�
#include "Usart1deal.h"                    // ����1�������ݴ����ͷ�ļ�
#include "Usart2deal.h"                    // ����2�����ͷ�ļ�
#include "Wifi.h"                          // Timer3�����ͷ�ļ�
#include "main.h"
#include "Mqtt.h"                          // Timer3�����ͷ�ļ�
#include "Leddeal.h"                       // LED�����ͷ�ļ�
#include "Keydeal.h"                           // ���������ͷ�ļ�
#include "DataMath.h"                          // �������ͷ���ļ�
#include "delay.h"
#include "sys.h"

/*
==========================================================================================
                             ��Դ�����ļ��ڲ�ʹ�õĺ���ԭ������  
==========================================================================================
*/  

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/*
==========================================================================================
 �������ȫ�ֱ������� ��  
==========================================================================================
*/  
/*--------------------------------------------------------------------------------------  
 Tick��ʱȫ�ֱ�������  
--------------------------------------------------------------------------------------*/  
vu32        TimingDelay;  
int         CDTime= 0;               //��¼���ص���ʱʱ��

/*--------------------------------------------------------------------------------------
ϵͳ����ȫ�ֱ�־��ȫ�ֱ������壺
--------------------------------------------------------------------------------------*/
char  *CMD1 = "APP+OneSW=C";           // ���ؿ������״̬��ת�� ��->�� ��->��
char  *CMD2 = "APP+OneSW=?";           // ���ز�ѯ����ظ���������ǰ����״̬
char  *CMD3 = "APP+OneSWCD";           // ���ÿ��ص���ʱ

/*--------------------------------------------------------------------------------------  
 ���봦�������������־��ȫ�ֱ������� ��  
--------------------------------------------------------------------------------------*/  
/*  
******************************************************************************************
**  
                             ��       ����ָ������嵥  
******************************************************************************************
**  
*/  
/*
==========================================================================================
 �������ܣ�    ������������������  
==========================================================================================
*/  
int main(void)
{
  
/*--------------------------------------------------------------------------------------  
������������еĳ�ʼ������  
--------------------------------------------------------------------------------------*/  
  SystemInit();
  
  NVIC_Configuration();                       // nvic�ĳ�ʼ��
  
  delay_init(180);
 
  Delay1ms(1000);
  Delay1ms(1000);  
/*
==========================================================================================
 �������ܣ�   ��ʼ��һ��
==========================================================================================
*/  
 
	
  
  PrintUsart1_Init();    // ����1 ��ʼ�� ���ڴ�ӡ����
 
  EspAtUsart2_Init();   // ����2��ʼ��������ATָ���
  u1_printf("ϵͳ��ʼ���У���ʼ����������Ⱥ�...\r\n"); 

  Timer4_Init(300,8400-1);                    // TIM4��ʼ������ʱʱ�� 30ms

  LED_Init( );               // LED��ʼ��
 
  Key_Init( );               // ������ʼ��

  WiFiResetIO_Init( );      // ��ʼ��WIFI�ĸ�λIO

  MqttBuff_Init( );          // MQTT�������ʼ��

  AliIotParameter_Init( );  // ��ʼ�����Ӱ�����IoTƽ̨MQTT�������Ĳ���		

  Delay1ms(1000);
  u1_printf("ϵͳ��ʼ���ɹ�...\r\n"); 

  
/*--------------------------------------------------------------------------------------  
 �򿪿��Ź���ʱ�������ÿ��Ź���ʱ�������ʱʱ�� ��  
--------------------------------------------------------------------------------------*/  
  /* LSI������ */  
  RCC_LSICmd(ENABLE); //�� LSI  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET); //�ȴ�ֱ�� LSI�ȶ�  

  /*
  IWDG timeout equal to 480 ms (the timeout may varies due to LSI frequencydispersion) */  
#ifdef  cSysWdtEnable  
  /* Enable write access to IWDG_PR and IWDG_RLR registers */  
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  
 
  /* IWDG counter clock: 40KHz(LSI) / 64 = 0.625 KHz = 1.6ms*/  
  IWDG_SetPrescaler(IWDG_Prescaler_128);  
 
  /* Set counter reload value to 300*1.6ms = 480ms */  
  IWDG_SetReload(2000);  
 
  /* Reload IWDG counter */  
  IWDG_ReloadCounter();  
 
  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */  
  IWDG_Enable();  
#endif   

/*--------------------------------------------------------------------------------------  
 ������������еĳ�ʼ������Ҫ���ж� ����ֻ���У��εĺ���  
--------------------------------------------------------------------------------------*/  
 
  while(1)
  {
/*--------------------------------------------------------------------------------------  
��������������費��ѭ�����еĺ���  
--------------------------------------------------------------------------------------*/  
#ifdef  cSysWdtEnable  
  IWDG_ReloadCounter();  
#endif  

		/*--------------------------------------------------------------------*/
		/*   Connect_flag=1ͬ����������������,���ǿ��Է������ݺͽ���������    */
		/*--------------------------------------------------------------------*/
    if(gbitMqtt.ConnectFlag == 1)
    {
			/*-------------------------------------------------------------*/
			/*                     �����ͻ���������                      */
			/*-------------------------------------------------------------*/
      if(gstvMqtt.TxDataOutPtr != gstvMqtt.TxDataInPtr)
      {
        /*
         * 0x10: ���ӱ��� 
         * 0x82: ���ı��� 
         * SubcribePack_flag��λ��˵�����ӺͶ��ĳɹ�
         */
        if((gstvMqtt.TxDataOutPtr[1] == 0x10) 
          ||((gstvMqtt.TxDataOutPtr[1] == 0x82)
          &&(gbitMqtt.ConnectPackFlag == SET))
          ||(gbitMqtt.SubcribePackFlag ==SET))
        {
					u1_printf("��������:0x%x\r\n",gstvMqtt.TxDataOutPtr[1]);  //������ʾ��Ϣ
          MqttTxData(gstvMqtt.TxDataOutPtr);  // ��������
          gstvMqtt.TxDataOutPtr += cMqttBuffSize;
          if(gstvMqtt.TxDataOutPtr == gstvMqtt.TxDataEndPtr)
            gstvMqtt.TxDataOutPtr = gstvMqtt.TxDataBuf[0];
        }
      }

			/*-------------------------------------------------------------*/
			/*                     ������ջ���������                      */
			/*-------------------------------------------------------------*/
      if(gstvMqtt.RxDataOutPtr != gstvMqtt.RxDataInPtr)
      {
        u1_printf("���յ�����:");
				/*-----------------------------------------------------*/
				/*                    ����CONNACK����                  */
				/*-----------------------------------------------------*/		
        /*
         * ���������4���ֽڣ���һ���ֽ���0x20����ʾ�յ�����CONNACK����
         */
        if((gstvMqtt.RxDataOutPtr[0] == 4) 
          &&(gstvMqtt.RxDataOutPtr[1] == 0x20))
        {
          switch(gstvMqtt.RxDataOutPtr[4])
          {
            case 0x00:
              u1_printf("CONNECT���ĳɹ�\r\n");
              gbitMqtt.ConnectPackFlag = 1;
              break;
            case 0x01:
              u1_printf("�����Ѿܾ�����֧�ֵ�Э��汾��׼������\r\n");
              gbitMqtt.ConnectPackFlag = CLEAR;
              break;
            case 0x02:
              u1_printf("�����Ѿܾ������ϸ�Ŀͻ��˱�ʶ����׼������\r\n");
              gbitMqtt.ConnectPackFlag = CLEAR;
              break;
            case 0x03:
              u1_printf("�����Ѿܾ�������˲����ã�׼������\r\n");
              gbitMqtt.ConnectPackFlag = CLEAR;
              break;
            case 0x04:
              u1_printf("�����Ѿܾ�����Ч���û��������룬׼������\r\n");
              gbitMqtt.ConnectPackFlag = CLEAR;
              break;
            case 0x05:
              u1_printf("�����Ѿܾ���δ��Ȩ��׼������\r\n"); 
              gbitMqtt.ConnectPackFlag = CLEAR;
              break;
            default:
              u1_printf("�����Ѿܾ���δ֪״̬��׼������\r\n"); 
              gbitMqtt.ConnectPackFlag = CLEAR;
              break;
          }
        }    
        /* ���һ�����յ���5���ֽڣ���һ���ֽ���0x90,��ʾ�յ�����suback���� */
        else if((gstvMqtt.RxDataOutPtr[0] == 5) 
               &&(gstvMqtt.RxDataOutPtr[1] == 0x90))
        {
          switch(gstvMqtt.RxDataOutPtr[5])
          {
            case 0x00:
            case 0x01:
              u1_printf("���ĳɹ�\r\n");
              gbitMqtt.SubcribePackFlag = SET;
              gstvMqtt.PingFlag = 0;
              TIM3_ENABLE_30S( );   // ����30S�Ķ�ʱ��
              break;
            default:
              u1_printf("����ʧ�ܣ�׼������\r\n");
              gbitMqtt.ConnectFlag = CLEAR;
          }
        } 
        /* ������յ���2���ֽڣ���һ���ֽ���0xd0����ʾ�յ���PINGRESP���� */
        else if((gstvMqtt.RxDataOutPtr[0] == 0X02)
          &&(gstvMqtt.RxDataOutPtr[1] == 0xd0))
        {
          u1_printf("PING���Ļظ�\r\n");
          if(gstvMqtt.PingFlag == 1)
          {
            gstvMqtt.PingFlag = 0;
          }
          else
          {
            gstvMqtt.PingFlag = 0;
            TIM3_ENABLE_30S( );
          }
        }
        /* ������յ��ĵ�һ���ֽ���0x30,��ʾ�յ����Ƿ������������������� */
        else if(gstvMqtt.RxDataOutPtr[1] == 0x30)
        {
          u1_printf("�������ȼ�0����\r\n");
          MQTTRecDealPushdataQs0(gstvMqtt.RxDataOutPtr);
        }

        gstvMqtt.RxDataOutPtr += cMqttBuffSize;
        if(gstvMqtt.RxDataOutPtr == gstvMqtt.RxDataEndPtr)
        {
          gstvMqtt.RxDataOutPtr = gstvMqtt.RxDataBuf[0];
        }
      }
      
			/*-------------------------------------------------------------*/
			/*                     ���������������                      */
			/*-------------------------------------------------------------*/
      if(gstvMqtt.CmdDataOutPtr != gstvMqtt.CmdDataInPtr)
      {
        gstvMqtt.CmdDataOutPtr[gstvMqtt.CmdDataOutPtr[0]+1] = '\0';
        u1_printf("����:%s\r\n", &gstvMqtt.CmdDataOutPtr[1]);
        if(!memcmp(&gstvMqtt.CmdDataOutPtr[1], CMD1, strlen(CMD1)))  //�ж�ָ������CMD1
        {
          LED1_OUT(!LED1_IN_STA);
          LED_CD_State( );
        }
        else if(!memcmp(&gstvMqtt.CmdDataOutPtr[1], CMD2, strlen(CMD1)))   //�ж�ָ������CMD2���ظ�����״̬
        {
          LED_CD_State( );
        }
        else if(!memcmp(&gstvMqtt.CmdDataOutPtr[1], CMD3, strlen(CMD1)))   //�ж�ָ������CMD3�����õ���ʱʱ�� 
        {
          CDTime = gstvMqtt.CmdDataOutPtr[12];   // ��¼����ʱʱ��
          if(CDTime != 0)
          {
            u1_printf("����ʱ:%d����\r\n",CDTime);   
            TIM1Enable60s( );
          }
          else
          {
            u1_printf("ȡ������ʱ\r\n");
            TIM_Cmd(TIM1, DISABLE);
          }
          LED_CD_State();
        }
        else
        {
          u1_printf("δָ֪��\r\n");
        }

        gstvMqtt.CmdDataOutPtr += cMqttBuffSize;
        if(gstvMqtt.CmdDataOutPtr == gstvMqtt.CmdDataEndPtr)
        {
          gstvMqtt.CmdDataOutPtr = gstvMqtt.CmdDataBuf[0];
        }
      }
    }
    else
    {
      u1_printf("��Ҫ���ӷ�����...\r\n");
      TIM_Cmd(TIM4, DISABLE);
      TIM_Cmd(TIM3, DISABLE);

      Wifi_RxCounter = 0;
      memset(Wifi_RxBuf, 0, Wifi_RxBuff_Size);
      if(WifiConnectIoTServer( ) == 0)
      {
        u1_printf("����TCP���ӳɹ�...\r\n");   
        gbitMqtt.ConnectFlag = SET;

        Wifi_RxCounter = 0;
        memset(Wifi_RxBuf, 0, Wifi_RxBuff_Size);
        MqttBufRe_Init( );       // ���³�ʼ��
      }
    }    
  }
}

/*-------------------------------------------------*/
/*���������жϿ��غ͵���ʱ״̬����������������     */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void LED_CD_State(void)
{
  char temp[20];

  MemClearSram(&temp, 20);
 
  sprintf(temp, "+OneSW:");     // �����ظ�����
 
  if(LED1_IN_STA) 
   temp[7] = '0';
  else
   temp[7] = '1';
  temp[8] = CDTime;
 
  MqttSendPublishQs0(gstvDevice.PubTopicName, temp, 9);
}


/*--------------------------------------------------------------------------------------  
 �������ƣ�    nvic�ĳ�ʼ����  
 �������ܣ�    ����������nvic�ĳ�ʼ��������  
 ������ڲ��� ��û��  
 ��������ֵ ��  û��  
 ���ú�������������  
������������������  
 ��ע��        NVIC_PriorityGroup_2   
               �����������������е���һ�μ��� ��  
--------------------------------------------------------------------------------------*/  
void NVIC_Configuration(void)
{
  /* Configure the NVIC Preemption Priority Bits */   
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}


/*--------------------------------------------------------------------------------------  
 �������ƣ�    ��ʱ100us����  
 �������ܣ�    ����������ϵͳ��ʱ100us������  
 ������ڲ��� ��û��  
 ��������ֵ ��  û��  
 ���ú�������������  
������������������  
 ��ע��         
--------------------------------------------------------------------------------------*/  
void Delay50us(vu32 Timing100usCnt)
{  
  u32 i;
  for(i=0; i<Timing100usCnt; i++)
  {
    delay_us(50);
    #ifdef  cSysWdtEnable  
    IWDG_ReloadCounter();  
    #endif  
  }
}  

/*--------------------------------------------------------------------------------------
�������ƣ�������ʱ100us����
�������ܣ�����������������ʱ100us����
������ڲ�����
��������ֵ����û��
�������ڲ�����?
���ú�������������
��ע��        
--------------------------------------------------------------------------------------*/
void  Delay1ms(u32 DelayCnt)
{
  u32 i;
  for(i=0; i<DelayCnt; i++)
  {
    delay_us(1000);
    #ifdef  cSysWdtEnable  
    IWDG_ReloadCounter();  
    #endif  
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {
  }
  return ch;
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/  


