/*
********************************************************************************************
Դ�����ļ�����      String.c
Դ�������ƣ�        �ַ���������Դ�����ļ�
����汾������      1.4
�����ܣ�
�����������������ַ���������Դ�����ļ���

����˵����
�����������ļ������к������ǿ������Ժ�����

�����ӳ����ļ�������
�������������������㼰����ת������ѧ�㷨��Դ�����ļ���DataMath.c��
������������˵�������ô��ļ��е���� SRAM ���ֽ����ݺ��������̳�����롣
������������������Դ�����ļ���Դ�����ļ���Main.c��
������������˵����ʹ�ô��ļ��е�"gbitMcuFlag.SecUpd"��־λ��

���빤�������      IAR Embedded Workbench for Atmel AVR �汾��5.20A ����

�����ߣ�            Hbyin
�������ڣ�          2009��07��09��
----------------------------------------------------------------------------------------
��������оƬ����:   Ƕ��ʽ΢������
��������оƬ���ͣ�  Ƕ��ʽ΢������
����оƬʱ��Ƶ�ʣ�  ����
�洢��ģʽ��        û��Ҫ��
�ⲿ��չ�洢����С��û��Ҫ�� ���ֽڡ�
���ö�ջ��С��      û��Ҫ�� ���ֽڡ�
���ݶ�ջ��С��      û��Ҫ�� ���ֽڡ�
----------------------------------------------------------------------------------------
Դ����汾��ʷ��
2009��07��09�ա���Hbyin��  -------- �汾 1.0 �����а汾
********************************************************************************************
*/


/*==========================================================================================
                                        ���Կ�������
==========================================================================================*/
//#define DEBUG


/*==========================================================================================
                                    ��Դ���������ͷ�ļ�
���飺��������Ŀ���ļ�ʹ�� #include "�ļ���.��չ��" ��
      ����ϵͳ����ļ�ʹ�� #include <�ļ���.��չ��> ��
==========================================================================================*/
#include "Mystring.h"                           // �������ͷ���ļ�


/*==========================================================================================
����������ָ�����������ֱ���ϵͳΪ C++ �� C ��Ԥ����ָ�
"__cplusplus" Ϊ C++ Ԥ���������֣�������ָ������������������Щָ��Ϊ C ����������
==========================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif


/*==========================================================================================
                            ��Դ�����ļ��ڲ�ʹ�õ��ַ�����������
==========================================================================================*/



/*==========================================================================================
                             ��Դ�����ļ��ڲ�ʹ�õĺ���ԭ������
==========================================================================================*/



/*==========================================================================================
                                        ȫ�ֳ�������
==========================================================================================*/



/*==========================================================================================
                                        ȫ�ֱ�������
==========================================================================================*/



/*==========================================================================================
                             ��Դ�����ļ��ڲ�ʹ�õľֲ���������
==========================================================================================*/



/*==========================================================================================
                        ��Դ�����ļ��ڲ�ʹ�õľֲ���̬�;�̬��������
==========================================================================================*/



/*
********************************************************************************************
                             ��       ����ָ������嵥
********************************************************************************************
*/
/*==========================================================================================
�������ƣ����������ַ������ֽ����ݴ� SRAM �� SRAM ��
�������ܣ������������ǽ��ַ������ֽ����ݴ�Դ SRAM ���Ƶ�Ŀ�� SRAM �еĺ�����
������ڲ�����*pSource ------ �洢�� SRAM �е�Դ���ݵ��׸���ַָ�롣
              *pObject ------ �洢�� SRAM �е�Ŀ�����ݵ��׸���ַָ�롣
��������ֵ���������ַ����ĵ������ֽڳ��ȣ���������
���ú�������������
��ע��        ����ע�⣺��*pSource���洢�����ȱ�����ڵ��ڡ�*pObject���洢�����ȡ�
==========================================================================================*/
unsigned char  StrCopySramToSram (void *pSource, void *pObject)
{
  unsigned char       *pSrc;
  unsigned char       *pDst;
  unsigned char       cnt;

  pSrc    =  pSource;
  pDst    =  pObject;
  cnt     =  0;
  while (*pSrc)
  {
    *pDst =  *pSrc;
    pDst++;
    pSrc++;
    cnt++;
  }
  return(cnt);
}

