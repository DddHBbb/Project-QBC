
#include "Init.h"
#include "Gloablevariable.h"

extern unsigned int  RESET_POS_AD;
extern  unsigned int  RESET_POS_AD_CG; 
/*==============================================================================
 *     ��������:  PORT �˿ڳ�ʼ��
==============================================================================*/
void InitIO(void)
{
    PORTAbits.RA10=0;   
    PORTAbits.RA11=0;
    TRISA=0xf3ee;       //RA11��RA10���
    ANSELA=0x0000;      //0--digital IO;
    
    PORTB=0x9DF0;   
    PORTBbits.RB13=0;
    TRISB=0x9DF0;       //0--RB14��RB9��RB3��RB2��RB1��RB0 RB13  ���  1--RB4����
    ANSELB=0x0010;      //0--digital IO; RB4ģ���
    
    PORTC=0xff7f; 
    PORTCbits.RC0=0;
    PORTCbits.RC1=0;
    PORTCbits.RC8=0;
    TRISC=0xfe7C;       //RC7--TXD 0--RC0��RC1��RC8���
    ANSELC=0x0000;      //0--digital IO;

	
	//StepMotorDisable;   //2018-09-25
}


#ifdef PLL_XT
/*==============================================================================
 *     �������ƣ� ��ʱ��1��ʼ��  1ms    XT:4MHz, XTPLL: Fosc =16MHz, 0.0625us,
 *                                 ��ʱ��ʱ��=Fosc/2=16M/2=8M,       
 ==============================================================================*/
void InitTimer1(void) 
{
    T1CON = 0;            //�رն�ʱ��
    TMR1 = 0;             //���������㣬��TMR1=PR1ʱ���жϱ�־λ���
    PR1 = 8000;           //ʱ�Ӳ���Ƶ��Tcy=1/8=0.125us.    PR1=0.125us*8000,1mS ��������
//    IPC0bits.T1IP = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 0;
}
#endif


#ifdef PLL_XT
/*==============================================================================
 *     �������ƣ� ��ʱ��2��ʼ��37.5us   XT:4MHz, XTPLL: Fosc =16MHz, 0.0625us,
 *                                 ��ʱ��ʱ��=Fosc/2=16M/2=8M,      
==============================================================================*/
void InitTimer2(void)   //����OC3��PWM���
{
    T2CON = 0;            //�رն�ʱ��
    TMR2 = 0;             //���������㣬��TMR5=PR5ʱ���жϱ�־λ���
    T2CONbits.TCKPS=0;
    
    PR2 = 9000;            //ʱ�Ӳ���Ƶ��Tcy=1/8=0.125us.    PR2=0.125us*400, 50uS ���Ƶ��Ϊ1/50us=20KHz����1/1s=1Hz�� 
    IFS0bits.T2IF = 0;    //�жϱ�־λ����
    IEC0bits.T2IE = 0;    //�ж�ʹ��
    T2CONbits.TON = 0;    //������ʱ��
}

void InitTimer3(void) 
{
    T3CON = 0;            //�رն�ʱ��
    TMR3 = 0;             //���������㣬��TMR1=PR1ʱ���жϱ�־λ���
    T3CONbits.TCKPS=0;    //Ԥ��Ƶ 1:64
    
    PR3=400;            //ʱ�Ӳ���Ƶ��Tcy=1/8=0.125us.    PR2=0.125us*100, 12.5uS ���Ƶ��Ϊ1/12.5us=80KHz����1/1s=1Hz�� 
//    IPC2bits.T3IP = 1;
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 0;
    T3CONbits.TON = 0;
}

void InitTimer4(void)   //����OC2��PWM���
{
    T4CON = 0;            //�رն�ʱ��
    TMR4 = 0;             //���������㣬��TMR5=PR5ʱ���жϱ�־λ���
    T4CONbits.TCKPS=0;
    
    PR4 = 62;            //ʱ�Ӳ���Ƶ��Tcy=1/8=0.125us.    PR2=0.125us*400, 50uS ���Ƶ��Ϊ1/50us=20KHz����1/1s=1Hz�� 
    IFS1bits.T4IF = 0;    //�жϱ�־λ����
    IEC1bits.T4IE = 0;    //�ж�ʹ��
    T4CONbits.TON = 1;    //������ʱ��
}
#endif


#ifndef PLL_XT
/*==============================================================================
 *     �������ƣ� ��ʱ��1��ʼ��  1ms    XT:4MHz,  Fosc =4MHz, 0.25us,
 *                                 ��ʱ��ʱ��=Fosc/2=4M/2=2M,       
 ==============================================================================*/
void InitTimer1(void) 
{
    T1CON = 0;            //�رն�ʱ��
    TMR1 = 0;             //���������㣬��TMR1=PR1ʱ���жϱ�־λ���
    PR1 = 2000;           //ʱ�Ӳ���Ƶ��Tcy=1/2=0.5us.    PR1=0.5us*2000,1mS ��������
//    IPC0bits.T1IP = 1;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;
}
#endif


