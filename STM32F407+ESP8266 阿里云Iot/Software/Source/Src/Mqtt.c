#include "Mqtt.h"                        // Timer3�����ͷ�ļ�
#include "DataMath.h"                    // �������ͷ���ļ�
#include "Mystring.h"                    // �������ͷ���ļ�
#include "utils_hmac.h"                  // ������Ҫ��ͷ�ļ�
#include "Usart1deal.h"                  // ����1�������ݴ����ͷ�ļ�
#include "string.h"                      // ������Ҫ��ͷ�ļ�
#include "stdio.h"                       // ������Ҫ��ͷ�ļ�


/*==========================================================================================
����������ָ�����������ֱ���ϵͳΪ C++ �� C ��Ԥ����ָ�
"__cplusplus" Ϊ C++ Ԥ���������֣�������ָ������������������Щָ��Ϊ C ����������
==========================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif


const DeviceMsgStru cDeviceMsgDefault[] = 
{
  "a1vqTyIII6X",
  0x0B,
  "D001",
  0x04,
  "6f0e8a03fd4366b5954cf1897b287ea7",
  0x20,
  "/sys/a1vqTyIII6X/D001/thing/event/property/set",
  "/sys/a1vqTyIII6X/D001/thing/event/property/post",
};






/*==========================================================================================
                                        ȫ�ֳ�������
==========================================================================================*/


/*==========================================================================================
                                        ȫ�ֱ�������
==========================================================================================*/
/*--------------------------------------------------------------------------------------
MQTT״̬����ȫ�ֱ�������:
--------------------------------------------------------------------------------------*/
MqttStateBits  gbitMqtt;

/*--------------------------------------------------------------------------------------
MQTT���ݵ�ȫ�����ݽṹ��ȫ�ֱ���������
--------------------------------------------------------------------------------------*/
MqttDataStru gstvMqtt;

/*--------------------------------------------------------------------------------------
�豸��Ϣ���ݵ�ȫ�����ݽṹ��ȫ�ֱ���������
--------------------------------------------------------------------------------------*/
DeviceMsgStru gstvDevice;

/*--------------------------------------------------------------------------------------
������Ϣ���ݵ�ȫ�����ݽṹ��ȫ�ֱ���������
--------------------------------------------------------------------------------------*/
UserNetMsgStru gstvUserNet;



/*==========================================================================================
                             ��Դ�����ļ��ڲ�ʹ�õľֲ���������
==========================================================================================*/

/*
********************************************************************************************
                             ��       ����ָ������嵥
********************************************************************************************
*/
/*----------------------------------------------------------*/
/*����������ʼ������,����,�������ݵ� ������ �Լ���״̬����  */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void MqttBuff_Init(void)
{
  MqttDataStru  *pMqtt;

  pMqtt = &gstvMqtt;

	MemClearSram(&gbitMqtt,     sizeof(MqttStateBits));
	MemClearSram2(&gstvMqtt,    sizeof(MqttDataStru));
	MemClearSram2(&gstvDevice,  sizeof(DeviceMsgStru));
	MemClearSram2(&gstvUserNet, sizeof(UserNetMsgStru));

  pMqtt->RxDataInPtr  = pMqtt->RxDataBuf[0];                // ָ���ͻ�����������ݵ�ָ���λ
  pMqtt->RxDataOutPtr = pMqtt->RxDataInPtr;                  // ָ���ͻ�������ȡ���ݵ�ָ���λ
  pMqtt->RxDataEndPtr = pMqtt->RxDataBuf[cMqttRxBufNum - 1]; // ָ���ͻ�����������ָ���λ

  pMqtt->TxDataInPtr  = pMqtt->TxDataBuf[0];                // ָ���ͻ�����������ݵ�ָ���λ
  pMqtt->TxDataOutPtr = pMqtt->TxDataInPtr;                  // ָ���ͻ�������ȡ���ݵ�ָ���λ
  pMqtt->TxDataEndPtr = pMqtt->TxDataBuf[cMqttTxBufNum - 1]; // ָ���ͻ�����������ָ���λ

  pMqtt->CmdDataInPtr  = pMqtt->CmdDataBuf[0];                 // ָ���ͻ�����������ݵ�ָ���λ
  pMqtt->CmdDataOutPtr = pMqtt->CmdDataInPtr;                  // ָ���ͻ�������ȡ���ݵ�ָ���λ
  pMqtt->CmdDataEndPtr = pMqtt->CmdDataBuf[cMqttTxBufNum - 1]; // ָ���ͻ�����������ָ���λ
}


