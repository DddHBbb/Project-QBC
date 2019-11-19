
#include "Work.h"
#include "Gloablevariable.h"

 

/*==============================================================================
 *     函数名称： 工作
==============================================================================*/
void Working(void)
{
    switch(To_position)                                  //要到达的位置
    {
        case 1:
            if(Flag_P1==1)                                //到达1号取管位置
            {
                Flag_ready_fetch_tube = 1;                //置位准备取管
                Flag_P1 = 0;
            }
            else
            {
                InitVar();                               //清
                Init_Tube();                             //电机先到5#，再初始到1号取管位置
            }
            break;             
            
        case 2:            
            if(Flag_P2==0)                               //第一次启动检测命令，由1号,先到2号位置顶管
            {
                if(JN_P2==0)                             //反转到2号
                {
                    if(Flag_first_move==0)
                    {
                        Flag_first_move = 1;
                        StepMotorEnable;                 //步进电机   
                        IEC0bits.T2IE = 1;  
                        StepMotorReversal;
                        systemtime = 0; 
                    }
                }    
                else                                     //到2号位置  //if(JN_P2==1)  
                {
                    Flag_first_move = 0;
                    StepMotorDisable;    
                    IEC0bits.T2IE = 0;     
                    Flag_P2 = 1;
                }    
            }
            else
            {
                To_position = 3;                        //要到达到3号位置
                Camera_count = 0;                       //清拍照次数
                Flag_ready_fetch_tube = 0;              //清1+8次拍照结束准备取管
                Flag_end_camera = 0;                    //清拍照结束命令
                Flag_first_P4 = 0;
                delaynms(5);  
            }
            break;
            
        case 3:      
            if(Flag_P3==0)                                 //3号位置拍照    
            {    
                if(JN_P3==0)                               //由4或2号，正转到3号
                {
                    if(Flag_first_move==0)
                    {
                        Flag_first_move = 1;
                        StepMotorEnable;                    //步进电机   
                        IEC0bits.T2IE = 1;  
                        StepMotorForeward;
                        systemtime = 0;
                    }
                }    
                else                                        //到3号位置 //if(JN_P3==1)  
                {        
                    Flag_first_move = 0;
                    StepMotorDisable;    
                    IEC0bits.T2IE = 0;     
                    Flag_P3 = 1;
                }    
            }   
            else                                          //3号位置拍照
            {
                if(Flag_first_P4 == 1)                    //4号位置已经拍照
                {
#ifdef test_aging 
                    delaynms(2500);                       //定义：测试，不和上位机通信，每个位置延时4ms*n
                    Flag_end_camera = 1;
#endif                     
                    Camera();
                }
                else
                {
                    To_position = 4;                     //要到达到4号位置
                }
            }
            break;  
            
        case 4:    
            if(Flag_P4==0)      
            {
                if(JN_P4==0)                                //由3号，反转到4号
                {
                    if(Flag_first_move==0)
                    {
                        Flag_first_move = 1;
                        StepMotorEnable;                    //步进电机   
                        IEC0bits.T2IE = 1;  
                        StepMotorReversal;
                        systemtime = 0;
                    }
                }    
                else                                        //到4号位置 //if(JN_P4==1)   
                {        
                    Flag_first_move = 0;
                    StepMotorDisable;    
                    IEC0bits.T2IE = 0;     
                    Flag_P4 = 1;
                }  
            }
            else
            {
                if(Flag_first_P4 == 0)                     //第一次到4号位置拍照
                {
#ifdef test_aging 
                    delaynms(2500);                        //定义：测试，不和上位机通信，每个位置延时4ms*n
                    Flag_end_camera = 1;
#endif                  
                    Camera();
                }
                else
                {
                    To_position = 3;                      //换向，要到达到3号位置
                }  
            }
            break;  

        default:
            break;            
    }
}


/*==============================================================================
 *     函数名称： 拍照
 ==============================================================================*/
void Camera(void)   
{
    static unsigned char  count_send_camera;        //拍照一次，发送计数，100ms发送一次，发送3次

    if(Flag_end_camera==1)                          //接收到上位机发来的拍照结束命令            
    {
        Flag_end_camera = 0;                        //拍照结束命令
        Flag_first_camera = 0;
        
//#ifndef test_aging         
//        BLUE_DISable;                               //关闭蓝色光源   test常亮
//        BLUE_OFF;
//#endif    
        
        Camera_count++;                             //拍照次数+1
        SystemTime1ms = 0;                          //用于每次拍照发送计时
       
        if((To_position == 4)&&(Flag_first_P4==0))  //第一次到4号位置拍照
        {
            Flag_first_P4 = 1;
            Flag_P3 = 0;                            //4、3号位置换向、拍照
            Flag_P4 = 0;   
            To_position = 3;                        //要到达到3号位置            
        }
        else if((To_position == 3)&&(Flag_first_P4==1))
        {
            Flag_P3 = 0;                            //4、3号位置换向、拍照
            Flag_P4 = 0;    
            To_position = 4;                       //要到达到4号位置
        }
            
        if(Camera_count>=9)                         //1+8次到
        {
            Flag_P1 = 0;
            To_position = 1;                        //要到达到5号位置,再到达1号位置
            
#ifndef test_aging         
            BLUE_DISable;                               //关闭蓝色光源   test常亮
           // BLUE_OFF;
#endif                
        }
    }
    else if(Flag_first_camera==0)                   //第一次移动进入拍照
    {
        Ready_Trans(TR_READY,TR_READY_CHK);         //移动到位，向上位机发送准备好可以拍照命令           
        Flag_first_camera = 1;
        BLUE_ENable;                                //打开蓝色光源
      //  BLUE_ON;

        SystemTime1ms = 0;
        count_send_camera = 0;
    }
    else if(count_send_camera < 3)                   //发送3次
    {
        if(SystemTime1ms > 100)                      //100ms, 未接收到上位机发来的拍照结束命令，继续发送
        {
            SystemTime1ms = 0;                       //用于每次拍照发送计时
            Ready_Trans(TR_READY,TR_READY_CHK);      //移动到位，向上位机发送准备好可以拍照命令
            count_send_camera ++;
        }
    }
           
    if(SystemTime1ms > 60000)                         //超过60秒
    {
        SystemTime1ms = 0;                            //用于每次拍照发送计时
        Flag_camera_error = 1;                        //0，拍照ok；1，拍照错误
    }
}


