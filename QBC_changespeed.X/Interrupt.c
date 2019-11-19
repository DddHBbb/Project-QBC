
#include "Interrupt.h"
#include "Gloablevariable.h"
extern unsigned char CM;
 unsigned  char   AD_Re;                //the counter of receive data
 unsigned int     AD[20];              //the buffer of receive data  
/*==============================================================================
 *     函数名称： 定时器1中断            1ms
 *     函数功能:  系统时间计数
==============================================================================*/
void __attribute__((__interrupt__,auto_psv))_T1Interrupt(void)
{
    TMR1 = 0;  
    systemtime ++;                                                            //定期扫描计数，用于电机移动到位计时
    SystemTime1ms ++;                                                         //1ms计数，用于每次拍照发送计时
    systemtime1 ++;                                                           //用于发送错误或仓门关闭计时
    
    if((Flag_first_move==1)&&(systemtime > 30000))                            //超过30s， 移动不到位
    {
        Flag_move_error = 1;                                                  //移动错误标志
        StepMotorDisable;                                                     //步进电机   
        IEC0bits.T2IE =0;   
        systemtime = 0;
    }
    
    IFS0bits.T1IF = 0;                
}


/*==============================================================================
 *     函数名称： 定时器2中断   250us
 *     函数功能:  驱动步进电机90°翻转，
==============================================================================*/
//void __attribute__((interrupt, no_auto_psv)) _T2Interrupt (void)
//{
//    TMR2 = 0;                              
//    StepMotorStep = ~StepMotorStep;  
//    IFS0bits.T2IF = 0;     
//}
//void __attribute__((interrupt, no_auto_psv)) _T3Interrupt (void)
//{
//    TMR3 = 0;                              
//    StepMotorMODE3 = ~StepMotorMODE3;  
//
//    IFS0bits.T3IF = 0;     
//}
unsigned char  once=0;
void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt (void)
{
    unsigned char q;
    q = IFS0bits.U1RXIF;
    R_Buff[Count_Re]=U1RXREG;            //read data

//    if(R_Buff[Count_Re]==0xAA)           //the first receive data
//    {
//       R_Buff[0]=0xAA;
//       Count_Re=0;
//    }  
    
    Count_Re++;
    if((R_Buff[2] != 0) && (once == 0))
    {
        CM = R_Buff[2];
        once = 1;
    }
    if((R_Buff[0]==0xAA)&&(Count_Re>=DATA_LENGTH))    
    {
        Count_Re=0;
        Flag_ReceivOver = 1;
    }
	IFS0bits.U1RXIF=0;
	
}


//void __attribute__((__interrupt__,auto_psv)) _U1TXInterrupt (void)
//{
// 	IFS0bits.U1TXIF=0;
//    
//    U1TXREG=T_Buff[Count_Tr];
//    Count_Tr++;
//    
//    if(Count_Tr>=5)
//    {
//        Count_Tr=0;
//        U1STAbits.UTXEN=0;               //disable transmit
//    }
//}

/*==============================================================================
 *     函数名称： AD
 *     函数功能:  ad sample
==============================================================================*/
unsigned int Target_POS_Final;    //运动位置终止变量
unsigned int  Target_POS_First;   //运动位置起始变量
unsigned char  FLAG_POS_TEST;
unsigned char  FLAG_POS_Triger;

unsigned int  RESET_POS_AD;                       //初始位置AD值
unsigned int  POSADTEMP;                         //位移传感器ad转存变量
unsigned char  FLAG_POS_Reset;                   //电机复位标志位
unsigned char  FLAG_POS_Reset_triger;                   //电机复位触发标志位
unsigned int  RESET_POS_AD_CG;
extern  unsigned char  FLAG_AD_TRIGER;
unsigned int Val;
unsigned char  More=0,Less=0;
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{//66us
    unsigned int pos;
    unsigned int temp;
    
    POSADTEMP=ADC1BUF0;
    if(FLAG_AD_TRIGER==1)
    {
      POSADTEMP=ADC1BUF0;
      FLAG_AD_TRIGER=0;
      if((POSADTEMP>=(RESET_POS_AD-3))&&(POSADTEMP<=(RESET_POS_AD+3)))    //正好在复位位置，电机不运动
      {FLAG_POS_Reset_triger=3;}  
       if(POSADTEMP>(RESET_POS_AD+3))                                 //位置超出，需要回管动作
      {FLAG_POS_Reset_triger=2;} 
       if(POSADTEMP<(RESET_POS_AD-3))                                 //位置不到，需要进管动作
      {FLAG_POS_Reset_triger=1;}       
     }
    if(FLAG_POS_Reset_triger!=0) 
     {
       if((POSADTEMP>0)&&((POSADTEMP>(RESET_POS_AD-1))&&(POSADTEMP<(RESET_POS_AD+1)))) 
         {
           motor_turnoff();
           FLAG_POS_Reset=1;
           FLAG_POS_Reset_triger=0;
           POSADTEMP=0;
          }  
      }
    Val = ADC1BUF0;
    if(Val < 370)
    {
        More = 1;
    }
    else if(Val > 975)
    {
        Less = 1;
    }
    AD_Re=0;
    IFS0bits.AD1IF = 0;
}

/*==============================================================================
              AD[AD_Re]=ADC1BUF0;//12/5
            AD_Re++;
             if((AD_Re==1)&&(AD[0]>Target_POS_First))  
           {
               if((AD[0]-Target_POS_First)>Target_POS_Final)
              {
                      pos=AD[0]-Target_POS_First;  
                      temp=pos-Target_POS_Final;
                      if((temp>0)&&((temp>3)||(temp<3))) 
                      {
                        FLAG_POS_TEST=1;
                      // AD[1]=0;AD[0]=0;
                       FLAG_POS_TEST=1;
                      } 
               } 
         

           }
==============================================================================*/
    