/*----------------------------------------------------------*/
/*�����������³�ʼ������,����,������� �Լ���״̬����     */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void MqttBufRe_Init(void)
{
  MqttDataStru  *pMqtt;
  
  u8  *MqttTxDataTempPtr;       // ָ���ͻ�����λ�õ���ʱָ��

  pMqtt = &gstvMqtt;

  if(pMqtt->TxDataOutPtr != pMqtt->TxDataInPtr) // if�����Ļ���˵�����ͻ�������������
  {
    pMqtt->TxDataOutPtr = pMqtt->TxDataInPtr;
    if(pMqtt->TxDataOutPtr == pMqtt->TxDataBuf[0])
    {
      pMqtt->TxDataOutPtr = pMqtt->TxDataBuf[cMqttTxBufNum - 4];
    }
    else if(pMqtt->TxDataOutPtr == pMqtt->TxDataBuf[1])
    {
      pMqtt->TxDataOutPtr = pMqtt->TxDataBuf[cMqttTxBufNum - 3];
    }
    else if(pMqtt->TxDataOutPtr == pMqtt->TxDataBuf[2])
    {
      pMqtt->TxDataOutPtr = pMqtt->TxDataBuf[cMqttTxBufNum - 2];
    }
    else
    {
      pMqtt->TxDataOutPtr -= cMqttBuffSize;  // OUTָ������һ����Ԫ
      pMqtt->TxDataOutPtr -= cMqttBuffSize;  // OUTָ������һ����Ԫ
      pMqtt->TxDataOutPtr -= cMqttBuffSize;  // OUTָ������һ����Ԫ
    }

    MqttTxDataTempPtr = pMqtt->TxDataInPtr;
    pMqtt->TxDataInPtr = pMqtt->TxDataOutPtr;
    MqttSendConnectPack( );                           // �������ӱ���
    MqttSendSubscribe(gstvDevice.SubTopicName, 0);  //������Ӷ���topic���ȼ�0			
    pMqtt->TxDataInPtr = MqttTxDataTempPtr;
  }
  else
  {
    MqttSendConnectPack( );                           // �������ӱ���
    MqttSendSubscribe(gstvDevice.SubTopicName, 0);  //������Ӷ���topic���ȼ�0			
  }   
  gbitMqtt.ConnectPackFlag = CLEAR;
  gbitMqtt.SubcribePackFlag = CLEAR;
  gstvMqtt.PingFlag = 0;
}


/*----------------------------------------------------------*/
/*�������������Ƴ�ʼ���������õ��ͻ���ID���û���������      */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void AliIotParameter_Init(void)
{
  u8 temp[128];
  
  UserNetMsgStru  *pUserNet;
  DeviceMsgStru   *pDevice;

  pUserNet = &gstvUserNet;
  pDevice  = &gstvDevice;
  
	MemClearSram2(&gstvUserNet, sizeof(UserNetMsgStru));
  MemCopyFlashToSram2(&cDeviceMsgDefault, &gstvDevice, sizeof(DeviceMsgStru));

  sprintf((char *)pUserNet->ClientId, "%s|securemode=3,signmethod=hmacsha1|", pDevice->DeviceName);
  pUserNet->ClientIdLen = strlen((char *)pUserNet->ClientId);

	sprintf((char *)pUserNet->UserName, "%s&%s", pDevice->DeviceName, pDevice->ProductKey);                     
	pUserNet->UserNameLen = strlen((char *)pUserNet->UserName);                                      
	
	sprintf((char *)temp, "clientId%sdeviceName%sproductKey%s", pDevice->DeviceName, pDevice->DeviceName, pDevice->ProductKey);   
	utils_hmac_sha1((char *)temp, strlen((char *)temp), (char *)pUserNet->Passward, (char *)pDevice->DeviceSecre, pDevice->DeviceSecreLen);               
	pUserNet->PasswardLen = strlen((char *)pUserNet->Passward);                                                    
	
	sprintf((char *)pUserNet->ServerIp, "%s.iot-as-mqtt.cn-shanghai.aliyuncs.com", pDevice->ProductKey);                  
	pUserNet->ServerPort = 1883;                          
	
	u1_printf("�� �� ����%s:%d\r\n", pUserNet->ServerIp,pUserNet->ServerPort); 
	u1_printf("�ͻ���ID��%s\r\n", pUserNet->ClientId);          
	u1_printf("�� �� ����%s\r\n", pUserNet->UserName);             
	u1_printf("��    �룺%s\r\n", pUserNet->Passward);         
}