/*==============================================================================
 *     函数名称： 初始取放管位置，1号
 *     先正转到5号位置，然后反转到1号位置，取放管
 ==============================================================================*/
void Init_Tube(void)
{
    if(Flag_P5==0)
    {
        if(JN_P5==0)                          //不在5号位置，都要正转到5号 移动到位，平时为低，遮挡为高
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  

                StepMotorEnable;             //步进电机   
                IEC0bits.T2IE = 1;                     
                StepMotorForeward;
                
                systemtime = 0;
            }
        }
        else                                    //if(JN_P5==1)
        {
            Flag_first_move = 0;            
            StepMotorDisable;    
            IEC0bits.T2IE = 0;    
            Flag_P5 = 1;
        }
    }
    if(Flag_P5==1)                             //5号反转到1号取管位置
    {
        if(JN_P1==0)                           //反转到1号 移动到位，平时为低，遮挡为高
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  
                 
                StepMotorEnable;               //步进电机   
                IEC0bits.T2IE = 1;                     
                StepMotorReversal;
                
                systemtime = 0;
            }
        }
        else                                  //if(JN_P1==1)
        {
            Flag_first_move = 0;      
            StepMotorDisable;    
            IEC0bits.T2IE = 0;   
            Flag_P1 = 1;
            Flag_Init_Tube = 1;               //取管位置
            To_position = 2;                  //接收到启动检测命令后，要到达到2号位置
        } 
    }
}


#ifdef test_aging
/*==============================================================================
 *     函数名称： 错误
==============================================================================*/
void Error(void)  
{
//    static unsigned char  count_send_err = 0;                  //发送计数，1000ms发送一次，发送3次
    
    if((Flag_move_error==1)||(Flag_camera_error==1))  
    {
        InitVar();                                             //清启动检测、启动拍照,关灯等

        while(1)
//        while(Flag_stop==0)                                   //接收到上位机的停止命令
        {
            if(systemtime1 > 1000)
            {
                systemtime1 = 0;
                Ready_Trans(TR_ERR,TR_ERR_CHK);                //向上位机发送错误命令  ,3次
                SystemTime1ms = 0;
            }
            BlueTooth();                                      //接收上位机命令
        }
        
        Flag_ready_fetch_tube = 0;
        Flag_finish_detect = 0; 
        Flag_stop = 0;
    }
}
#endif


#ifndef test_aging
/*==============================================================================
 *     函数名称： 错误
==============================================================================*/
void Error(void)  
{
    static unsigned char  count_send_err = 0;              //发送计数，1000ms发送一次，发送3次
    
    if((Flag_move_error==1)||(Flag_camera_error==1))  
    {
        if(count_send_err < 3)
        {
            if(systemtime1 > 1000)                        //用于发送错误命令计时
            {
                systemtime1 = 0;
                Ready_Trans(TR_ERR,TR_ERR_CHK);           //向上位机发送错误命令  ,3次
                count_send_err++;
                SystemTime1ms = 0;
            }
        }
        else
        {
            count_send_err = 0;
            
            InitVar();                                   //清启动检测、启动拍照,关灯等
            Flag_ready_fetch_tube = 0;
            Flag_finish_detect = 0; 
 ////            Init_Tube();                                 //电机初始到1号取管位置,不调用，电机停在原来位置
        }
    }
}
#endif


#ifdef test_aging2_5  
/*==============================================================================
 *     函数名称： 测试老化2#~5#位
 *     先正转到5号位置，延时，然后反转到2号位置
 ==============================================================================*/
void Test_25(void)
{
    if(Flag_P5==0)
    {
        if(JN_P5==0)                          //不在5号位置，都要正转到5号 移动到位，平时为低，遮挡为高
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  

                StepMotorEnable;             //步进电机   
                IEC0bits.T2IE = 1;                     
                StepMotorForeward;
                
                systemtime = 0;
            }
        }
        else                                    //if(JN_P5==1)
        {
            Flag_first_move = 0;            
            StepMotorDisable;    
            IEC0bits.T2IE = 0;    
            Flag_P5 = 1;
            delaynms(250);                    //定义：测试，不和上位机通信，延时4ms*n
        }
    }
    if(Flag_P5==1)                             //5号反转到2号位置
    {
        if(JN_P2==0)                           //反转到2号 移动到位，平时为低，遮挡为高
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  
                 
                StepMotorEnable;               //步进电机   
                IEC0bits.T2IE = 1;                     
                StepMotorReversal;
                
                systemtime = 0;
            }
        }
        else                                  //if(JN_P2==1)
        {
            Flag_first_move = 0;      
            StepMotorDisable;    
            IEC0bits.T2IE = 0;   
//            Flag_P2 = 1;
//            To_position = 5;                  //接收到启动检测命令后，要到达到2号位置
            delaynms(250);                    //定义：测试，不和上位机通信，延时4ms*n
            Flag_P5 = 0;
            
        } 
    }
}
#endif
