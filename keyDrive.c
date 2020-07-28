/**
  ******************************************************************************
  * @file    keyDrive.c
  * @author  const_zpc
  * @date    2020-6-20
  * @brief   ���ļ��ṩ����ģ�������ܣ��Թ��� KEY ����������������¹��ܣ�
  *           + KEY�����Ӳ������
  *           + ������Ϣ��ʼ������
  *           + ������Ϣ������
  *           + ��ȡ������������
  *           + ����/��λ������ز�������
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "keyDrive.h"
#include "MPC5604B_Extend.h"
#include "MPC5604B.h"
#include <string.h>

/** @addtogroup FunctionalModuleLayer
  * @brief      ����ģ���
  * @{
  */

/** @addtogroup FML_KEY
  * @brief      KEY ����ģ��
  * @{
  */

/** @addtogroup KEY_DRIVE
  * @brief      KEY ����
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/**
  * @brief ����������Ϣ�ṹ�嶨��
  */
typedef struct{
    KEY_ModeTypeDef emMode;                     /*!< ָ����ѡ��������ģʽ�Ľ���/ʹ��
                                                     This parameter can be any value of @ref KEY_ModeTypeDef */

    KEY_StateTypeDef emKeyState;                /*!< ���������صĵ�ƽ״̬ */
    
    uint8_t uiAction;                           /*!< ָ����ѡ�����Ķ�����Ϣ */

    uint16_t uiPressTic;                        /*!< ָ����ѡ�����İ����ۼ�ʱ��, �ò�����λΪ1ms,��ֵ��ֵΪ0 */

    uint16_t uiShortPressTime;                  /*!< ָ����ѡ�����Ķ̰���Чʱ��, �ò�����λΪ1ms */

    uint16_t uiLongPressTime;                   /*!< ָ����ѡ�����ĳ�����Чʱ��(����ģʽ��ֹʱ��Ч), �ò�����λΪ1ms */
} KEY_ConfigInfoType;

/**
  * @brief ���������Ϣ�ṹ�嶨��
  */
typedef struct{
    KEY_ConfigInfoType tKeysConfigInfo[KEY_MAX_NUM];        /*!< ���а���������Ϣָ�� */
} KEY_DriveHandleType;

/* Private define ------------------------------------------------------------*/

/** ����ͨ�����ö��� */
#define KEY_SHORT_TIME     20
#define KEY_LONG_TIME      1000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static KEY_DriveHandleType sg_tKeyDrvHandle = {0};

/* Private function prototypes -----------------------------------------------*/
static void SetOutputPin(PORT_PadTypeDef port);
static void SacnKeyDriveState(void);
static void OneKeyShortModeHandle(KEY_ConfigInfoType * const ptKeyInfo, uint8_t callTime);
static void OneKeyLongModeHandle(KEY_ConfigInfoType * const ptKeyInfo, uint8_t callTime);

/* Private function ----------------------------------------------------------*/

/** @defgroup KEY �����������1 KEY �����Ӳ������
 *  @brief    KEY �����Ӳ������
 *
 @verbatim
 ===============================================================================
                 ##### KEY �����Ӳ������  #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      KEY Ӳ�������ĳ�ʼ��.
  * @retval     -1,����; 0,�ɹ�.
  */
void FML_KEY_DriveInit(void)
{
    SIU.PCR[PORT_C5].R = 0x0102;
    SIU.PCR[PORT_C2].R = 0x0102;
    SIU.PCR[PORT_C3].R = 0x0102;
    SIU.PCR[PORT_C4].R = 0x0102;
    SIU.PCR[PORT_A1].R = 0x0203;
    SIU.PCR[PORT_A2].R = 0x0203;
    SIU.PCR[PORT_A3].R = 0x0203;
    SIU.PCR[PORT_A4].R = 0x0203;
}

/**
  * @brief      ���󰴼���ָ��IO������.
  * @param[in]  port ��Ҫ���ߵ� IO ��.
  * @retval     None.
  */
static void SetOutputPin(PORT_PadTypeDef port)
{
    SIU.GPDO[PORT_A1].B.PDO = 0;
    SIU.GPDO[PORT_A2].B.PDO = 0;
    SIU.GPDO[PORT_A3].B.PDO = 0;
    SIU.GPDO[PORT_A4].B.PDO = 0;
    
    SIU.GPDO[port].B.PDO = 1;
}

/**
  * @brief      ɨ�����а����Ŀ���״̬.
  * @retval     None.
  */