/*----------------------------------------------------------*/
/*�����������ӷ���������                                    */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void MqttSendConnectPack(void)
{
  MqttDataStru    *pMqtt;
  UserNetMsgStru  *pUserNet;

  pUserNet = &gstvUserNet;
  pMqtt    = &gstvMqtt;
  
	pMqtt->FixedLen    = 2;                                                   
	pMqtt->VariableLen = 10;                                                   
	pMqtt->PayloadLen  = 2 + pUserNet->ClientIdLen+ 2 + pUserNet->UserNameLen+ 2 + pUserNet->PasswardLen; 
	
	pMqtt->TxBuff[0]  = 0x10;              //��1���ֽ� ���̶�0x01	
	pMqtt->TxBuff[1]  = pMqtt->VariableLen + pMqtt->PayloadLen;        //��2���ֽ� ���ɱ䱨ͷ+��Ч���ɵĳ���
	pMqtt->TxBuff[2]  = 0x00;          		//��3���ֽ� ���̶�0x00	            
	pMqtt->TxBuff[3]  = 0x04;              //��4���ֽ� ���̶�0x04
	pMqtt->TxBuff[4]  = 0x4D;							//��5���ֽ� ���̶�0x4D
	pMqtt->TxBuff[5]  = 0x51;							//��6���ֽ� ���̶�0x51
	pMqtt->TxBuff[6]  = 0x54;							//��7���ֽ� ���̶�0x54
	pMqtt->TxBuff[7]  = 0x54;							//��8���ֽ� ���̶�0x54
	pMqtt->TxBuff[8]  = 0x04;							//��9���ֽ� ���̶�0x04
	pMqtt->TxBuff[9]  = 0xC2;						  //��10���ֽڣ�ʹ���û���������У�飬��ʹ���������������Ự
	pMqtt->TxBuff[10] = 0x00; 						  //��11���ֽڣ�����ʱ����ֽ� 0x00
	pMqtt->TxBuff[11] = 0xB4;						  //��12���ֽڣ�����ʱ����ֽ� 0x64   100s
	
	/* CLIENT_ID */
	pMqtt->TxBuff[12] = pUserNet->ClientIdLen/256;                			  			//�ͻ���ID���ȸ��ֽ�
	pMqtt->TxBuff[13] = pUserNet->ClientIdLen%256;               			  			//�ͻ���ID���ȵ��ֽ�
	memcpy(&pMqtt->TxBuff[14], pUserNet->ClientId, pUserNet->ClientIdLen);     //���ƹ����ͻ���ID�ִ�	
	
	/* �û��� */
	pMqtt->TxBuff[14 + pUserNet->ClientIdLen] = pUserNet->UserNameLen / 256; 				  		  //�û������ȸ��ֽ�
	pMqtt->TxBuff[15 + pUserNet->ClientIdLen] = pUserNet->UserNameLen % 256; 				 		    //�û������ȵ��ֽ�
	memcpy(&pMqtt->TxBuff[16+pUserNet->ClientIdLen], pUserNet->UserName, pUserNet->UserNameLen);             

	/* ���� */
	pMqtt->TxBuff[16+pUserNet->ClientIdLen+pUserNet->UserNameLen] = pUserNet->PasswardLen/256;			    //���볤�ȸ��ֽ�
	pMqtt->TxBuff[17+pUserNet->ClientIdLen+pUserNet->UserNameLen] = pUserNet->PasswardLen%256;			    //���볤�ȵ��ֽ�
	memcpy(&pMqtt->TxBuff[18+pUserNet->ClientIdLen+pUserNet->UserNameLen],pUserNet->Passward,pUserNet->PasswardLen); 

	TxDataBuf_Deal(&pMqtt->TxBuff[0], pMqtt->FixedLen + pMqtt->VariableLen + pMqtt->PayloadLen);  
}