unsigned int  StrCopySramToSram2 (void *pSource, void *pObject)
{
  unsigned char       *pSrc;
  unsigned char       *pDst;
  unsigned int        cnt;

  pSrc    =  pSource;
  pDst    =  pObject;
  cnt     =  0;
  while (*pSrc)
  {
    *pDst =  *pSrc;
    pDst++;
    pSrc++;
    cnt++;
  }
  return(cnt);
}


/*==========================================================================================
�������ƣ����������ַ������ֽ����ݴ� const �� SRAM ��
�������ܣ������������ǽ��ַ������ֽ����ݴ�Դ const ���Ƶ�Ŀ�� SRAM �еĺ�����
������ڲ�����*pSource ------ �洢�� const �е�Դ���ݵ��׸���ַָ�롣
              *pObject ------ �洢�� SRAM �е�Ŀ�����ݵ��׸���ַָ�롣
��������ֵ���������ַ����ĵ������ֽڳ��ȣ���������
���ú�������������
��ע��        ����ע�⣺��*pSource���洢�����ȱ�����ڵ��ڡ�*pObject���洢�����ȡ�
==========================================================================================*/
unsigned char  StrCopyFlashToSram (void const *pSource, void *pObject)
{
  unsigned char const *pSrc;
  unsigned char       *pDst;
  unsigned char       cnt;

  pSrc    =  pSource;
  pDst    =  pObject;
  cnt     =  0;
  while (*pSrc)
  {
    *pDst =  *pSrc;
    pDst++;
    pSrc++;
    cnt++;
  }
  return(cnt);
}

unsigned int  StrCopyFlashToSram2 (void const *pSource, void *pObject)
{
  unsigned char const *pSrc;
  unsigned char       *pDst;
  unsigned int        cnt;

  pSrc    =  pSource;
  pDst    =  pObject;
  cnt     =  0;
  while (*pSrc)
  {
    *pDst =  *pSrc;
    pDst++;
    pSrc++;
    cnt++;
  }
  return(cnt);
}

/*==========================================================================================
�������ƣ��������ַ��� *pSource ���������ַ��� *pTarget ƥ������ַ�����
�������ܣ�    �����������ַ��� *pSource ���������ַ��� *pTarget ƥ������ַ���������ҵ�ƥ��
�������������������ַ��������� *pSource �е����ַ�������ʼ��ַָ�룻���򷵻� NULL��
������ڲ�����*pSource ------ ָ��洢�� SRAM �е�Դ�ַ������׸���ַָ�롣
              *pTarget ------ ָ��洢�� SRAM �е�Ŀ���ַ������׸���ַָ�롣
��������ֵ������*pSource �е����ַ�������ʼ��ַָ�롱��ʾ������ƥ������ַ�����
              ��NULL��                               ��ʾû��������ƥ������ַ�����
���ú�������������
��ע��        ����
==========================================================================================*/
void  *StrStr (void *pSource, void *pTarget)
{
  unsigned char *pSrc;
  unsigned char *pDst;
  unsigned char *s;
  unsigned char *t;

  pSrc    =  pSource;
  pDst    =  pTarget;
  if (*pDst == '\0')                          // ���Ŀ���ַ��� pDst Ϊ��
  {
    return(pSrc);                             // ��ֱ�ӷ��ء�pSrc ����ʼ��ַָ��
  }

  while (*pSrc)
  {
    s     =  pSrc;
    t     =  pDst;
    while (*t && *s == *t)
    {
      ++s;
      ++t;
    }

    if (*t == '\0')
    {
      return(pSrc);
    }
    ++pSrc;
    while (*pSrc != '\0' && *pSrc != *pDst)
    {
      ++pSrc;
    }
  }
  return(NULL);
}

