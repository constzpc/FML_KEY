/**
  ******************************************************************************
  * @file    key_cfg.h
  * @author  ������
  * @date    30-August-2019
  * @brief   ���ļ�����KEY��������������õ����к���ԭ��
  ******************************************************************************
  * @attention
  *
  * ����
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SOURCE_FML_KEY_KEY_CFG_H_
#define SOURCE_FML_KEY_KEY_CFG_H_

/* Includes ------------------------------------------------------------------*/
#include "key_drv.h"

/** @addtogroup FML_KEY
  * @{
  */

/** @addtogroup KEY_Cfg
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ����ģʽѡ��ö��
  * @note   ����ģʽ�����ֶ̰��ͳ�������״̬��������ʱ�䳤��
  */
typedef enum{
    KEY_SHORT_MODE = 0,                         /*!< (0)�̰���ģʽ(Ĭ��) */
    KEY_LONG_MODE,                              /*!< (1)����ģʽ */
}KEY_ModeTypeDef;

/**
  * @brief ����������Ϣ�ṹ�嶨��
  */
typedef struct{
    KEY_NameTypeDef emKeyName;                  /*!< ָ��(ģ��)���밴������ö�ٶ��� */

    KEY_ModeTypeDef  emLongMode;                /*!< ָ����ѡ��������ģʽ�Ľ���/ʹ��
                                                     This parameter can be any value of @ref KEY_ModeTypeDef */

    uint8_t actionInfo;                         /*!< ָ����ѡ�����Ķ�����Ϣ */

    uint8_t funEnable;                          /*!< ָ����ѡ�����Ĺ���ʹ��(1)/��ֹ(0) */

    uint16_t  pressTic;                         /*!< ָ����ѡ�����İ����ۼ�ʱ��
                                                     �ò�����λΪ1ms,��ֵ��ֵΪ0 */

    uint16_t shortPressMaxTic;                  /*!< ָ����ѡ�����Ķ̰���Чʱ��
                                                     �ò�����λΪ1ms,����ֵΪ KEY_ConfigInfoHandle ������������ �������� */

    uint16_t longPressMaxTic;                   /*!< ָ����ѡ�����ĳ�����Чʱ��(����ģʽ��ֹʱ��Ч)
                                                     �ò�����λΪ1ms,����ֵΪ KEY_ConfigInfoHandle ������������ �������� */
} KEY_ConfigInfoType;

/* Exported constants --------------------------------------------------------*/

/* �����Ķ�����Ϣ */
#define KEY_NOT_PRESS           ((uint8_t)0x00) /* û�а��� */
#define KEY_FRIST_PRESS         ((uint8_t)0x01) /* �״ΰ��� */
#define KEY_SHORT_HOLD_PRESS    ((uint8_t)0x02) /* �̰��������� */
#define KEY_SHORT_LOOSEN        ((uint8_t)0x04) /* �̰��ɿ� */
#define KEY_LONG_HOLD_PRESS     ((uint8_t)0x08) /* ������������ */
#define KEY_LONG_LOOSEN         ((uint8_t)0x10) /* �����ɿ� */

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern KEY_ConfigInfoType g_arrtKeyConfigInfo[KEY_MAX_NUM];

/* Exported functions --------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */


#endif /* SOURCE_FML_KEY_KEY_CFG_H_ */
