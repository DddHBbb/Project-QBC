#include "uart.h"
#include "Gloablevariable.h"
 extern unsigned char CM;
 extern unsigned char  FLAG_POS_Reset_triger;                   //电机复位触发标志位
 unsigned char  FLAG_AD_TRIGER;                                 //AD触发标志位，用于AD中断检测当前AD值，判断复位时应前进后退停止
 extern unsigned char  FLAG_POS_Reset; 
 extern unsigned char  More,Less;
 extern unsigned int Count_Re; 
void OutChar(unsigned char n)
{ 
    U1TXREG = n;
    while(U1STAbits.TRMT == 0);   
}

unsigned char  FLAG_PHOTO_END;
void uart_from_6755()
{
    while(1)                                            //等待串口接受数据
    {
      if(Flag_ReceivOver==1)  break;
    }
    if(Flag_ReceivOver==1)
    {
     Flag_ReceivOver=0;
     if((R_Buff[0]==0xAA)&&(R_Buff[1]==0x55))    
    {
       if(R_Buff[4]==0x56)   //启动检测
       {
           R_Buff[0]=0;R_Buff[1]=0; R_Buff[2]=0;R_Buff[3]=0;R_Buff[4]=0;
           Count_Re=0;
           FLAG_AD_TRIGER=1;
           while(1)
           {
             if(FLAG_POS_Reset_triger!=0)  break;
                if(FLAG_POS_Reset==1)
                   {
                     FLAG_POS_Reset=0;
                     break;
                     }
            } 
           while(1)
           {
            motor_move_12();
            motor_move_23();
            if(FLAG_PHOTO_END==2)
               {
                 FLAG_PHOTO_END=0;
                 break;
               }
             motor_move_34(2);
                if(FLAG_PHOTO_END==2)
               {
                 FLAG_PHOTO_END=0;
                 break;
               }  
             motor_paizhao_7times();  
            break;
           }

        }
        if(R_Buff[4]==0x58)   //拍照结束
       {
           R_Buff[0]=0;R_Buff[1]=0; R_Buff[2]=0;R_Buff[3]=0;R_Buff[4]=0;
           FLAG_PHOTO_END=1;
        } 
        if(R_Buff[4]==0x59)   //完成一次全流程检测，回到初始位置
       {
           R_Buff[0]=0;R_Buff[1]=0; R_Buff[2]=0;R_Buff[3]=0;R_Buff[4]=0;
           FLAG_PHOTO_END=2;
          // motor_reset_5();       
        } 
        if(R_Buff[4]==0x60)   //停止拍照，强制复位到初始位置
       {
           R_Buff[0]=0;R_Buff[1]=0; R_Buff[2]=0;R_Buff[3]=0;R_Buff[4]=0;
           FLAG_PHOTO_END=2;
         //  motor_reset_5();
        } 
    }
     
    }
}

void uart_from_6755move()
{
    while(1)                                            //等待串口接受数据
    {
      if(Flag_ReceivOver==1)  break;
    }
    if(Flag_ReceivOver==1)
    {
     Flag_ReceivOver=0;
     if((R_Buff[0]==0xAA)&&(R_Buff[1]==0x55))    
    {
        if(R_Buff[4]==0x58)   //拍照结束
       {
           R_Buff[0]=0;R_Buff[1]=0; R_Buff[2]=0;R_Buff[3]=0;R_Buff[4]=0;
           FLAG_PHOTO_END=1;
        } 
        if(R_Buff[4]==0x59)   //完成一次全流程检测，回到初始位置
       {
           R_Buff[0]=0;R_Buff[1]=0; R_Buff[2]=0;R_Buff[3]=0;R_Buff[4]=0;
           FLAG_PHOTO_END=2;
           
        } 
        if(R_Buff[4]==0x60)   //停止拍照，强制复位到初始位置
       {
           R_Buff[0]=0;R_Buff[1]=0; R_Buff[2]=0;R_Buff[3]=0;R_Buff[4]=0;
           FLAG_PHOTO_END=2;
        } 
    }
     
    }
}



void uart_to_6755_paizhao(unsigned char num)    //拍照命令，num为变量，1--边界拍照   2-9--三分层8次拍照
{
    OutChar(0x55);
    delaynms(1);  
    OutChar(0xaa);
    delaynms(1);  
    OutChar(0x01);
    delaynms(1);  
    OutChar(num);
    delaynms(1);  
    OutChar(0xab);
    delaynms(1);  
}

void uart_to_6755_quguan()    //取管命令
{
    OutChar(0x55);
    delaynms(1);  
    OutChar(0xaa);
    delaynms(1);  
    OutChar(0x02);
    delaynms(1);  
    OutChar(0x00);
    delaynms(1);  
    OutChar(0xac);
    delaynms(1);  
}

void uart_to_6755_cmguanbi()    //仓门关闭命令
{
    OutChar(0x55);
    delaynms(1);  
    OutChar(0xaa);
    delaynms(1);  
    OutChar(0x03);
    delaynms(1);  
    OutChar(0x00);
    delaynms(1);  
    OutChar(0xad);
    delaynms(1);  
}


void uart_to_6755_cmyichang()    //仓门异常命令
{
    OutChar(0x55);
    delaynms(1);  
    OutChar(0xaa);
    delaynms(1);  
    OutChar(0x03);
    delaynms(1);  
    OutChar(0x00);
    delaynms(1);  
    OutChar(0xa0);
    delaynms(1);  
}

void uart_to_6755_errorpz()    //错误,拍照超时
{
    OutChar(0x55);
    delaynms(1);  
    OutChar(0xaa);
    delaynms(1);  
    OutChar(0x04);
    delaynms(1);  
    OutChar(0x01);
    delaynms(1);  
    OutChar(0xae);
    delaynms(1);  
}
void uart_to_6755_errormotor()    //错误,电机移动异常
{
    OutChar(0x55);
    delaynms(1);  
    OutChar(0xaa);
    delaynms(1);  
    OutChar(0x04);
    delaynms(1);  
    OutChar(0x80);
    delaynms(1);  
    OutChar(0xae);
    delaynms(1);  
}
unsigned char move=0;
void Check_Sta()
{
if(More == 1)
    {
        More_Left();
        More = 0;
        move = 1;
    }
else if(Less == 1)
    {
        Less_Right();
        Less = 0;
        move = 1;
    }
}
/*void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt (void)
{
    R_Buff[Count_Re]=U1RXREG;            //read data

    if(R_Buff[Count_Re]==0xAA)           //the first receive data
    {
       R_Buff[0]=0xAA;
       Count_Re=0;
    }  
    
    Count_Re++;
    
    if((R_Buff[0]==0xAA)&&(Count_Re>=DATA_LENGTH))    
    {
        Count_Re=0;
        Flag_ReceivOver = 1;
    }
	IFS0bits.U1RXIF=0;
}*/