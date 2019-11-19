
#include "Interrupt.h"
#include "Gloablevariable.h"
extern unsigned char CM;
 unsigned  char   AD_Re;                //the counter of receive data
 unsigned int     AD[20];              //the buffer of receive data  
/*==============================================================================
 *     �������ƣ� ��ʱ��1�ж�            1ms
 *     ��������:  ϵͳʱ�����
==============================================================================*/
void __attribute__((__interrupt__,auto_psv))_T1Interrupt(void)
{
    TMR1 = 0;  
    systemtime ++;                                                            //����ɨ����������ڵ���ƶ���λ��ʱ
    SystemTime1ms ++;                                                         //1ms����������ÿ�����շ��ͼ�ʱ
    systemtime1 ++;                                                           //���ڷ��ʹ������Źرռ�ʱ
    
    if((Flag_first_move==1)&&(systemtime > 30000))                            //����30s�� �ƶ�����λ
    {
        Flag_move_error = 1;                                                  //�ƶ������־
        StepMotorDisable;                                                     //�������   
        IEC0bits.T2IE =0;   
        systemtime = 0;
    }
    
    IFS0bits.T1IF = 0;                
}


/*==============================================================================
 *     �������ƣ� ��ʱ��2�ж�   250us
 *     ��������:  �����������90�㷭ת��
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
 *     �������ƣ� AD
 *     ��������:  ad sample
==============================================================================*/
unsigned int Target_POS_Final;    //�˶�λ����ֹ����
unsigned int  Target_POS_First;   //�˶�λ����ʼ����
unsigned char  FLAG_POS_TEST;
unsigned char  FLAG_POS_Triger;

unsigned int  RESET_POS_AD;                       //��ʼλ��ADֵ
unsigned int  POSADTEMP;                         //λ�ƴ�����adת�����
unsigned char  FLAG_POS_Reset;                   //�����λ��־λ
unsigned char  FLAG_POS_Reset_triger;                   //�����λ������־λ
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
      if((POSADTEMP>=(RESET_POS_AD-3))&&(POSADTEMP<=(RESET_POS_AD+3)))    //�����ڸ�λλ�ã�������˶�
      {FLAG_POS_Reset_triger=3;}  
       if(POSADTEMP>(RESET_POS_AD+3))                                 //λ�ó�������Ҫ�عܶ���
      {FLAG_POS_Reset_triger=2;} 
       if(POSADTEMP<(RESET_POS_AD-3))                                 //λ�ò�������Ҫ���ܶ���
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
    