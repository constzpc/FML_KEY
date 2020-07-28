/**
  ******************************************************************************
  * @file    keyManage.c
  * @author  const_zpc
  * @date    2020-6-20
  * @brief   ���ļ��ṩ����ģ�������ܣ��Թ��� KEY ������������¹��ܣ�
  *           + ��ʼ������
  *           + ɨ��������
  *
  *
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "keyManage.h"
#include <string.h>

/** @addtogroup FunctionalModuleLayer
  * @brief      ����ģ���
  * @{
  */

/** @addtogroup FML_KEY
  * @brief      KEY����ģ��
  * @{
  */

/** @addtogroup KEY_MANAGE
  * @brief      KEY����
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/**
  * @brief TIME �����Ϣ�ṹ�嶨��
  */
typedef struct{
    uint16_t ucSupportCnt;              /*!< ע��Ķ�ʱ�ص���������Ŀ */
    
    KeyFun tCallFun[KEY_MAX_NUM];       /*!< ע��Ļص����� */
} KEY_ManageHandleType;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static KEY_ManageHandleType sg_tKeyManageHandle = {0};

/* Private function prototypes -----------------------------------------------*/
/* Private function ----------------------------------------------------------*/

/**
  * @brief      KEY���빦�ܳ�ʼ������.
  * @retval     None.
  */
void FML_KEY_ManageInit(void)
{
    FML_KEY_DriveInit();
    FML_KEY_ConfigInit();
    memset(&sg_tKeyManageHandle, 0, sizeof(sg_tKeyManageHandle));
}

/**
  * @brief      ע�ᰴ�������ص�����.
  * @note       ע��Ļص�����ִ��ʱ�䲻��̫��
  * @param[in]  emKeyName ָ������
  * @param[in]  pKeyFun �ص�����
  * @retval     0,�ɹ�; -1,ʧ��
  */
int FML_KEY_Register(KEY_NameTypeDef emKeyName, KeyFun pKeyFun)
{
    if (emKeyName < KEY_MAX_NUM)
    {
        sg_tKeyManageHandle.tCallFun[emKeyName] = pKeyFun;
        return 0;
    }

    return -1;    
}

/**
  * @brief      ע�����������ص�����.
  * @param[in]  emKeyName ָ������
  * @retval     None
  */
void FML_KEY_UnRegister(KEY_NameTypeDef emKeyName)
{
    if (emKeyName < KEY_MAX_NUM)
    {
        sg_tKeyManageHandle.tCallFun[emKeyName] = NULL;
    }
}

/**
  * @brief      KEY����ɨ������.
  * @note       10ms����
  * @retval     None.
  */
void FML_KEY_ScanTask(void)
{
    int i;
    KEY_NameTypeDef keyName = SCH_KEY_1;
    int keyState;
    KEY_ActionTypeDef keyAction;
    
    FML_KEY_ConfigHandle(10);
    
    for (i = 0; i < KEY_MAX_NUM; i++)
    {
        keyState = FML_KEY_ReadAction(keyName);
        
        if (FML_KEY_CONFIRM_ACTION(keyState, KEY_FRIST_PRESS))
        {
            keyAction = KEY_IS_FRIST_PRESS;
        }
        else if (FML_KEY_CONFIRM_ACTION(keyState, KEY_SHORT_HOLD_PRESS))
        {
            keyAction = KEY_IS_HOLD_PRESS;
        }
        else if (FML_KEY_CONFIRM_ACTION(keyState, KEY_SHORT_LOOSEN))
        {
            keyAction = KEY_IS_LOOSEN;
        }
        else if (FML_KEY_CONFIRM_ACTION(keyState, KEY_LONG_HOLD_PRESS))
        {
            keyAction = KEY_IS_LONG_HOLD_PRESS;
        }
        else if (FML_KEY_CONFIRM_ACTION(keyState, KEY_LONG_LOOSEN))
        {
            keyAction = KEY_IS_LONG_LOOSEN;
        }
        else
        {
            keyAction = KEY_IS_NOT_PRESS;
        }
        
        if (sg_tKeyManageHandle.tCallFun[i] != NULL)
        {
            sg_tKeyManageHandle.tCallFun[i](keyName, keyAction);
        }
        
        keyName++;
    }
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
