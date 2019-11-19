
#ifndef GLOABLEDEFINE_H
#define GLOABLEDEFINE_H

#include "p24FV32KA304.h"

//2019��3��4���޸�


#define  PLL_XT                            //��Ƶ
//#define  test                              //����
//#define  testCOMM                          //����ͨѶ
//#define  test_aging                         //�����ϻ� �����������̣�5��λ�ã������մ����������λ��ͣ��10��
//#define test_aging2_5                        //�����ϻ�2#~5#λ������λ�������ܣ��ֱ�ͣ��1��

//4V

#ifdef PLL_XT                                 //16MHz
    #define FOSC 16000000           
    #define FCY  FOSC/2
    #define BAND 9600                      //56000 //57600 //115200 //128000 ѡ�⼸�������ʶ�����
#else                                         //4MHz
    #define FOSC 4000000           
    #define FCY  FOSC/2
    #define BAND 19200                        //14400 //19200 //38400 ѡ�⼸�������ʶ�����
#endif


/********      ͨѶ      ********/
#define DATA_LENGTH    5                     //receive or transmit  n BYTEs

#define RE_START         0x01                  //���յ������λ�����͵������������
#define RE_END_CAMERA    0x03                  //���յ������λ�����͵����ս�������
#define RE_FINISH        0x04                  //���յ������λ�����͵ļ���������
#define RE_IN_TEST       0xFC                  //���յ������λ�����͵Ľ�������������
#define RE_EX_TEST       0xFB                  //���յ������λ�����͵��˳������������
#define RE_AGING         0xFA                  //���յ������λ�����͵��ϻ��������
#define RE_STOP          0xF0                  //���յ������λ�����͵���ֹ�������

#define TR_CLOSE         0x03                  //���͵�������͸���λ��,���Źر�����
#define TR_CLOSE_CHK     0xad                  //���͵�������͸���λ��,���Źر�����,У����
#define TR_READY         0x01                  //���͵�������͸���λ��,׼���ÿ�������
#define TR_READY_CHK     0xab                  //���͵�������͸���λ��,׼���ÿ�������,У����
#define TR_TUBE          0x02                  //���͵�������͸���λ��,׼���ÿ���ȡ��
#define TR_TUBE_CHK      0xac                  //���͵�������͸���λ��,׼���ÿ���ȡ��,У����
#define TR_ERR           0x04                  //���͵�������͸���λ��,�����쳣
#define TR_ERR_CHK       0xae                  //���͵�������͸���λ��,�����쳣,У����


/********      ����      ********/
#define  OPEN_CLOSE           PORTAbits.RA1



/********      λ�ð������ӵ����5,3,4,1,2      ********/
#define  JN_P2                PORTBbits.RB3          //���ڵĶ���ʱ���չ���˳��ӵ����5��3��4��1��2��1--ȡ�Ź�λ�ã�2�����λ�ã�  
#define  JN_P1                PORTBbits.RB2
#define  JN_P4                PORTCbits.RC1
#define  JN_P3                PORTCbits.RC0
#define  JN_P5                PORTCbits.RC2   


/********      ��Դ      ********/
#define  BLUE_ENable          PORTAbits.RA11 = 1 ;asm ("NOP")          //��ɫ��Դʹ��
#define  BLUE_DISable         PORTAbits.RA11 = 0 ;asm ("NOP")         
//#define  BLUE_ON              PORTAbits.RA4 = 1 ;asm ("NOP")           //��ɫ��Դ
//#define  BLUE_OFF             PORTAbits.RA4 = 0 ;asm ("NOP")         

#define  BLUE1_EN               PORTBbits.RB13= 1 ;asm ("NOP")          //��ɫ��Դ1ʹ��
#define  BLUE1_DIS              PORTBbits.RB13 = 0 ;asm ("NOP")         
//#define  RED_ON               PORTBbits.RB15 = 1 ;asm ("NOP")           //��ɫ��Դ1
//#define  RED_OFF              PORTBbits.RB15 = 0 ;asm ("NOP")         



/********     �������      ********/   //20190305
#define StepMotorEnable       PORTCbits.RC1 = 1 ;asm ("NOP")      //nENBL������������� 
#define StepMotorDisable      PORTCbits.RC1 = 0 ;asm ("NOP")      //nENBL����������ر�

#define StepMotorReversal     PORTBbits.RB1 = 1  ;asm ("NOP")    //DIR������������� 0  ˳ʱ��
#define StepMotorForeward     PORTBbits.RB1 = 0  ;asm ("NOP")    //DIR������������� 1  ��ʱ��
#define StepMotorMODE4        PORTBbits.RB1                      //DIR�������������    mode4

#define StepMotorStepOn       PORTAbits.RA10 = 1  ;asm ("NOP")
#define StepMotorStepOff      PORTAbits.RA10 = 0  ;asm ("NOP")
#define StepMotorStep         PORTAbits.RA10                      //STEP�������������
 
#define StepMotorMODE1        PORTBbits.RB2                  //mode1
#define StepMotorMODE2        PORTBbits.RB3                  //mode2
#define StepMotorMODE3        PORTBbits.RB0                  //mode3
#define StepMotorSTBY         PORTCbits.RC0                  //STBY
#define StepMotorVS           PORTBbits.RB14                 //����оƬ��Դ����



#endif