static void SacnKeyDriveState(void)
{
    uint8_t i;
    KEY_ConfigInfoType *ptKeyInfo = sg_tKeyDrvHandle.tKeysConfigInfo;
    PORT_PadTypeDef emPort[] = {PORT_A1, PORT_A2, PORT_A3, PORT_A4};
    
    for (i = 0; i < KEY_MAX_NUM; i++)
    {
        ptKeyInfo[i].emKeyState = KEY_IS_OFF;
    }
    
    for (i = 0; i < 4; i++)
    {
        SetOutputPin(emPort[i]);
        
        if (SIU.GPDI[PORT_C5].B.PDI)
        {
            ptKeyInfo[SCH_KEY_1 + i * 4].emKeyState = KEY_IS_ON;
        }
        if (SIU.GPDI[PORT_C2].B.PDI)
        {
            ptKeyInfo[SCH_KEY_2 + i * 4].emKeyState = KEY_IS_ON;
        }
        if (SIU.GPDI[PORT_C3].B.PDI)
        {
            ptKeyInfo[SCH_KEY_3 + i * 4].emKeyState = KEY_IS_ON;
        }
        if (SIU.GPDI[PORT_C4].B.PDI)
        {
            ptKeyInfo[SCH_KEY_4 + i * 4].emKeyState = KEY_IS_ON;
        }
    }
}

/**
  * @}
  */

/** @defgroup KEY �����������2 KEY ������Ϣ����
 *  @brief    KEY ������Ϣ����
 *
 @verbatim
 ===============================================================================
                 ##### KEY ������Ϣ���� #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      ����������Ϣ���г�ʼ��.
  * @param[in]  pInfo - ���а�����������Ϣ, ָ��"KEY_ConfigInfoType"�ṹ�����͵�ָ��.
  * @param[in]  num -   ���ú�İ�����Ŀ.
  * @retval     None.
  */
void FML_KEY_ConfigInit(void)
{
    uint8_t i;
    
    memset(&sg_tKeyDrvHandle, 0, sizeof(sg_tKeyDrvHandle));
    
    for (i = 0; i < KEY_MAX_NUM; i++)
    {
        sg_tKeyDrvHandle.tKeysConfigInfo[i].uiLongPressTime = KEY_LONG_TIME;
        sg_tKeyDrvHandle.tKeysConfigInfo[i].uiShortPressTime = KEY_SHORT_TIME;
        sg_tKeyDrvHandle.tKeysConfigInfo[i].emMode = KEY_NORMAL_MODE;
        sg_tKeyDrvHandle.tKeysConfigInfo[i].uiPressTic = 0;
        sg_tKeyDrvHandle.tKeysConfigInfo[i].uiAction = KEY_NOT_PRESS;
        sg_tKeyDrvHandle.tKeysConfigInfo[i].emKeyState = KEY_IS_OFF;
    }
}

/**
  * @brief      ��ָ���̰�ģʽ�İ�����Ϣ���д���.
  * @param[in][out]  ptKeyInfo - ָ��"KEY_OperaInfoType"�ṹ�����͵�ָ��.
  * @param[in]  callTime - �ú�����������ʱ��, ��λms.
  * @retval     None.
  */
static void OneKeyShortModeHandle(KEY_ConfigInfoType * const ptKeyInfo, uint8_t callTime)
{
    if (ptKeyInfo->uiPressTic < ptKeyInfo->uiShortPressTime)
    {
        if (KEY_IS_ON == ptKeyInfo->emKeyState)
        {
            ptKeyInfo->uiPressTic += callTime;
        }
        else
        {
            ptKeyInfo->uiPressTic = 0;                        /* δ�ﵽ�̰�ʱ�� */
        }
    }
    else
    {
        if (KEY_NOT_PRESS == ptKeyInfo->uiAction)
        {
            ptKeyInfo->uiAction |= KEY_FRIST_PRESS;
            ptKeyInfo->uiAction |= KEY_SHORT_HOLD_PRESS;
        }
        else
        {
            if (KEY_IS_ON == ptKeyInfo->emKeyState)
            {
                ptKeyInfo->uiAction |= KEY_SHORT_HOLD_PRESS;
            }
            else
            {
                ptKeyInfo->uiPressTic = 0;
                ptKeyInfo->uiAction |= KEY_SHORT_LOOSEN;
            }
        }
    }
}

/**
  * @brief      ��ָ������ģʽ�İ�����Ϣ���д���.
  * @param[in][out]  ptKeyInfo - ָ��"KEY_OperaInfoType"�ṹ�����͵�ָ��.
  * @param[in]  callTime - �ú�����������ʱ��, ��λms.
  * @retval     None.
  */
