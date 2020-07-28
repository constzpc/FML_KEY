/**
  ******************************************************************************
  * @file    key_drv.h
  * @author  ������
  * @date    30-August-2019
  * @brief   ���ļ�����KEY����Ӳ���ӿڶ�������к���ԭ��
  ******************************************************************************
  * @attention
  *
  * ����
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_DRV_H_
#define __KEY_DRV_H_

/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/** @addtogroup FML_KEY
  * @{
  */

/** @addtogroup KEY_Drv
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ����/ģ�ⰴ������ö�ٶ���
  * @note   �ɲο�ԭ��ͼ�еĲ�������
  */
typedef enum{
    KEY_1 = 0,                              /*!< (0)ԭ��ͼ�ϵ�KEY1 */
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    
    /* ��ɾ��,����ͳ�ư�������Ŀ */
    KEY_MAX_NUM,
} KEY_NameTypeDef;

/**
  * @brief  KEY����ö�ٶ���
  */
typedef enum{
    KEY_IS_OFF = 0,                         /*!< (0)�Ͽ�(�޶���) */
    KEY_IS_ON = !KEY_IS_OFF,                /*!< (1)�պ�(�ж���) */
}KEY_StateTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* KEY ������ʼ�� *************************************************************/
extern uint8_t  KEY_Initialize(void);
    
/* ��ȡ/ģ�����а�����ԭʼ״̬���� ********************************************/
extern void     KEY_AllButtonInScan(void);

/* ��ȡָ������/ģ�ⰴ����ԭʼ״̬ ********************************************/
extern KEY_StateTypeDef KEY_GetButtonInState(KEY_NameTypeDef key);

#endif /* SOURCE_FML_KEY_KEY_DRV_H_ */