/*----------------------------------------------------------*/
/*��������SUBSCRIBE����topic����                            */
/*��  ����QoS�����ĵȼ�                                     */
/*��  ����topic_name������topic��������                     */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void MqttSendSubscribe(u8  *topic_name, int Qos)
{
  MqttDataStru    *pMqtt;

  pMqtt    = &gstvMqtt;

  pMqtt->FixedLen    = 2;
  pMqtt->VariableLen = 2;
  pMqtt->PayloadLen  = 2 + strlen((char *)topic_name) + 1;

	pMqtt->TxBuff[0] = 0x82;                                        //��1���ֽ� ���̶�0x82                      
	pMqtt->TxBuff[1] = pMqtt->VariableLen + pMqtt->PayloadLen;       //��2���ֽ� ���ɱ䱨ͷ+��Ч���ɵĳ���	
	pMqtt->TxBuff[2] = 0x00;                                        //��3���ֽ� �����ı�ʶ�����ֽڣ��̶�ʹ��0x00
	pMqtt->TxBuff[3] = 0x01;		                                      //��4���ֽ� �����ı�ʶ�����ֽڣ��̶�ʹ��0x01
	pMqtt->TxBuff[4] = strlen((char *)topic_name)/256;                  //��5���ֽ� ��topic_name���ȸ��ֽ�
	pMqtt->TxBuff[5] = strlen((char *)topic_name)%256;		               //��6���ֽ� ��topic_name���ȵ��ֽ�
	memcpy(&pMqtt->TxBuff[6], topic_name, strlen((char *)topic_name));  //��7���ֽڿ�ʼ �����ƹ���topic_name�ִ�		
	pMqtt->TxBuff[6 + strlen((char *)topic_name)] = Qos;                  //���1���ֽڣ����ĵȼ�
	
	TxDataBuf_Deal(&pMqtt->TxBuff[0], pMqtt->FixedLen + pMqtt->VariableLen + pMqtt->PayloadLen);  //���뷢�����ݻ�����
}

/*----------------------------------------------------------*/
/*��������PING���ģ�������                                  */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void MqttSendPingReq(void)
{
  MqttDataStru    *pMqtt;
  
  pMqtt    = &gstvMqtt;
  
	pMqtt->TxBuff[0]=0xC0;              //��1���ֽ� ���̶�0xC0                      
	pMqtt->TxBuff[1]=0x00;              //��2���ֽ� ���̶�0x00 

	TxDataBuf_Deal(&pMqtt->TxBuff[0], 2);   //�������ݵ�������
}


