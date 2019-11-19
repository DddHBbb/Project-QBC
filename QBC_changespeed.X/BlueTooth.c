//

#include "Gloablevariable.h"
#include "BlueTooth.h"



/*==============================================================================
 *     �������ƣ� ���������ж�
 *     ��ڲ�����������  01--������⣬03--���ս�����04--������
                        fc--������ԣ�fb--�˳����ԣ�04--������
 *              У����
 ==============================================================================*/
void BlueTooth(void)
{
    if(Flag_ReceivOver==1)
    {
        Flag_ReceivOver=0;

        if((R_Buff[2]==RE_START)&&(Flag_ready_fetch_tube==0)) //����ȡ��״̬
        {
            Flag_start_detect=1;              //set flag �����������
        }
        else if((R_Buff[2]==RE_END_CAMERA)&&(Flag_P3==1))  //3������λ��
        {
            Flag_end_camera=1;               //set flag ���ս�������
        }
        else if(R_Buff[2]==RE_FINISH)
        {
            Flag_finish_detect=1;            //set flag ��ɼ������
        }
        else if(R_Buff[2]==RE_STOP)   
        {
            Flag_stop=1;                     //set flag ���λ�ø�λ��ǿ�Ƴ��ܣ��ص�ȡ��λ�ã�  ����ֹ���
        }      
//        else if(R_Buff[2]==RE_IN_TEST)        
//        {
//            Flag_test=1;                     //set flag ��������������
//        }  
//        else if(R_Buff[2]==RE_EX_TEST)        
//        {
//            Flag_test=0;                     //clear flag �˳������������
//        }
    }
}

 
/*=======================================================================================
 *     �������ƣ� ��������
 *     ��ڲ�����������  01--׼���ÿ������գ�02--׼���ÿ���ȡ�ܣ�03--���Źرգ�04--�����쳣
 *              У����
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


void CheckSum(void)                  //����У���
{
    ;
}
