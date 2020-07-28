/**
  ******************************************************************************
  * @file    key_cfg.c
  * @author  ������
  * @date    30-August-2019
  * @brief   ���ļ��ṩ����ģ�������ܣ��Թ���KEY��������������õ����¹��ܣ�
  *           + ���ذ��������Ϣ����
  *
  *
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "key_cfg.h"

/** @addtogroup FunctionalModuleLayer
  * @brief      ����ģ���
  * @{
  */

/** @addtogroup FML_KEY
  * @brief      KEY����ģ��
  * @{
  */

/** @addtogroup KEY_Cfg
  * @brief      KEY����������������
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
  * @brief  ������������Ϣ.
  * @note   �������Ƶ�ö��ֵ�������ֵ����ֵ��Ӧ
  */
KEY_ConfigInfoType g_arrtKeyConfigInfo[KEY_MAX_NUM] = {
    {KEY_1, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_2, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_3, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_4, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_5, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_6, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_7, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_8, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
    {KEY_9, KEY_SHORT_MODE, KEY_NOT_PRESS, 1, 0, 20, 0},
};

/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
