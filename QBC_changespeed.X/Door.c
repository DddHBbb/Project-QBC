
#include "Door.h"
#include "Gloablevariable.h"


/*==============================================================================
 *     �������ƣ� ���ż��
 *     ���ڣ�     Flag_close_ok
 *     ����ʱ��ֱ����Flag_open=1���������ţ�ע�͡�
==============================================================================*/
void Door_check(void)
{
    Flag_open = 1;                              //test
        
//    if(OPEN_CLOSE==0)                                      //�������Ƿ�ر�
    {
       if(Flag_open == 1)
       {
            Flag_close = 1;                                  //�ò��Źر�
            Flag_open = 0;                                   //����Ŵ�
       }
       
        if(Flag_close == 1)               //if(Flag_open == 1)
        {
            Flag_close_ok = 1;                             //�򿪣�Ȼ����ϣ��ò��Źرպ�    
        }
    }
//    else
//    {
//        Flag_open = 1;                                     //�ò��Ŵ�
//        Flag_close_ok = 0;   
//        Flag_close = 0;                                    //����Źر�
//    }

    if((Flag_close_ok==1)&&(Flag_Init_Tube==1))                  //���Źرպ�, ��ȡ��λ��
    {
        if((Flag_start_detect==0)&&(Flag_ready_fetch_tube==0))   //δ�������, ����ȡ��״̬
        {
            if(systemtime1 > 1000)
            {
                systemtime1 = 0;
                Ready_Trans(TR_CLOSE,TR_CLOSE_CHK);              //����λ�����Ͳ��Źرպ�����
            }
#ifdef test_aging            
            systemtime = 0;
            delaynms(500);                                        //1s
            Flag_start_detect=1;                                  //set flag �����������
#endif
        }   
    }
}