static void OneKeyLongModeHandle(KEY_ConfigInfoType * const ptKeyInfo, uint8_t callTime)
{
    if (ptKeyInfo->uiPressTic < ptKeyInfo->uiShortPressTime)
    {
        if (KEY_IS_ON == ptKeyInfo->emKeyState)
        {
            ptKeyInfo->uiPressTic += callTime;
        }
        else
        {
            ptKeyInfo->uiPressTic = 0;                        /* δ����̰�ʱ�� */
        }
    }
    else
    {
        if (KEY_NOT_PRESS == ptKeyInfo->uiAction)
        {
            ptKeyInfo->uiAction |= KEY_FRIST_PRESS;
            ptKeyInfo->uiAction |= KEY_SHORT_HOLD_PRESS;
        }
        else
        {
            if (ptKeyInfo->uiPressTic < ptKeyInfo->uiLongPressTime)
            {
                if (KEY_IS_ON == ptKeyInfo->emKeyState)
                {
                    ptKeyInfo->uiPressTic += callTime;
                }
                else
                {
                    ptKeyInfo->uiPressTic = 0;                /* δ���㳤��ʱ�� */
                    ptKeyInfo->uiAction |= KEY_SHORT_LOOSEN;
                }
            }
            else
            {
                if (KEY_IS_ON == ptKeyInfo->emKeyState)
                {
                    ptKeyInfo->uiAction |= KEY_LONG_HOLD_PRESS;
                }
                else
                {
                    ptKeyInfo->uiPressTic = 0;
                    ptKeyInfo->uiAction |= KEY_LONG_LOOSEN;
                }
            }
        }
    }
}

/**
  * @brief      ��һ������ָ���İ�����Ϣ���д���.
  * @param[in]  callTime - �ú�����������ʱ��, ��λms.
  * @retval     None.
  */
void FML_KEY_ConfigHandle(uint8_t callTime)
{
    uint8_t i;
    KEY_ConfigInfoType *ptKeyInfo = sg_tKeyDrvHandle.tKeysConfigInfo;
    void (*pKeyModeHandle[2])(KEY_ConfigInfoType*, uint8_t) = {OneKeyShortModeHandle, OneKeyLongModeHandle};

    SacnKeyDriveState();
    
    for (i = 0; i < KEY_MAX_NUM; i++)
    {
        pKeyModeHandle[ptKeyInfo[i].emMode](&ptKeyInfo[i], callTime);
    }
}

/**
  * @}
  */

/** @defgroup KEY �����������3 KEY ��������/��ȡ
 *  @brief    KEY ��������/��ȡ
 *
 @verbatim
 ===============================================================================
                         ##### KEY ��������/��ȡ #####
 ===============================================================================

 @endverbatim
  * @{
  */

/**
  * @brief      ���ָ�������Ƿ���ڶ���.
  * @param[in]  emKeyName ָ������
  * @retval     ��������, ���ص�ֵ��������:
  * 			@arg -1,����
  *             @arg 0,�޶���
  *             @arg 1,�ж���
  */
int FML_KEY_CheckIsAction(KEY_NameTypeDef emKeyName)
{
    if (emKeyName < KEY_MAX_NUM)
    {
        if (sg_tKeyDrvHandle.tKeysConfigInfo[emKeyName].uiAction != 0)
        {
            return 1;
        }

        return 0;
    }
    
    return -1;
}

/**
  * @brief      ��ȡָ�������Ķ�����Ϣ.
  * @note       1.���̰�ģʽ�°������һ�ζ���, �����º��ɿ�, ���������˳��ÿ�ε��øú�������֮ǰ�Ķ�����Ϣ��
  *                 �״ΰ��� -> �̰��������� -> �̰��ɿ�(Ҳ�ʺϳ���ģʽ�����һ�ζ̰�����).
  *             2.������ģʽ�°������һ�ζ���, �����´ﵽ����ʱ����ɿ�, ���������˳��ÿ�ε��øú�������֮ǰ�Ķ�����Ϣ��
  *                 �״ΰ��� -> �̰��������� -> ������������ -> �����ɿ�.
  *             3.����"��������"״̬�����ù�����û���ɿ�,��һֱ����
  *             4.ÿ�ε��øú�����ȡ����ʹ�ú궨������"KEY_CONFIRM_ACTION(keyAction, Action)"����Ƿ���϶�����Ϣ
  * @param[in]  emKeyName ָ������
  * @retval     ��������, ���ص�ֵ��������:
  *             @arg -1,����
  *             @arg KEY_NOT_PRESS,û�а���
  *             @arg KEY_FRIST_PRESS,�״ΰ���
  *             @arg KEY_SHORT_HOLD_PRESS,�̰���������
  *             @arg KEY_SHORT_LOOSEN,�̰��ɿ�
  *             @arg KEY_LONG_HOLD_PRESS,������������(������ģʽ��Ч)
  *             @arg KEY_LONG_LOOSEN,�����ɿ�(������ģʽ��Ч)
  */
