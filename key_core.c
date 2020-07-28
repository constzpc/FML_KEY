/**
  ******************************************************************************
  * @file    key_core.c
  * @author  ������
  * @version V2.0.0
  * @date    18-October-2019
  * @brief   ���ļ��ṩ����ģ�������ܣ��Թ���KEY����������ݴ�������¹��ܣ�
  *           + ������Ϣ��ʼ������
  *           + ������Ϣ������
  *           + ��ȡ������������
  *           + ����/��λ������ز�������
  *
  ******************************************************************************
  * @note �汾����˵��
  * v2.0.0      18-October-2019
  * 	1.������ָ������ɨ��ʶ����ʹ��/��ֹ
  * 	2.�������ָ�������Ƿ���ڶ���
  *
  * v1.1.0		30-August-2019
  * 	1.�Ż��ļ�ģ��ܹ�, �Ż��ײ������ӿں����ͺ��Ĺ������ģ��
  * 	2.�Ż�ģ�� API �ӿں���
  * 	3.���ֺ�����������������
  * 	4.�����Ż�����
  *
  * v1.0.0		22-January-2019
  * 	�װ淢��
  *
  ******************************************************************************
  * @attention
  * ������Ҫ���������BUGʱ���ļ���������Ķ�
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "key_core.h"
#include "key_cfg.h"

/** @addtogroup FunctionalModuleLayer
  * @brief      ����ģ���
  * @{
  */

/** @addtogroup FML_KEY
  * @brief      KEY����ģ��
  * @{
  */

/** @addtogroup KEY_Core
  * @brief      KEY�����������ݴ���
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** ��������ʱ��(��λ: 1ms) */
#define KEY_HANDLE_TIME     10
      
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void OneKeyShortModeHandle(KEY_ConfigInfoType * const ptKeyInfo);
static void OneKeyLongModeHandle(KEY_ConfigInfoType * const ptKeyInfo);

/* Private function ----------------------------------------------------------*/

/** @defgroup KEY_Core_Private_Functions
  * @{
  */

/** @defgroup KEY����ĺ���������1 KEY�������Ϣ��ʼ��
 *  @brief    KEY�������Ϣ��ʼ��
 *
 @verbatim
 ===============================================================================
                 ##### KEY�������Ϣ��ʼ�� #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      ����������Ϣ���г�ʼ��.
  * @retval     None.
  */
void KEY_ConfigInfoInit(void)
{
    uint8_t i;

    for (i = 0; i < KEY_MAX_NUM; i++)
    {
        g_arrtKeyConfigInfo[i].pressTic = 0;
        g_arrtKeyConfigInfo[i].actionInfo = KEY_NOT_PRESS;
    }
}

/**
  * @}
  */

/** @defgroup KEY����ĺ���������2 KEY��Ϣ������
 *  @brief    KEY��Ϣ������
 *
 @verbatim
 ===============================================================================
                         ##### KEY��Ϣ������ #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      ��ָ���̰�ģʽ�İ�����Ϣ���д���.
  * @param[in]  ptKeyInfo - ָ��"KEY_OperaInfoType"�ṹ�����͵�ָ��.
  * @param[out] ptKeyInfo - ָ��"KEY_OperaInfoType"�ṹ�����͵�ָ��
  * @retval     None.
  */
static void OneKeyShortModeHandle(KEY_ConfigInfoType * const ptKeyInfo)
{
    KEY_StateTypeDef emKeyState = KEY_GetButtonInState(ptKeyInfo->emKeyName);

    if (ptKeyInfo->pressTic < ptKeyInfo->shortPressMaxTic)
    {
        if (KEY_IS_ON == emKeyState)
        {
            ptKeyInfo->pressTic += KEY_HANDLE_TIME;
        }
        else
        {
            ptKeyInfo->pressTic = 0;                        /* δ�ﵽ�̰�ʱ�� */
        }
    }
    else
    {
        if (KEY_NOT_PRESS == ptKeyInfo->actionInfo)
        {
            ptKeyInfo->actionInfo |= KEY_FRIST_PRESS;
            ptKeyInfo->actionInfo |= KEY_SHORT_HOLD_PRESS;
        }
        else
        {
            if (KEY_IS_ON == emKeyState)
            {
                ptKeyInfo->actionInfo |= KEY_SHORT_HOLD_PRESS;
            }
            else
            {
                ptKeyInfo->pressTic = 0;
                ptKeyInfo->actionInfo |= KEY_SHORT_LOOSEN;
            }
        }
    }
}

/**
  * @brief      ��ָ������ģʽ�İ�����Ϣ���д���.
  * @param[in]  ptKeyInfo - ָ��"KEY_OperaInfoType"�ṹ�����͵�ָ��.
  * @param[out] ptKeyInfo - ָ��"KEY_OperaInfoType"�ṹ�����͵�ָ��
  * @retval     None.
  */