/*==========================================================================================
�������ƣ��������ַ��� *pSource �������� const �洢�����ַ��� *pTarget ƥ������ַ�����
�������ܣ�    �����������ַ��� *pSource ���������ַ��� *pTarget ƥ������ַ���������ҵ�ƥ��
�������������������ַ��������� *pSource �е����ַ�������ʼ��ַָ�룻���򷵻� NULL��
������ڲ�����*pSource ------ ָ��洢�� SRAM �е�Դ�ַ������׸���ַָ�롣
              *pTarget ------ ָ��洢�� const �е�Ŀ���ַ������׸���ַָ�롣
��������ֵ������*pSource �е����ַ�������ʼ��ַָ�롱��ʾ������ƥ������ַ�����
              ��NULL��                               ��ʾû��������ƥ������ַ�����
���ú�������������
��ע��        ����
==========================================================================================*/
void  *StrStrFlash (void *pSource, void const *pTarget)
{
  unsigned char       *pSrc;
  unsigned char const *pDst;
  unsigned char       *s;
  unsigned char const *t;

  pSrc    =  pSource;
  pDst    =  pTarget;
  if (*pDst == '\0')                          // ���Ŀ���ַ��� pDst Ϊ��
  {
    return(pSrc);                             // ��ֱ�ӷ��ء�pSrc ����ʼ��ַָ��
  }

  while (*pSrc)
  {
    s     =  pSrc;
    t     =  pDst;
    while (*t && *s == *t)
    {
      ++s;
      ++t;
    }

    if (*t == '\0')
    {
      return(pSrc);
    }
    ++pSrc;
    while (*pSrc != '\0' && *pSrc != *pDst)
    {
      ++pSrc;
    }
  }
  return(NULL);
}
extern void *StrAscFlash(void *pSource, void const *pTarget, unsigned short SrcLen)
{
  unsigned char       *pSrc;
  unsigned char const *pDst;
  unsigned char       *s;
  unsigned char const *t;
	unsigned short       SLen;

  pSrc    =  pSource;
  pDst    =  pTarget;
	SLen    =  SrcLen;

 if (*pDst == '\0')                          // ���Ŀ���ַ��� pDst Ϊ��
  {
    return(pSrc);                             // ��ֱ�ӷ��ء�pSrc ����ʼ��ַָ��
  }

  while (SLen != 0x00)
  {
    s     =  pSrc;
    t     =  pDst;
    while (*s == *t)
    {
      ++s;
      ++t;
			if (*t == '\0')
		    {
		      return(pSrc);
		    }
    }

    
    ++pSrc;
		SLen--;
    while (SLen != 0x00 && *pSrc != *pDst)
    {
      ++pSrc;
			SLen--;
    }
  }
  return(NULL);
}	


