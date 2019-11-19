
#include "Door.h"
#include "Gloablevariable.h"


/*==============================================================================
 *     函数名称： 仓门检测
 *     出口：     Flag_close_ok
 *     测试时，直接置Flag_open=1，不检测仓门，注释。
==============================================================================*/
void Door_check(void)
{
    Flag_open = 1;                              //test
        
//    if(OPEN_CLOSE==0)                                      //检测仓门是否关闭
    {
       if(Flag_open == 1)
       {
            Flag_close = 1;                                  //置仓门关闭
            Flag_open = 0;                                   //清仓门打开
       }
       
        if(Flag_close == 1)               //if(Flag_open == 1)
        {
            Flag_close_ok = 1;                             //打开，然后关上，置仓门关闭好    
        }
    }
//    else
//    {
//        Flag_open = 1;                                     //置仓门打开
//        Flag_close_ok = 0;   
//        Flag_close = 0;                                    //清仓门关闭
//    }

    if((Flag_close_ok==1)&&(Flag_Init_Tube==1))                  //仓门关闭好, 且取管位置
    {
        if((Flag_start_detect==0)&&(Flag_ready_fetch_tube==0))   //未启动检测, 不是取管状态
        {
            if(systemtime1 > 1000)
            {
                systemtime1 = 0;
                Ready_Trans(TR_CLOSE,TR_CLOSE_CHK);              //向上位机发送仓门关闭好命令
            }
#ifdef test_aging            
            systemtime = 0;
            delaynms(500);                                        //1s
            Flag_start_detect=1;                                  //set flag 启动检测命令
#endif
        }   
    }
}
