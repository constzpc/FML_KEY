/**
  ******************************************************************************
  * @file    key_core.h
  * @author  ������
  * @version V2.0.0
  * @date    18-October-2019
  * @brief   ���ļ�����KEY����������ݴ�������к���ԭ��
  ******************************************************************************
  * @attention
  *
  * ����
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_KEY_CORE_H_
#define BSP_KEY_CORE_H_

/* Includes ------------------------------------------------------------------*/
#include "key_cfg.h"
#include "key_drv.h"

/** @addtogroup FML_KEY
  * @{
  */

/** @addtogroup KEY_Core
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/**
  * @brief  ȷ�ϻ�ȡ�İ��������������İ��������Ƿ����
  * @note   keyAction Ϊ��ȡ�İ�������, Action Ϊ�����İ�������
  * @retval 0,������; 1,����
  */
#define KEY_CONFIRM_ACTION(keyAction, Action)  ((keyAction) == (Action) ? 1 : 0)

/* Exported functions --------------------------------------------------------*/

/* KEY ��Ϣ��ʼ������ *********************************************************/
extern void     KEY_ConfigInfoInit(void);

/* KEY ��Ϣ������ ***********************************************************/
extern void     KEY_ConfigInfoHandle(void);

/* KEY ��ⰴ���Ƿ���ڶ������� ***********************************************/
extern uint8_t  KEY_CheckIsAction(uint8_t index);

/* KEY ��ȡ������������ *******************************************************/
extern uint8_t  KEY_ReadAction(uint8_t index);

/* KEY ���ð���ģʽ���� *******************************************************/
extern void     KEY_ChangeMode(uint8_t index, KEY_ModeTypeDef  emMode);

/* KEY ���ð���������Чʱ�亯�� ***********************************************/
extern void     KEY_ChangeShortTime(uint8_t index, uint16_t time);
extern void     KEY_ChangeLongTime(uint8_t index, uint16_t time);

/* KEY ��λ������������ *******************************************************/
extern void     KEY_ResetAction(uint8_t index);

/* KEY ʹ��/��ֹ����ɨ�躯�� **************************************************/
extern void     KEY_EnableScan(uint8_t index, uint8_t enable);

/**
  * @}
  */

/**
  * @}
  */

#endif /* SOURCE_FML_KEY_KEY_CORE_H_ */
