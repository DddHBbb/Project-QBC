#ifndef GLOABLEVARIABLE_H
#define GLOABLEVARIABLE_H

#include "Gloabledefine.h"

#define CM_XG



//*==============================================================================
// *    全局变量声明
//==============================================================================*/
extern unsigned int systemtime;            //1ms定时中累加
extern unsigned int SystemTime1ms;         //1ms定时中累加
extern unsigned int systemtime1;           //1ms定时中累加

extern unsigned char Freq_count;           //电机频率加速计数

extern unsigned char  Flag_ReceivOver;         //finish Receiving data , set this flag


extern unsigned char  Flag_start_detect;      //set flag  启动检测命令
extern unsigned char  Flag_end_camera;        //set flag  拍照结束命令
extern unsigned char  Flag_finish_detect;     //set flag  完成检测命令
extern unsigned char  Flag_test;              //set flag  电机调试命令，收到进入电机调试命令=1；收到退出电机调试命令=0
extern unsigned char  Flag_aging;             //set flag  电机老化命令
extern unsigned char  Flag_stop;              //set flag  中止检测命令


extern unsigned int Count_Re;                //the counter of receive data
extern unsigned int Count_Tr;                //the counter of transmit data    
extern unsigned int Count_TransTime;         //the counter of transmit data time ,  
extern unsigned char R_Buff[DATA_LENGTH];              //the buffer of receive data    
extern unsigned char T_Buff[DATA_LENGTH];              //the buffer of transmit data    




extern void Ready_Trans(unsigned char commd, unsigned char chksum);
extern void BlueTooth(void);


extern unsigned char Flag_ready_fetch_tube;        //准备取管

extern unsigned char Flag_close_ok;              //1，仓门关闭；0，未关闭


extern unsigned char Flag_first_move;         //第一次移动
extern unsigned char Flag_move_error;         //移动错误标志
extern unsigned char Flag_first_camera;       //第一次进入拍照
extern unsigned char Flag_camera_error;       //拍照错误
//extern unsigned char Flag_error;              //错误

extern unsigned char Camera_count;            //拍照次数
extern unsigned char Flag_error;              //错误标志

extern unsigned char Flag_close_ok;            //1、仓门打开，仓门又关闭；0，未打开过，未关闭



extern unsigned char Flag_P1;                 //1号位置
extern unsigned char Flag_P2;                 //2号位置
extern unsigned char Flag_P3;                 //3号位置
extern unsigned char Flag_P4;                 //4号位置
extern unsigned char Flag_P5;                 //5号位置
extern unsigned char Flag_Init_Tube;          //1号位置
extern unsigned char Flag_first_P4;           //第一次到4号位置拍照


extern void Working(void);


extern void Door_check(void); 
extern void Testing(void); 


extern void Test_25(void);

extern void delaynms(unsigned int n);
extern void Delay(unsigned int n);
extern void Init_Tube(void); 
extern void InitVar(void);

#endif