static void OneKeyLongModeHandle(KEY_ConfigInfoType * const ptKeyInfo)
{
    KEY_StateTypeDef emKeyState = KEY_GetButtonInState(ptKeyInfo->emKeyName);

    if (ptKeyInfo->pressTic < ptKeyInfo->shortPressMaxTic)
    {
        if (KEY_IS_ON == emKeyState)
        {
            ptKeyInfo->pressTic += KEY_HANDLE_TIME;
        }
        else
        {
            ptKeyInfo->pressTic = 0;                        /* δ����̰�ʱ�� */
        }
    }
    else
    {
        if (KEY_NOT_PRESS == ptKeyInfo->actionInfo)
        {
            ptKeyInfo->actionInfo |= KEY_FRIST_PRESS;
            ptKeyInfo->actionInfo |= KEY_SHORT_HOLD_PRESS;
        }
        else
        {
            if (ptKeyInfo->pressTic < ptKeyInfo->longPressMaxTic)
            {
                if (KEY_IS_ON == emKeyState)
                {
                    ptKeyInfo->pressTic += KEY_HANDLE_TIME;
                }
                else
                {
                    ptKeyInfo->pressTic = 0;                /* δ���㳤��ʱ�� */
                    ptKeyInfo->actionInfo |= KEY_SHORT_LOOSEN;
                }
            }
            else
            {
                if (KEY_IS_ON == emKeyState)
                {
                    ptKeyInfo->actionInfo |= KEY_LONG_HOLD_PRESS;
                }
                else
                {
                    ptKeyInfo->pressTic = 0;
                    ptKeyInfo->actionInfo |= KEY_LONG_LOOSEN;
                }
            }
        }
    }
}

/**
  * @brief      ��һ������ָ���İ�����Ϣ���д���.
  * @warning    ���ݸú����ĵ��������޸ĺ궨�� KEY_HANDLE_TIME.
  * @retval     None.
  */
void KEY_ConfigInfoHandle(void)
{
    uint8_t i;
    KEY_ConfigInfoType *ptKeyInfo = g_arrtKeyConfigInfo;
    void (*pKeyModeHandle[2])(KEY_ConfigInfoType*) = {OneKeyShortModeHandle, OneKeyLongModeHandle};

    for (i = 0; i < KEY_MAX_NUM; i++)
    {
    	if (ptKeyInfo[i].funEnable)
    	{
            /* ���ݰ�������ģʽ��ֹ/ʹ��ѡ��ͬ�ж����� */
            pKeyModeHandle[ptKeyInfo[i].emLongMode](&ptKeyInfo[i]);
    	}
    	else
    	{
    		ptKeyInfo[i].actionInfo = KEY_NOT_PRESS;
    	}
    }
}

/**
  * @}
  */

/** @defgroup KEY����ĺ���������3 KEY��ȡ������������
 *  @brief    KEY��ȡ������������
 *
 @verbatim
 ===============================================================================
                         ##### KEY��ȡ������������ #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      ���ָ�������Ƿ���ڶ���.
  * @param[in]  index - g_arrtKeyConfigInfo ������ֵ.
  * @retval     ��������, ���ص�ֵ��������:
  *             @arg 0,�޶���
  *             @arg 1,�ж���
  */
uint8_t KEY_CheckIsAction(uint8_t index)
{
	if (g_arrtKeyConfigInfo[index].actionInfo != 0)
	{
		return 1;
	}

	return 0;
}

/**
  * @brief      ��ȡָ�������Ķ�����Ϣ.
  * @note       1.���̰�ģʽ�°������һ�ζ���, �����º��ɿ�, ���������˳��ÿ�ε��øú�������֮ǰ�Ķ�����Ϣ��
  *                 �״ΰ��� -> �̰��������� -> �̰��ɿ�(Ҳ�ʺϳ���ģʽ�����һ�ζ̰�����).
  *             2.������ģʽ�°������һ�ζ���, �����´ﵽ����ʱ����ɿ�, ���������˳��ÿ�ε��øú�������֮ǰ�Ķ�����Ϣ��
  *                 �״ΰ��� -> �̰��������� -> ������������ -> �����ɿ�.
  *             3.����"��������"״̬�����ù�����û���ɿ�,��һֱ����
  *             4.ÿ�ε��øú�����ȡ����ʹ�ú궨������"KEY_CONFIRM_ACTION(keyAction, Action)"����Ƿ���϶�����Ϣ
  * @param[in]  index - g_arrtKeyConfigInfo ������ֵ.
  * @retval     ��������, ���ص�ֵ��������:
  *             @arg KEY_NOT_PRESS: û�а���
  *             @arg KEY_FRIST_PRESS: �״ΰ���
  *             @arg KEY_SHORT_HOLD_PRESS: �̰���������
  *             @arg KEY_SHORT_LOOSEN: �̰��ɿ�
  *             @arg KEY_LONG_HOLD_PRESS: ������������(������ģʽ��Ч)
  *             @arg KEY_LONG_LOOSEN: �����ɿ�(������ģʽ��Ч)
  */