/*----------------------------------------------------------*/
/*���������ȼ�0 ������Ϣ����                                */
/*��  ����topic_name��topic����                             */
/*��  ����data������                                        */
/*��  ����data_len�����ݳ���                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void MqttSendPublishQs0(u8  *topic, char *data, u16 data_len)
{
  MqttDataStru    *pMqtt;
  
  pMqtt    = &gstvMqtt;

	pMqtt->FixedLen    = 2;                                     //�̶���ͷ���ȣ�2�ֽ�
	pMqtt->VariableLen = 2 + strlen((char *)topic);                //�ɱ䱨ͷ���ȣ�2�ֽ�(topic����)+ topic�ַ����ĳ���
	pMqtt->PayloadLen  = data_len;                             //��Ч���ɳ��ȣ�����data_len
	
	pMqtt->TxBuff[0]=0x30;                                     //��1���ֽ� ���̶�0xC0                
	pMqtt->TxBuff[1]=pMqtt->VariableLen + pMqtt->PayloadLen;    //��2���ֽ� ���ɱ䱨ͷ+��Ч���ɵĳ���	
	pMqtt->TxBuff[2]=strlen((char *)topic)/256;                    //��3���ֽ� ��topic���ȸ��ֽ�
	pMqtt->TxBuff[3]=strlen((char *)topic)%256;		                 //��4���ֽ� ��topic���ȵ��ֽ�
	memcpy(&pMqtt->TxBuff[4],topic,strlen((char *)topic));         //��5���ֽڿ�ʼ ������topic�ַ���	
	memcpy(&pMqtt->TxBuff[4+strlen((char *)topic)],data,data_len);//����data����
	
	TxDataBuf_Deal(&pMqtt->TxBuff[0], pMqtt->FixedLen + pMqtt->VariableLen + pMqtt->PayloadLen);  //���뷢�����ݻ�����
}

/*----------------------------------------------------------*/
/*����������������������ĵȼ�0������                       */
/*��  ����redata�����յ�����                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void MQTTRecDealPushdataQs0(unsigned char *redata)
{
	int  re_len;               	            //����һ����������Ž��յ������ܳ���
	int  pack_num;                         //����һ�����������������һ�����ʱ���������͵ĸ���
  int  temp_len;                         //����һ���������ݴ�����
  int  totle_len;                        //����һ������������Ѿ�ͳ�Ƶ����͵���������
	int  topic_len;              	        //����һ���������������������ĳ���
	int  cmd_len;                          //����һ����������������а������������ݵĳ���
	int  cmd_loca;                         //����һ����������������а������������ʼλ��
	int  i;                                 //����һ������������forѭ��
	unsigned char temp[cMqttBuffSize];      //��ʱ������
	unsigned char *data;                    //redata������ʱ�򣬵�һ���ֽ�������������data����ָ��redata�ĵ�2���ֽڣ����������ݿ�ʼ�ĵط�
		
	re_len   = redata[0];                                  //��ȡ���յ������ܳ���
	data     = &redata[1];                                 //dataָ��redata�ĵ�2���ֽڣ����������ݿ�ʼ�� 
	pack_num = temp_len = totle_len = 0;                	  //������������
	do
  {
		pack_num++;                                     			//��ʼѭ��ͳ�����͵ĸ�����ÿ��ѭ�����͵ĸ���+1
		temp_len  = data[1+totle_len]+2;                 			//���㱾��ͳ�Ƶ����͵����ݳ���
		totle_len += temp_len;                          			//�ۼ�ͳ�Ƶ��ܵ����͵����ݳ���
		re_len    -= temp_len ;                            	  //���յ������ܳ��� ��ȥ ����ͳ�Ƶ����͵��ܳ���      
	}while(re_len!=0);                                  		//������յ������ܳ��ȵ���0�ˣ�˵��ͳ�������
	if(pack_num!=1)
    u1_printf("���ν�����%d����������\r\n",pack_num);    //���������Ϣ
	temp_len = totle_len = 0;                		           	//������������
	for(i=0;i<pack_num;i++)                                //�Ѿ�ͳ�Ƶ��˽��յ����͸�������ʼforѭ����ȡ��ÿ�����͵����� 
  {                            
		topic_len = data[2+totle_len]*256+data[3+totle_len] + 2;  //���㱾����������������ռ�õ�������
		cmd_len = data[1+totle_len]-topic_len;                      //���㱾��������������������ռ�õ�������
		cmd_loca = totle_len + 2 +  topic_len;                      //���㱾�������������������ݿ�ʼ��λ��
		memcpy(temp,&data[cmd_loca],cmd_len);                       //�������ݿ�������		                 
		CMDBuf_Deal(temp, cmd_len);                                 //�������������
		temp_len = data[1+totle_len]+2;                             //��¼�������͵ĳ���
		totle_len += temp_len;                                      //�ۼ��Ѿ�ͳ�Ƶ����͵����ݳ���
	}
}


/*----------------------------------------------------------*/
/*�������������ͻ�����                                    */
/*��  ����data������                                        */
/*��  ����size�����ݳ���                                    */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void TxDataBuf_Deal(unsigned char *data, int size)
{
  MqttDataStru    *pMqtt;
  
  pMqtt    = &gstvMqtt;
  
  MemCopyFlashToSram(&data[0], &pMqtt->TxDataInPtr[1], size);

	pMqtt->TxDataInPtr[0] = size;                  //��¼���ݳ���
  
	pMqtt->TxDataInPtr += cMqttBuffSize;            //ָ������
	if(pMqtt->TxDataInPtr == pMqtt->TxDataEndPtr)   //���ָ�뵽������β����
	{
		pMqtt->TxDataInPtr = pMqtt->TxDataBuf[0];         //ָ���λ����������ͷ
	}
}


/*----------------------------------------------------------*/
/*�������������������                                    */
/*��  ����data������                                        */
/*��  ����size�����ݳ���                                    */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void CMDBuf_Deal(unsigned char *data, int size)
{
  MqttDataStru    *pMqtt;
  
  pMqtt    = &gstvMqtt;
  
  MemCopyFlashToSram(&data[0], &pMqtt->CmdDataInPtr[1], size);

	pMqtt->CmdDataInPtr[0] = size;                   //��¼���ݳ���
	pMqtt->CmdDataInPtr[size+1] = '\0';              //�����ַ���������
	pMqtt->CmdDataInPtr += cMqttBuffSize;             //ָ������
	if(pMqtt->CmdDataInPtr == pMqtt->CmdDataEndPtr)   //���ָ�뵽������β����
	{
		pMqtt->CmdDataInPtr = pMqtt->CmdDataBuf[0];                 //ָ���λ����������ͷ
	}
}


/*==========================================================================================
����������ָ���������������������ֱ���ϵͳΪ C++ �� C ��Ԥ����ָ�����Ӧ������ָ��
 extern "C" ����ָʾ�������򣬴˴���"}"�������"{"���Ӧ��Ϊ����ָʾ�����ý�������
==========================================================================================*/
#ifdef __cplusplus
}
#endif


/*
********************************************************************************************
                                 ��������Դ�����ļ����˽���
********************************************************************************************
*/