int FML_KEY_ReadAction(KEY_NameTypeDef emKeyName)
{
    uint8_t state;
    KEY_ConfigInfoType *ptKeyInfo = &sg_tKeyDrvHandle.tKeysConfigInfo[emKeyName];

    if (emKeyName < KEY_MAX_NUM)
    {
        if (ptKeyInfo->uiAction & KEY_FRIST_PRESS)
        {
            state = KEY_FRIST_PRESS;
            ptKeyInfo->uiAction &= ~KEY_FRIST_PRESS;
        }
        else if (ptKeyInfo->uiAction & KEY_SHORT_HOLD_PRESS)
        {
            state = KEY_SHORT_HOLD_PRESS;

            if ((ptKeyInfo->uiAction & KEY_SHORT_LOOSEN) || (ptKeyInfo->uiAction & KEY_LONG_LOOSEN) ||
                            (ptKeyInfo->uiAction & KEY_LONG_HOLD_PRESS))
            {
                    ptKeyInfo->uiAction &= ~KEY_SHORT_HOLD_PRESS;
            }
        }
        else if (ptKeyInfo->uiAction & KEY_LONG_HOLD_PRESS)
        {
            state = KEY_LONG_HOLD_PRESS;

            if ((ptKeyInfo->uiAction & KEY_SHORT_LOOSEN) || (ptKeyInfo->uiAction & KEY_LONG_LOOSEN))
            {
                    ptKeyInfo->uiAction &= ~KEY_LONG_HOLD_PRESS;
            }
        }
        else if ((ptKeyInfo->uiAction & KEY_SHORT_LOOSEN) || (ptKeyInfo->uiAction & KEY_LONG_LOOSEN))
        {
            state = (ptKeyInfo->uiAction & KEY_SHORT_LOOSEN) ? KEY_SHORT_LOOSEN : KEY_LONG_LOOSEN;
            ptKeyInfo->uiAction = KEY_NOT_PRESS;
        }
        else
        {
            state = KEY_NOT_PRESS;
        }
        
        return state;
    }

    return -1;
}

/**
  * @brief      �ı�ָ������ģʽ.
  * @param[in]  emKeyName ָ������
  * @param[in]  emMode - ����ģʽ.
  * @retval     -1,����; 0,�ɹ�.
  */
int FML_KEY_ChangeMode(KEY_NameTypeDef emKeyName, KEY_ModeTypeDef  emMode)
{
    if (emKeyName < KEY_MAX_NUM)
    {
        sg_tKeyDrvHandle.tKeysConfigInfo[emKeyName].emMode = emMode;
        return 0;
    }
    
    return -1;
}

/**
  * @brief      �ı�ָ����������Чʱ��.
  *             longTime ����֧�ֳ���ģʽ����Ч
  * @param[in]  emKeyName ָ������
  * @param[in]  shortTime �̰���Чʱ��, ��λ: 1ms.
  * @param[in]  longTime  ������Чʱ��, ��λ: 1ms.
  * @retval     -1,����; 0,�ɹ�.
  */
int FML_KEY_ChangeTime(KEY_NameTypeDef emKeyName, uint16_t shortTime, uint16_t longTime)
{
    if (emKeyName < KEY_MAX_NUM)
    {
        sg_tKeyDrvHandle.tKeysConfigInfo[emKeyName].uiShortPressTime = shortTime;
        sg_tKeyDrvHandle.tKeysConfigInfo[emKeyName].uiLongPressTime = longTime;
        return 0;
    }
    
    return -1;
}

/**
  * @brief      ��λָ�������Ķ���.
  *         	��λ��, �����Ķ�����Ϣ�ᱻ���
  * @param[in]  emKeyName ָ������.
  * @retval     -1,����; 0,�ɹ�.
  */
int FML_KEY_ResetAction(KEY_NameTypeDef emKeyName)
{
    if (emKeyName < KEY_MAX_NUM)
    {
        sg_tKeyDrvHandle.tKeysConfigInfo[emKeyName].uiAction = KEY_NOT_PRESS;
        sg_tKeyDrvHandle.tKeysConfigInfo[emKeyName].uiPressTic   = 0;
        return 0;
    }
    
    return -1;
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
