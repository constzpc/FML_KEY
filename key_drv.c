/**
  ******************************************************************************
  * @file    key_drv.c
  * @author  ������
  * @date    30-August-2019
  * @brief   ���ļ��ṩ����ģ�������ܣ��Թ���KEY����Ӳ���ӿڶ�������¹��ܣ�
  *           + (ģ��)�������а����Ŀ���״̬
  *           + ��ȡָ��(ģ��)���밴���Ŀ���״̬
  *
  ******************************************************************************
  * @attention
  * ���ı�Ӳ����·ʱ���޸ĸ��ļ��еĺ��� KEY_AllButtonInScan
  * ���ṩ��Ƭ�������Ӳ����Դ�ĳ�ʼ��
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "key_drv.h"

// HAL
#include "pal.h"

/** @addtogroup FunctionalModuleLayer
  * @brief      ����ģ���
  * @{
  */

/** @addtogroup FML_KEY
  * @brief      KEY����ģ��
  * @{
  */

/** @addtogroup KEY_Drv
  * @brief      KEY�����Ӳ���ӿڶ���
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* �������������صĵ�ƽ��Ϣ */
static KEY_StateTypeDef sg_arrKeyState[KEY_MAX_NUM];

/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/** @defgroup KEY_Drv_Private_Functions
  * @{
  */

/** @defgroup KEY�����Ӳ��������1 (ģ��)�������а����Ŀ���״̬
 *  @brief    (ģ��)�������а����Ŀ���״̬
 *
 @verbatim
 ===============================================================================
                 ##### (ģ��)�������а����Ŀ���״̬ #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      KEY�����ĳ�ʼ��.
  * @retval     0, �ɹ�; 1,ʧ��.
  */
uint8_t KEY_Initialize(void)
{
    uint8_t res = 0;
    

    return res;
}

/**
  * @brief      (ģ��)�������а����Ŀ���״̬.
  * @note       ģ��: ����IOֱ������,����������ʽ����,��ͨ��������źż�Ӿ����ð����Ŀ���״̬.
  * @param      None.
  * @retval     None.
  */
void KEY_AllButtonInScan(void)
{
    /* ���ذ���Ϊ�͵�ƽ, ���ȡ�� */
    sg_arrKeyState[KEY_1] = (KEY_StateTypeDef)!pal_readpad(PORT_A, 7);
    sg_arrKeyState[KEY_2] = (KEY_StateTypeDef)!pal_readpad(PORT_A, 3);
    sg_arrKeyState[KEY_3] = (KEY_StateTypeDef)!pal_readpad(PORT_A, 8);
    sg_arrKeyState[KEY_4] = (KEY_StateTypeDef)!pal_readpad(PORT_D, 14);
    sg_arrKeyState[KEY_5] = (KEY_StateTypeDef)!pal_readpad(PORT_D, 9);
    sg_arrKeyState[KEY_6] = (KEY_StateTypeDef)!pal_readpad(PORT_B, 15);
    sg_arrKeyState[KEY_7] = (KEY_StateTypeDef)!pal_readpad(PORT_E, 14);
    sg_arrKeyState[KEY_8] = (KEY_StateTypeDef)!pal_readpad(PORT_A, 14);
    sg_arrKeyState[KEY_9] = (KEY_StateTypeDef)!pal_readpad(PORT_B, 6);
}

/**
  * @}
  */

/** @defgroup KEY�����Ӳ��������2 ��ȡָ������/ģ�ⰴ����ԭʼ״̬
 *  @brief    ��ȡָ������/ģ�ⰴ����ԭʼ״̬
 *
 @verbatim
 ===============================================================================
                 ##### ��ȡָ������/ģ�ⰴ����ԭʼ״̬ #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      ��ȡָ��(ģ��)���밴���Ŀ���״̬.
  * @note       ��״̬û�о����˲��ȴ���
  * @param[in]  key - ��ֵΪ"KEY_NameTypeDef"�����ö��ֵ.
  * @retval     ����/ģ�ⰴ����ԭʼ״̬(�޶���, �ж���).
  */
KEY_StateTypeDef KEY_GetButtonInState(KEY_NameTypeDef emKeyName)
{
    return sg_arrKeyState[emKeyName];
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

