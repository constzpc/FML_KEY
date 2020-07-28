/**
  ******************************************************************************
  * @file    keyDrive.h
  * @author  const_zpc
  * @date    2020-6-20
  * @brief   ���ļ����� KEY ����������������к���ԭ��
  ******************************************************************************
  * @attention
  *
  * ����
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SOURCE_FML_KEY_DRIVE_H_
#define SOURCE_FML_KEY_DRIVE_H_

/* Includes ------------------------------------------------------------------*/
#include "typedefs.h"

/** @addtogroup FML_KEY
  * @{
  */

/** @addtogroup KEY_DRIVE
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ����/ģ�ⰴ������ö�ٶ���
  * @note   �ɲο�ԭ��ͼ�еĲ�������
  */
typedef enum{
    SCH_KEY_1 = 0,                                  /*!< (0)ԭ��ͼ�ϵ�KEY1 */
    SCH_KEY_2,
    SCH_KEY_3,
    SCH_KEY_4,
    SCH_KEY_5,
    SCH_KEY_6,
    SCH_KEY_7,
    SCH_KEY_8,
    SCH_KEY_9,
    SCH_KEY_10,
    SCH_KEY_11,
    SCH_KEY_12,
    SCH_KEY_13,
    SCH_KEY_14,
    SCH_KEY_15,
    SCH_KEY_16,
    
    /* ��ɾ��,����ͳ�ư�������Ŀ */
    KEY_MAX_NUM
} KEY_NameTypeDef;

/**
  * @brief  KEY����ö�ٶ���
  */
typedef enum{
    KEY_IS_OFF = 0,                         	/*!< (0)�Ͽ�(�޶���) */
    KEY_IS_ON = !KEY_IS_OFF                     /*!< (1)�պ�(�ж���) */
} KEY_StateTypeDef;

/**
  * @brief  ����ģʽѡ��ö��
  * @note   ����ģʽ�����ֶ̰��ͳ�������״̬��������ʱ�䳤��
  */
typedef enum{
    KEY_NORMAL_MODE = 0,                        /*!< (0)��ͨģʽ(Ĭ��) */
    KEY_LONG_MODE                               /*!< (1)֧�ֳ���ģʽ */
} KEY_ModeTypeDef;

/* Exported constants --------------------------------------------------------*/

/* �����Ķ�����Ϣ */
#define KEY_NOT_PRESS           ((uint8_t)0x00) /* û�а��� */
#define KEY_FRIST_PRESS         ((uint8_t)0x01) /* �״ΰ��� */
#define KEY_SHORT_HOLD_PRESS    ((uint8_t)0x02) /* �̰��������� */
#define KEY_SHORT_LOOSEN        ((uint8_t)0x04) /* �̰��ɿ� */
#define KEY_LONG_HOLD_PRESS     ((uint8_t)0x08) /* ������������ */
#define KEY_LONG_LOOSEN         ((uint8_t)0x10) /* �����ɿ� */

/* Exported macro ------------------------------------------------------------*/

/**
  * @brief  ȷ�ϻ�ȡ�İ��������������İ��������Ƿ����
  * @note   keyAction Ϊ��ȡ�İ�������, Action Ϊ�����İ�������
  * @retval 0,������; 1,����
  */
#define FML_KEY_CONFIRM_ACTION(keyAction, Action)  ((keyAction) == (Action) ? 1 : 0)

/* Exported functions --------------------------------------------------------*/

/* KEY Ӳ����ʼ������ */
extern void FML_KEY_DriveInit(void);

/* KEY ���ó�ʼ������ */
extern void FML_KEY_ConfigInit(void);

/* KEY ��Ϣ������ */
extern void FML_KEY_ConfigHandle(uint8_t callTime);

/* KEY ��ⰴ���Ƿ���ڶ������� */
extern int  FML_KEY_CheckIsAction(KEY_NameTypeDef emKeyName);

/* KEY ��ȡ������������ */
extern int  FML_KEY_ReadAction(KEY_NameTypeDef emKeyName);

/* KEY ���ð���ģʽ���� */
extern int  FML_KEY_ChangeMode(KEY_NameTypeDef emKeyName, KEY_ModeTypeDef  emMode);

/* KEY ���ð���������Чʱ�亯�� */
extern int  FML_KEY_ChangeTime(KEY_NameTypeDef emKeyName, uint16_t shortTime, uint16_t longTime);

/* KEY ��λ������������ */
extern int  FML_KEY_ResetAction(KEY_NameTypeDef emKeyName);

/**
  * @}
  */

/**
  * @}
  */

#endif /* SOURCE_FML_KEY_DRIVE_H_ */