#ifndef PLL_XT
/*==============================================================================
 *     �������ƣ� ��ʱ��2��ʼ��25us   XT:4MHz,  Fosc =4MHz, 0.25us,
 *                                 ��ʱ��ʱ��=Fosc/2=4M/2=2M,      
==============================================================================*/
void InitTimer2(void)//15.6k
{
    T2CON=0;
    T2CONbits.TCKPS=0;//fcy
    TMR2=0;
    PR2=512;
    T2CONbits.TON=1;
}

#endif

void InitOutput(void)//15.6K  OC3
{
    OC3CON1 = 0;
    OC3CON1bits.OCTSEL=0;//TIMER2
    OC3CON1 = 0x07;
    OC3CON2bits.SYNCSEL = 0x0c;//timer2
    OC3R = 4000;
    OC3RS = 9000;//DUTY OF THE PWM
}

void InitOutput1(void)//15.6K  OC2
{
    OC2CON1 = 0X0807;  //ѡ��timer4,���Ķ����PWMģʽ 
    OC2CON2bits.SYNCSEL = 14;//timer4
    OC2R = 62;
    OC2RS =50 ;//DUTY OF THE PWM


}

void InitOSCCON(void)
{	
    __builtin_write_OSCCONH(0x03);   //�л�����������PLL XT����4����16MHz
    __builtin_write_OSCCONL(0x01);   //�л�ʹ��
    while(OSCCONbits.COSC != 0b011); //�ȴ��л�
    // Wait for PLL to lock
    //while(OSCCONbits.LOCK != 1);   //�ȴ�����
    while(OSCCONbits.OSWEN);
}


unsigned int rest(void)
{
    unsigned int rd;
    unsigned int i;
        
    RCONbits.SWDTEN = 0;               //watchdog off
    rd = RCON;
    RCON = 0X2000;
    
#ifdef PLL_XT    
    InitOSCCON();                    //��Ƶ
#endif
    
    for(i=0;i++;i<9000);
    
    return rd;
}


/*==============================================================================
 *     �������ƣ� ����1��ʼ��   XT:4MHz, XTPLL: Fosc =16MHz, 0.0625us,
 *                                 fcy=Fosc/2=16M/2=8M ,      
==============================================================================*/
void InitUart1(void)
{
  U1BRG=((FCY/BAND)/16)-1;           //207��   Fosc=4M, fcy=2M,  baud,   high speed 

  U1MODE=0x0000;
  U1MODEbits.BRGH=0;               // 1= high speed
  U1MODEbits.PDSEL=0;            // no parity and 8-bit data
  U1MODEbits.STSEL=0;            // 1-stop bit
          
  U1STAbits.URXISEL=0;           //interrupt generated when any character is transfered.���յ����ַ������ж�
  
  U1STAbits.UTXISEL1=0; 
  U1STAbits.UTXISEL0=1; 
  
  IFS0bits.U1RXIF=0;
  IFS0bits.U1TXIF=0;
  
  IEC0bits.U1TXIE=0;            
  IEC0bits.U1RXIE=1;            

  U1MODEbits.UARTEN=1;
  U1STAbits.UTXEN=1;   
  

}

/*==============================================================================
 *     �������ƣ� AD��ʼ��   XT:4MHz, XTPLL: Fosc =16MHz, 0.0625us,
 *                                 fcy=Fosc/2=16M/2=8M ,      
==============================================================================*/
void InitAdc(void)
{
    AD1CON1 = 0;
    AD1CON1bits.ASAM = 1;
    AD1CON1bits.SSRC = 7;//����Դ
    AD1CON2bits.PVCFG = 0;
    AD1CON2bits.NVCFG = 0;
    AD1CON2bits.CSCNA = 0;//ɨ������
    AD1CON2bits.SMPI = 0;//4�β����ж�
    AD1CON3bits.SAMC = 4;//�Զ�����ʱ��
    AD1CON3bits.ADCS = 7;//ADת��ʱ��
    AD1CHSbits.CH0SA = 15;
    AD1CSSL = 0X0080;
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;
    ANSELA = 0X0000;
    ANSELB = 0X0010;
    ANSELC = 0X0000;
    AD1CON1bits.ADON = 1;/**/
}

/*==============================================================================
 *     �������ƣ� ������ʼ�� 
==============================================================================*/
void InitVar(void)
{
    Flag_first_move = 0;  
    Flag_move_error = 0;
    Flag_first_camera=0;
    Flag_camera_error = 0;
    
    Flag_P1 = 0;     
    Flag_P2 = 0;
    Flag_P3 = 0;
    Flag_P4 = 0;   
    Flag_P5 = 0;
    Flag_Init_Tube = 0; 
    Flag_first_P4 = 0;  
    
//    BLUE_DISable;                   //�ر���ɫ��Դ   test����
//    BLUE_OFF;  
    Camera_count = 0;               //�����մ���
    Flag_start_detect = 0;
    
    Flag_stop = 0;
    Flag_test = 0; 
    Flag_aging = 0;
    
    systemtime1 = 0;
    systemtime = 0;
    SystemTime1ms = 0;
}


void InitDevices(void)
{
    Restreg=rest();
//    InitIO();
    InitAdc();
    InitTimer1();
   
    InitTimer3();
    InitTimer4();
    InitUart1();
    //InitVar();
    InitOutput1();
//    InitAdc();
    RESET_POS_AD=846;
    RESET_POS_AD_CG=RESET_POS_AD-525;
}


