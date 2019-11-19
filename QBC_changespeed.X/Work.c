
#include "Work.h"
#include "Gloablevariable.h"

 

/*==============================================================================
 *     �������ƣ� ����
==============================================================================*/
void Working(void)
{
    switch(To_position)                                  //Ҫ�����λ��
    {
        case 1:
            if(Flag_P1==1)                                //����1��ȡ��λ��
            {
                Flag_ready_fetch_tube = 1;                //��λ׼��ȡ��
                Flag_P1 = 0;
            }
            else
            {
                InitVar();                               //��
                Init_Tube();                             //����ȵ�5#���ٳ�ʼ��1��ȡ��λ��
            }
            break;             
            
        case 2:            
            if(Flag_P2==0)                               //��һ��������������1��,�ȵ�2��λ�ö���
            {
                if(JN_P2==0)                             //��ת��2��
                {
                    if(Flag_first_move==0)
                    {
                        Flag_first_move = 1;
                        StepMotorEnable;                 //�������   
                        IEC0bits.T2IE = 1;  
                        StepMotorReversal;
                        systemtime = 0; 
                    }
                }    
                else                                     //��2��λ��  //if(JN_P2==1)  
                {
                    Flag_first_move = 0;
                    StepMotorDisable;    
                    IEC0bits.T2IE = 0;     
                    Flag_P2 = 1;
                }    
            }
            else
            {
                To_position = 3;                        //Ҫ���ﵽ3��λ��
                Camera_count = 0;                       //�����մ���
                Flag_ready_fetch_tube = 0;              //��1+8�����ս���׼��ȡ��
                Flag_end_camera = 0;                    //�����ս�������
                Flag_first_P4 = 0;
                delaynms(5);  
            }
            break;
            
        case 3:      
            if(Flag_P3==0)                                 //3��λ������    
            {    
                if(JN_P3==0)                               //��4��2�ţ���ת��3��
                {
                    if(Flag_first_move==0)
                    {
                        Flag_first_move = 1;
                        StepMotorEnable;                    //�������   
                        IEC0bits.T2IE = 1;  
                        StepMotorForeward;
                        systemtime = 0;
                    }
                }    
                else                                        //��3��λ�� //if(JN_P3==1)  
                {        
                    Flag_first_move = 0;
                    StepMotorDisable;    
                    IEC0bits.T2IE = 0;     
                    Flag_P3 = 1;
                }    
            }   
            else                                          //3��λ������
            {
                if(Flag_first_P4 == 1)                    //4��λ���Ѿ�����
                {
#ifdef test_aging 
                    delaynms(2500);                       //���壺���ԣ�������λ��ͨ�ţ�ÿ��λ����ʱ4ms*n
                    Flag_end_camera = 1;
#endif                     
                    Camera();
                }
                else
                {
                    To_position = 4;                     //Ҫ���ﵽ4��λ��
                }
            }
            break;  
            
        case 4:    
            if(Flag_P4==0)      
            {
                if(JN_P4==0)                                //��3�ţ���ת��4��
                {
                    if(Flag_first_move==0)
                    {
                        Flag_first_move = 1;
                        StepMotorEnable;                    //�������   
                        IEC0bits.T2IE = 1;  
                        StepMotorReversal;
                        systemtime = 0;
                    }
                }    
                else                                        //��4��λ�� //if(JN_P4==1)   
                {        
                    Flag_first_move = 0;
                    StepMotorDisable;    
                    IEC0bits.T2IE = 0;     
                    Flag_P4 = 1;
                }  
            }
            else
            {
                if(Flag_first_P4 == 0)                     //��һ�ε�4��λ������
                {
#ifdef test_aging 
                    delaynms(2500);                        //���壺���ԣ�������λ��ͨ�ţ�ÿ��λ����ʱ4ms*n
                    Flag_end_camera = 1;
#endif                  
                    Camera();
                }
                else
                {
                    To_position = 3;                      //����Ҫ���ﵽ3��λ��
                }  
            }
            break;  

        default:
            break;            
    }
}


/*==============================================================================
 *     �������ƣ� ����
 ==============================================================================*/
void Camera(void)   
{
    static unsigned char  count_send_camera;        //����һ�Σ����ͼ�����100ms����һ�Σ�����3��

    if(Flag_end_camera==1)                          //���յ���λ�����������ս�������            
    {
        Flag_end_camera = 0;                        //���ս�������
        Flag_first_camera = 0;
        
//#ifndef test_aging         
//        BLUE_DISable;                               //�ر���ɫ��Դ   test����
//        BLUE_OFF;
//#endif    
        
        Camera_count++;                             //���մ���+1
        SystemTime1ms = 0;                          //����ÿ�����շ��ͼ�ʱ
       
        if((To_position == 4)&&(Flag_first_P4==0))  //��һ�ε�4��λ������
        {
            Flag_first_P4 = 1;
            Flag_P3 = 0;                            //4��3��λ�û�������
            Flag_P4 = 0;   
            To_position = 3;                        //Ҫ���ﵽ3��λ��            
        }
        else if((To_position == 3)&&(Flag_first_P4==1))
        {
            Flag_P3 = 0;                            //4��3��λ�û�������
            Flag_P4 = 0;    
            To_position = 4;                       //Ҫ���ﵽ4��λ��
        }
            
        if(Camera_count>=9)                         //1+8�ε�
        {
            Flag_P1 = 0;
            To_position = 1;                        //Ҫ���ﵽ5��λ��,�ٵ���1��λ��
            
#ifndef test_aging         
            BLUE_DISable;                               //�ر���ɫ��Դ   test����
           // BLUE_OFF;
#endif                
        }
    }
    else if(Flag_first_camera==0)                   //��һ���ƶ���������
    {
        Ready_Trans(TR_READY,TR_READY_CHK);         //�ƶ���λ������λ������׼���ÿ�����������           
        Flag_first_camera = 1;
        BLUE_ENable;                                //����ɫ��Դ
      //  BLUE_ON;

        SystemTime1ms = 0;
        count_send_camera = 0;
    }
    else if(count_send_camera < 3)                   //����3��
    {
        if(SystemTime1ms > 100)                      //100ms, δ���յ���λ�����������ս��������������
        {
            SystemTime1ms = 0;                       //����ÿ�����շ��ͼ�ʱ
            Ready_Trans(TR_READY,TR_READY_CHK);      //�ƶ���λ������λ������׼���ÿ�����������
            count_send_camera ++;
        }
    }
           
    if(SystemTime1ms > 60000)                         //����60��
    {
        SystemTime1ms = 0;                            //����ÿ�����շ��ͼ�ʱ
        Flag_camera_error = 1;                        //0������ok��1�����մ���
    }
}


