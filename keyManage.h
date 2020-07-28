/**
  ******************************************************************************
  * @file    keyManage.h
  * @author  const_zpc
  * @date    2020-6-20
  * @brief   ���ļ����� KEY ������������к���ԭ��
  ******************************************************************************
  * @attention
  *
  * ����
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SOURCE_FML_KEY_MANAGE_H_
#define SOURCE_FML_KEY_MANAGE_H_

/* Includes ------------------------------------------------------------------*/
#include "keyDrive.h"

/** @addtogroup FML_KEY
  * @{
  */

/** @addtogroup KEY_MANAGE
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  KEY����ö�ٶ���
  */
typedef enum{
    KEY_IS_NOT_PRESS = 0,           /*!< (0)û�а��� */
    KEY_IS_FRIST_PRESS,             /*!< (1)�״ΰ��� */
    KEY_IS_HOLD_PRESS,              /*!< (2)�������� */
    KEY_IS_LOOSEN,                  /*!< (3)�ɿ� */
    KEY_IS_LONG_HOLD_PRESS,         /*!< (4)�������´ﵽ����ʱ��(��ʹ�ܳ���ģʽ����Ч) */
    KEY_IS_LONG_LOOSEN              /*!< (5)�ﵽ����ʱ����ɿ�(��ʹ�ܳ���ģʽ����Ч) */
} KEY_ActionTypeDef;

typedef void (*KeyFun)(KEY_NameTypeDef, KEY_ActionTypeDef);

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* ��ʼ������ ******************************************************************/
extern void FML_KEY_ManageInit(void);

/* KEY ע��/ע������ ***********************************************************/
extern int  FML_KEY_Register(KEY_NameTypeDef emKeyName, KeyFun pKeyFun);
extern void FML_KEY_UnRegister(KEY_NameTypeDef emKeyName);

/* KEY ɨ�������� ************************************************************/
extern void FML_KEY_ScanTask(void);

/**
  * @}
  */

/**
  * @}
  */

#endif /* SOURCE_FML_KEY_MANAGE_H_ */