void *StrUscFlash(void *pSource, void const *pTarget, unsigned char TarLen, unsigned short SrcLen)
{
  unsigned char       *pSrc;
  unsigned char const *pDst;
  unsigned char       *s;
  unsigned char const *t;
	unsigned char       Len;
	unsigned short       SLen;

  pSrc    =  pSource;
  pDst    =  pTarget;
	Len     =  TarLen;
	SLen    =  SrcLen;

  if (Len == 0x00)                           // ���Ŀ���ַ��� pDst Ϊ��
  {
    return(pSrc);                             // ��ֱ�ӷ��ء�pSrc ����ʼ��ַָ��
  }

  while (SLen != 0x00)
  {
    s     =  pSrc;
    t     =  pDst;
		Len   =  TarLen;
    while (*s == *t)
    {
      ++s;
      ++t;
			Len--;
			if (Len == 0x00)
		    {
		      return(pSrc);
		    }
    }

    
    ++pSrc;
		SLen--;
    while (SLen != 0x00 && *pSrc != *pDst)
    {
      ++pSrc;
			SLen--;
    }
  }
  return(NULL);
}	
/*--------------------------------------------------------------------------------------
�������ƣ��������ַ��� *pSource �������� const �洢�����ַ��� *pTarget ƥ������ַ�����
�������ܣ�    �����������ַ��� *pSource ���������ַ��� *pTarget ƥ������ַ���������ҵ�ƥ��
�������������������ַ��������� *pSource �е����ַ�������ʼ��ַָ�룻���򷵻� NULL��
������ڲ�����*pSource ------ ָ��洢�� SRAM �е�Դ�ַ������׸���ַָ�롣
              *pTarget ------ ָ��洢�� const �е�Ŀ���ַ������׸���ַָ�롣
��������ֵ������*pSource �е����ַ�������ʼ��ַָ�롱��ʾ������ƥ������ַ�����
              ��NULL��                               ��ʾû��������ƥ������ַ�����
���ú�������������
��ע��        ����
--------------------------------------------------------------------------------------*/
extern unsigned char StrStrFlashLen(void *pSource, void const *pTarget)
{
  unsigned char       *pSrc;
  unsigned char const *pDst;
  unsigned char       *s;
  unsigned char const *t;
	unsigned char				Len;
	
	Len			=  0x00;
  pSrc    =  pSource;
  pDst    =  pTarget;
	
  if (*pDst == '\0')                          // ���Ŀ���ַ��� pDst Ϊ��
  {
    return(Len);                             // ��ֱ�ӷ��ء�pSrc ����ʼ��ַָ��
  }

  Len		=  0x00;

  while (*pSrc)
  {
    s     =  pSrc;
    t     =  pDst;
		
		
    while (*t && *s == *t)
    {
      ++s;
      ++t;
			
    }

    if (*t == '\0')
    {
      return(Len);
    }
    ++pSrc;
		Len++;
    while (*pSrc != '\0' && *pSrc != *pDst)
    {
      ++pSrc;
			Len++;
    }
  }
  return(Len);
}
extern unsigned char StrAscFlashLen(void *pSource, void const *pTarget, unsigned short SrcLen)
{
  unsigned char       *pSrc;
  unsigned char const *pDst;
  unsigned char       *s;
  unsigned char const *t;
	unsigned char				Len;
	unsigned short       SLen;
	
	Len			=  0x00;
  pSrc    =  pSource;
  pDst    =  pTarget;
 
  SLen    =  SrcLen;

	
  Len		=  0x00;

  if (*pDst == '\0')                          // ���Ŀ���ַ��� pDst Ϊ��
  {
    return(Len);                             // ��ֱ�ӷ��ء�pSrc ����ʼ��ַָ��
  }
	
  while (SLen != 0x00)
  {
    s     =  pSrc;
    t     =  pDst;
		
    while (*s == *t)
    {
      ++s;
      ++t;
			if (*t == '\0')
		    {
		      return(Len);
		    }
    }
    ++pSrc;
		Len++;
		SLen--;
    while (SLen != 0x00  && *pSrc != *pDst)
    {
      ++pSrc;
			Len++;
			SLen--;
    }
  }
  return(Len);
}