/*==============================================================================
 *     �������ƣ� ��ʼȡ�Ź�λ�ã�1��
 *     ����ת��5��λ�ã�Ȼ��ת��1��λ�ã�ȡ�Ź�
 ==============================================================================*/
void Init_Tube(void)
{
    if(Flag_P5==0)
    {
        if(JN_P5==0)                          //����5��λ�ã���Ҫ��ת��5�� �ƶ���λ��ƽʱΪ�ͣ��ڵ�Ϊ��
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  

                StepMotorEnable;             //�������   
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
    if(Flag_P5==1)                             //5�ŷ�ת��1��ȡ��λ��
    {
        if(JN_P1==0)                           //��ת��1�� �ƶ���λ��ƽʱΪ�ͣ��ڵ�Ϊ��
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  
                 
                StepMotorEnable;               //�������   
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
            Flag_Init_Tube = 1;               //ȡ��λ��
            To_position = 2;                  //���յ�������������Ҫ���ﵽ2��λ��
        } 
    }
}


#ifdef test_aging
/*==============================================================================
 *     �������ƣ� ����
==============================================================================*/
void Error(void)  
{
//    static unsigned char  count_send_err = 0;                  //���ͼ�����1000ms����һ�Σ�����3��
    
    if((Flag_move_error==1)||(Flag_camera_error==1))  
    {
        InitVar();                                             //��������⡢��������,�صƵ�

        while(1)
//        while(Flag_stop==0)                                   //���յ���λ����ֹͣ����
        {
            if(systemtime1 > 1000)
            {
                systemtime1 = 0;
                Ready_Trans(TR_ERR,TR_ERR_CHK);                //����λ�����ʹ�������  ,3��
                SystemTime1ms = 0;
            }
            BlueTooth();                                      //������λ������
        }
        
        Flag_ready_fetch_tube = 0;
        Flag_finish_detect = 0; 
        Flag_stop = 0;
    }
}
#endif


#ifndef test_aging
/*==============================================================================
 *     �������ƣ� ����
==============================================================================*/
void Error(void)  
{
    static unsigned char  count_send_err = 0;              //���ͼ�����1000ms����һ�Σ�����3��
    
    if((Flag_move_error==1)||(Flag_camera_error==1))  
    {
        if(count_send_err < 3)
        {
            if(systemtime1 > 1000)                        //���ڷ��ʹ��������ʱ
            {
                systemtime1 = 0;
                Ready_Trans(TR_ERR,TR_ERR_CHK);           //����λ�����ʹ�������  ,3��
                count_send_err++;
                SystemTime1ms = 0;
            }
        }
        else
        {
            count_send_err = 0;
            
            InitVar();                                   //��������⡢��������,�صƵ�
            Flag_ready_fetch_tube = 0;
            Flag_finish_detect = 0; 
 ////            Init_Tube();                                 //�����ʼ��1��ȡ��λ��,�����ã����ͣ��ԭ��λ��
        }
    }
}
#endif


#ifdef test_aging2_5  
/*==============================================================================
 *     �������ƣ� �����ϻ�2#~5#λ
 *     ����ת��5��λ�ã���ʱ��Ȼ��ת��2��λ��
 ==============================================================================*/
void Test_25(void)
{
    if(Flag_P5==0)
    {
        if(JN_P5==0)                          //����5��λ�ã���Ҫ��ת��5�� �ƶ���λ��ƽʱΪ�ͣ��ڵ�Ϊ��
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  

                StepMotorEnable;             //�������   
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
            delaynms(250);                    //���壺���ԣ�������λ��ͨ�ţ���ʱ4ms*n
        }
    }
    if(Flag_P5==1)                             //5�ŷ�ת��2��λ��
    {
        if(JN_P2==0)                           //��ת��2�� �ƶ���λ��ƽʱΪ�ͣ��ڵ�Ϊ��
        {
            if(Flag_first_move==0)
            {
                Flag_first_move = 1;  
                 
                StepMotorEnable;               //�������   
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
//            To_position = 5;                  //���յ�������������Ҫ���ﵽ2��λ��
            delaynms(250);                    //���壺���ԣ�������λ��ͨ�ţ���ʱ4ms*n
            Flag_P5 = 0;
            
        } 
    }
}
#endif
