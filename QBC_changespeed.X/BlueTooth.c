//

#include "Gloablevariable.h"
#include "BlueTooth.h"



/*==============================================================================
 *     函数名称： 接收命令判断
 *     入口参数：命令字  01--启动检测，03--拍照结束，04--检测完成
                        fc--进入调试，fb--退出调试，04--检测完成
 *              校验字
 ==============================================================================*/
void BlueTooth(void)
{
    if(Flag_ReceivOver==1)
    {
        Flag_ReceivOver=0;

        if((R_Buff[2]==RE_START)&&(Flag_ready_fetch_tube==0)) //不是取管状态
        {
            Flag_start_detect=1;              //set flag 启动检测命令
        }
        else if((R_Buff[2]==RE_END_CAMERA)&&(Flag_P3==1))  //3号拍照位置
        {
            Flag_end_camera=1;               //set flag 拍照结束命令
        }
        else if(R_Buff[2]==RE_FINISH)
        {
            Flag_finish_detect=1;            //set flag 完成检测命令
        }
        else if(R_Buff[2]==RE_STOP)   
        {
            Flag_stop=1;                     //set flag 电机位置复位及强制出管（回到取管位置）  （中止命令）
        }      
//        else if(R_Buff[2]==RE_IN_TEST)        
//        {
//            Flag_test=1;                     //set flag 进入电机调试命令
//        }  
//        else if(R_Buff[2]==RE_EX_TEST)        
//        {
//            Flag_test=0;                     //clear flag 退出电机调试命令
//        }
    }
}

 
/*=======================================================================================
 *     函数名称： 发送命令
 *     入口参数：命令字  01--准备好可以拍照，02--准备好可以取管，03--仓门关闭，04--工作异常
 *              校验字
 ========================================================================================*/
void Ready_Trans(unsigned char commd, unsigned char chksum)                    //send data to TX buffer
{
    Count_Tr=0;
    T_Buff[0]=0x55;
    T_Buff[1]=0xAA;
    T_Buff[2]=commd;
    T_Buff[3]=0x00;               
    T_Buff[4]=chksum;        
    
    if(Flag_camera_error==1)
    {
        T_Buff[3]=0x01;
    }
    
    if(Flag_move_error==1)
    {
        T_Buff[3]=0x80;
    }
    
    U1STAbits.UTXEN=1;                 //enable transmit, and generate TXInterrupt
}


void CheckSum(void)                  //计算校验和
{
    ;
}
