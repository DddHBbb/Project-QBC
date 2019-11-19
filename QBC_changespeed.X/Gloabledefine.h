
#ifndef GLOABLEDEFINE_H
#define GLOABLEDEFINE_H

#include "p24FV32KA304.h"

//2019年3月4日修改


#define  PLL_XT                            //倍频
//#define  test                              //调试
//#define  testCOMM                          //测试通讯
//#define  test_aging                         //测试老化 按工作的流程，5个位置，不接收串口命令，拍照位置停留10秒
//#define test_aging2_5                        //测试老化2#~5#位，两个位置来回跑，分别停留1秒

//4V

#ifdef PLL_XT                                 //16MHz
    #define FOSC 16000000           
    #define FCY  FOSC/2
    #define BAND 9600                      //56000 //57600 //115200 //128000 选这几个波特率都可以
#else                                         //4MHz
    #define FOSC 4000000           
    #define FCY  FOSC/2
    #define BAND 19200                        //14400 //19200 //38400 选这几个波特率都可以
#endif


/********      通讯      ********/
#define DATA_LENGTH    5                     //receive or transmit  n BYTEs

#define RE_START         0x01                  //接收的命令，上位机发送的启动检测命令
#define RE_END_CAMERA    0x03                  //接收的命令，上位机发送的拍照结束命令
#define RE_FINISH        0x04                  //接收的命令，上位机发送的检测完成命令
#define RE_IN_TEST       0xFC                  //接收的命令，上位机发送的进入电机调试命令
#define RE_EX_TEST       0xFB                  //接收的命令，上位机发送的退出电机调试命令
#define RE_AGING         0xFA                  //接收的命令，上位机发送的老化电机命令
#define RE_STOP          0xF0                  //接收的命令，上位机发送的中止检测命令

#define TR_CLOSE         0x03                  //发送的命令，发送给上位机,仓门关闭命令
#define TR_CLOSE_CHK     0xad                  //发送的命令，发送给上位机,仓门关闭命令,校验码
#define TR_READY         0x01                  //发送的命令，发送给上位机,准备好可以拍照
#define TR_READY_CHK     0xab                  //发送的命令，发送给上位机,准备好可以拍照,校验码
#define TR_TUBE          0x02                  //发送的命令，发送给上位机,准备好可以取管
#define TR_TUBE_CHK      0xac                  //发送的命令，发送给上位机,准备好可以取管,校验码
#define TR_ERR           0x04                  //发送的命令，发送给上位机,工作异常
#define TR_ERR_CHK       0xae                  //发送的命令，发送给上位机,工作异常,校验码


/********      仓门      ********/
#define  OPEN_CLOSE           PORTAbits.RA1



/********      位置按：（从电机）5,3,4,1,2      ********/
#define  JN_P2                PORTBbits.RB3          //现在的定义时按照工作顺序从电机起5、3、4、1、2（1--取放管位置，2顶入管位置）  
#define  JN_P1                PORTBbits.RB2
#define  JN_P4                PORTCbits.RC1
#define  JN_P3                PORTCbits.RC0
#define  JN_P5                PORTCbits.RC2   


/********      光源      ********/
#define  BLUE_ENable          PORTAbits.RA11 = 1 ;asm ("NOP")          //蓝色光源使能
#define  BLUE_DISable         PORTAbits.RA11 = 0 ;asm ("NOP")         
//#define  BLUE_ON              PORTAbits.RA4 = 1 ;asm ("NOP")           //蓝色光源
//#define  BLUE_OFF             PORTAbits.RA4 = 0 ;asm ("NOP")         

#define  BLUE1_EN               PORTBbits.RB13= 1 ;asm ("NOP")          //蓝色光源1使能
#define  BLUE1_DIS              PORTBbits.RB13 = 0 ;asm ("NOP")         
//#define  RED_ON               PORTBbits.RB15 = 1 ;asm ("NOP")           //蓝色光源1
//#define  RED_OFF              PORTBbits.RB15 = 0 ;asm ("NOP")         



/********     步进电机      ********/   //20190305
#define StepMotorEnable       PORTCbits.RC1 = 1 ;asm ("NOP")      //nENBL，步进电机开启 
#define StepMotorDisable      PORTCbits.RC1 = 0 ;asm ("NOP")      //nENBL，步进电机关闭

#define StepMotorReversal     PORTBbits.RB1 = 1  ;asm ("NOP")    //DIR，步进电机方向 0  顺时针
#define StepMotorForeward     PORTBbits.RB1 = 0  ;asm ("NOP")    //DIR，步进电机方向 1  逆时针
#define StepMotorMODE4        PORTBbits.RB1                      //DIR，步进电机方向    mode4

#define StepMotorStepOn       PORTAbits.RA10 = 1  ;asm ("NOP")
#define StepMotorStepOff      PORTAbits.RA10 = 0  ;asm ("NOP")
#define StepMotorStep         PORTAbits.RA10                      //STEP，步进电机驱动
 
#define StepMotorMODE1        PORTBbits.RB2                  //mode1
#define StepMotorMODE2        PORTBbits.RB3                  //mode2
#define StepMotorMODE3        PORTBbits.RB0                  //mode3
#define StepMotorSTBY         PORTCbits.RC0                  //STBY
#define StepMotorVS           PORTBbits.RB14                 //驱动芯片电源控制



#endif