extern unsigned char StrUscFlashLen(void *pSource, void const *pTarget, unsigned char TarLen, unsigned short SrcLen)
{
  unsigned char       *pSrc;
  unsigned char const *pDst;
  unsigned char       *s;
  unsigned char const *t;
	unsigned char				Len;
  unsigned char       tLen;
	unsigned short       SLen;
	
	Len			=  0x00;
  pSrc    =  pSource;
  pDst    =  pTarget;
  tLen    =  TarLen;
  SLen    =  SrcLen;

	
  Len		=  0x00;

  if (tLen == 0)                          // ���Ŀ���ַ��� pDst Ϊ��
  {
    return(Len);                             // ��ֱ�ӷ��ء�pSrc ����ʼ��ַָ��
  }
	
  while (SLen != 0x00)
  {
    s     =  pSrc;
    t     =  pDst;
		tLen    =  TarLen;
		
    while (*s == *t)
    {
      ++s;
      ++t;
			tLen--;
			if (tLen == 0)
		    {
		      return(Len);
		    }
    }
    ++pSrc;
		Len++;
		SLen--;
    while (SLen != 0x00  && *pSrc != *pDst)
    {
      ++pSrc;
			Len++;
			SLen--;
    }
  }
  return(Len);
}
/*==========================================================================================
�������ƣ�����Unicode ����ַ���ת��Ϊʮ������ʱ�Ӹ�ʽ��
�������ܣ�    ���������ڽ� Unicode ���ʱ���ʽ�ַ���ת��Ϊʮ������ʱ�Ӹ�ʽ��
������ڲ�����*Ucs2Str ------- ָ��洢 Unicode ���ʱ���ʽ�ַ�����ָ�롣
              Separator ------ ʱ���ʽ�ķָ����ţ�һ��Ϊ��:��(0x003A)��
              *pstDst -------- ָ��洢ʮ������ʱ�Ӹ�ʽ��ָ�롣
��������ֵ������TRUE ����ʾת�������ɹ���
����������������FALSE����ʾת������ʧ�ܡ�
���ú�������������
��ע��        ����Unicode �ַ���ʱ��ʱ���ʽ��[��][��]:[��][��]:[��][��]���ָ���Ϊ:(0x003A)
==========================================================================================*/
unsigned char  Ucs2StrDecodeClock (Uchar8           *Ucs2Str,
                                   Uint16           Separator,
                                   TimeClock_Stru   *pstDst)
{
  unsigned char i;
  unsigned char strlen;
  unsigned char len;

  i       =  0;
  while (i < 16)                              // ��ȡ Unicode ���ʱ���ʽ�ַ����ĳ���
  {
    if ((*Ucs2Str != 0x00) && (*Ucs2Str != (Uchar8)(Separator >> 8)))
    {
      break;
    }
    Ucs2Str++;
    if (((*Ucs2Str < '0') || (*Ucs2Str > '9'))  && \
        (*Ucs2Str != (Uchar8)(Separator & 0x00FF)) )
    {
      Ucs2Str--;
      break;
    }
    Ucs2Str++;
    i    +=  2;
  }

  strlen  = i;
  Ucs2Str = Ucs2Str - i;
  i       = 0;
  len     = 0;
  for (i=0; i<5; i+=2)
  {
    // ������һ���ָ���
    if ((*Ucs2Str       == (Uchar8)(Separator >> 8)) && \
        (*(Ucs2Str + 1) == (Uchar8)(Separator & 0x00FF)))
    {
      len      = i + 2;
      Ucs2Str  = Ucs2Str - i;
      Ucs2Str += 1;
      if (i > 2)                              // Сʱʱ��Ϊ��λ
      {
        i              = *Ucs2Str - '0';
        i            <<= 4;
        Ucs2Str       += 2;
        pstDst->Hou    = ((*Ucs2Str - '0') & 0x0F) + i;
        Ucs2Str       += 1;
      }
      else
      {
        if (i)                                // ���ָ���ǰ�Ƿ������ݣ�
        {
          pstDst->Hou  = ((*Ucs2Str - '0') & 0x0F);
          Ucs2Str     += 1;
        }
        else
        {
          Ucs2Str     -= 1;
          pstDst->Hou  = 0x00;
        }
      }

      Ucs2Str += 2;                           // ������һ���ָ���
      // �����ڶ����ָ���
      for (i=0; i<5; i+=2)
      {
        if ((*Ucs2Str       == (Uchar8)(Separator >> 8)) && \
            (*(Ucs2Str + 1) == (Uchar8)(Separator & 0x00FF)))
        {
          len      = len + i + 2;
          Ucs2Str  = Ucs2Str - i;
          Ucs2Str += 1;
          if (i > 2)                          // ����ʱ��Ϊ��λ
          {
            i                = *Ucs2Str - '0';
            i              <<= 4;
            Ucs2Str         += 2;
            pstDst->Min      = ((*Ucs2Str - '0') & 0x0F) + i;
            Ucs2Str         += 1;
          }
          else
          {
            if (i)                            // ���ָ���ǰ�Ƿ������ݣ�
            {
              pstDst->Min    = ((*Ucs2Str - '0') & 0x0F);
              Ucs2Str       += 1;
            }
            else
            {
              Ucs2Str       -= 1;
              pstDst->Min    = 0x00;
            }
          }

          Ucs2Str += 2;                       // �����ڶ����ָ���
          if (len >= strlen)
          {
            pstDst->Sec = 0x00;
          }
          else
          {
            Ucs2Str += 1;
            i        = strlen - len;
            if (i > 2)                        // ��ʱ��Ϊ��λ
            {
              i              = *Ucs2Str - '0';
              i            <<= 4;
              Ucs2Str       += 2;
              pstDst->Sec    = ((*Ucs2Str - '0') & 0x0F) + i;
            }
            else
            {
              pstDst->Sec    = ((*Ucs2Str - '0') & 0x0F);
            }
          }

          return(TRUE);
        }

        Ucs2Str += 2;
      }
      return(FALSE);
    }

    Ucs2Str += 2;
  }

  return(FALSE);
}