uint8_t KEY_ReadAction(uint8_t index)
{
    uint8_t state;
    KEY_ConfigInfoType *ptKeyInfo = &g_arrtKeyConfigInfo[index];

    if (ptKeyInfo->actionInfo & KEY_FRIST_PRESS)
    {
        state = KEY_FRIST_PRESS;
        ptKeyInfo->actionInfo &= ~KEY_FRIST_PRESS;
    }
    else if (ptKeyInfo->actionInfo & KEY_SHORT_HOLD_PRESS)
    {
        state = KEY_SHORT_HOLD_PRESS;

        if ((ptKeyInfo->actionInfo & KEY_SHORT_LOOSEN) || (ptKeyInfo->actionInfo & KEY_LONG_LOOSEN) ||
                (ptKeyInfo->actionInfo & KEY_LONG_HOLD_PRESS))
        {
            ptKeyInfo->actionInfo &= ~KEY_SHORT_HOLD_PRESS;
        }
    }
    else if (ptKeyInfo->actionInfo & KEY_LONG_HOLD_PRESS)
    {
        state = KEY_LONG_HOLD_PRESS;

        if ((ptKeyInfo->actionInfo & KEY_SHORT_LOOSEN) || (ptKeyInfo->actionInfo & KEY_LONG_LOOSEN))
        {
            ptKeyInfo->actionInfo &= ~KEY_LONG_HOLD_PRESS;
        }
    }
    else if ((ptKeyInfo->actionInfo & KEY_SHORT_LOOSEN) || (ptKeyInfo->actionInfo & KEY_LONG_LOOSEN))
    {
        state = (ptKeyInfo->actionInfo & KEY_SHORT_LOOSEN) ? KEY_SHORT_LOOSEN : KEY_LONG_LOOSEN;
        ptKeyInfo->actionInfo = KEY_NOT_PRESS;
    }
    else
    {
        state = KEY_NOT_PRESS;
    }

    return state;
}

/**
  * @}
  */

/** @defgroup KEY����ĺ���������4 KEY ����/��λ������ز�������
 *  @brief    ����/��λ������ز�������
 *
 @verbatim
 ===============================================================================
                         ##### KEY ����/��λ������ز������� #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      �ı�ָ�������Ķ̰���Чʱ��.
  * @param[in]  index - g_arrtKeyConfigInfo ������ֵ.
  * @param[in]  emMode - ����ģʽ.
  * @retval     None.
  */
void KEY_ChangeMode(uint8_t index, KEY_ModeTypeDef  emMode)
{
    g_arrtKeyConfigInfo[index].emLongMode = emMode;
}

/**
  * @brief      �ı�ָ�������Ķ̰���Чʱ��.
  * @param[in]  index - g_arrtKeyConfigInfo ������ֵ.
  * @param[in]  time - ������Чʱ��, ��λ: 1ms.
  * @retval     None.
  */
void KEY_ChangeShortTime(uint8_t index, uint16_t time)
{
    g_arrtKeyConfigInfo[index].shortPressMaxTic = time;
}

/**
  * @brief      �ı�ָ�������ĳ�����Чʱ��.
  * @param[in]  index - g_arrtKeyConfigInfo ������ֵ.
  * @param[in]  time - ������Чʱ��, ��λ: 1ms.
  * @retval     None.
  */
void KEY_ChangeLongTime(uint8_t index, uint16_t time)
{
    g_arrtKeyConfigInfo[index].longPressMaxTic = time;
}

/**
  * @brief      ��λָ�������Ķ���.
  * @note       ��λ��, �����Ķ�����Ϣ�ᱻ���
  * @param[in]  index - g_arrtKeyConfigInfo ������ֵ.
  * @retval     None.
  */
void KEY_ResetAction(uint8_t index)
{
    g_arrtKeyConfigInfo[index].actionInfo = KEY_NOT_PRESS;
    g_arrtKeyConfigInfo[index].pressTic   = 0;
}

/**
  * @brief      ʹ��/��ֹ���а����Ķ���ʶ��.
  * @param[in]  index - g_arrtKeyConfigInfo ������ֵ.
  * @param[in]  enable - ʹ��(1)/��ֹ(0).
  * @retval     None.
  */
void KEY_EnableScan(uint8_t index, uint8_t enable)
{
	g_arrtKeyConfigInfo[index].funEnable = enable;
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