/*--------------------------------------------------------------------------------------
�������ƣ��������ַ��� *pSource ���������ַ��� *pTarget ƥ������ַ�����
�������ܣ�    �����������ַ��� *pSource ���������ַ��� *pTarget ƥ������ַ���������ҵ�ƥ��
�������������������ַ��������� *pSource �е����ַ�������ʼ��ַָ�룻���򷵻� NULL��
������ڲ�����*pSource ------ ָ��洢�� SRAM �е�Դ�ַ������׸���ַָ�롣
              *pTarget ------ ָ��洢�� SRAM �е�Ŀ���ַ������׸���ַָ�롣
��������ֵ������*pSource �е����ַ�������ʼ��ַָ�롱��ʾ������ƥ������ַ�����
              ��NULL��                               ��ʾû��������ƥ������ַ�����
���ú�������������
��ע��        ����
--------------------------------------------------------------------------------------*/
unsigned short StringLen(void const *pSource)
{
  unsigned const short       *pSrc;

	unsigned short       SLen;
	
	SLen			=  0x00;
  pSrc    =  pSource;


	while (*pSrc != 0x0000)
    {
     SLen++;
     pSrc++;
    }

  
  return(SLen);
}

/*--------------------------------------------------------------------------------------
�������ƣ���������8������ϳ�Unicode ��
�������ܣ���������������8������ϳ�Unicode ��
������ڲ�����*pSrc  --------  ָ��洢Դ�ַ�����������ָ�롣
  ������������*pDest --------- ָ��洢Ŀ�����ݣ�ʮ������������������ָ�롣
��������������strLen -------   Դ�ַ����������ֽڳ��ȣ�������ֵ����Ϊż������
��������ֵ����û��
���ú�����������.
��ע��        ����
--------------------------------------------------------------------------------------*/
void CharHexConvUsc(const void *pSource, void *pTarget, const unsigned char strLen)
{
  unsigned char        i;
  const unsigned char  *pSrc;
  unsigned short       *pDst;
  unsigned char        temp1, temp2;

  pSrc      =  pSource;
  pDst      =  pTarget;
  if(strLen != 0xff && strLen < 0xff)
  {
    for(i=0; i<strLen; i+=2)
    {
      temp1 = *pSrc++;
      temp2 = *pSrc++;
      *pDst++ = (temp2 << 8) | temp1++;
    }
  }
}

/*--------------------------------------------------------------------------------------
�������ƣ������������ַ������бȽϣ�Ȼ�󷵻رȽϽ��
�������ܣ��������������ڶ������ַ������бȽϣ�Ȼ�󷵻رȽϽ��
������ڲ�����*pSrc  --------  ָ��洢Դ�ַ�����������ָ�롣
  ������������*pDest --------- ָ��洢Ŀ�����ݣ�ʮ������������������ָ�롣
��������ֵ����û��
���ú�����������.
��ע��        ����
��s1<s2ʱ������Ϊ������
��s1==s2ʱ������ֵ= 0��
��s1>s2ʱ������������
--------------------------------------------------------------------------------------*/
int StrCmp(const unsigned char* str1, const unsigned char* str2)
{
	int ret = 0;
	while(!(ret=*(unsigned char*)str1-*(unsigned char*)str2) && *str1)
	{
		str1++;
		str2++;
	} 
	if (ret < 0)
	{
		return -1;
	}
	else if (ret > 0)
	{
		return 1;
	}
	return 0;
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
