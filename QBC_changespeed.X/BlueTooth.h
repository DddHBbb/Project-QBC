
#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

    
unsigned char  Flag_ReceivOver;         //finish Receiving data , set this flag

unsigned char  Flag_start_detect;       //set flag  启动检测命令
unsigned char  Flag_end_camera;         //set flag  拍照结束命令
unsigned char  Flag_finish_detect;      //set flag  完成检测命令
unsigned char  Flag_test;               //set flag  电机调试命令，收到进入电机调试命令=1；收到退出电机调试命令=0
unsigned char  Flag_aging;              //set flag  电机老化命令
unsigned char  Flag_stop;               //set flag  中止检测命令


unsigned int Count_Re=0;                //the counter of receive data
unsigned int Count_Tr=0;                //the counter of transmit data    
unsigned int Count_TransTime;         //the counter of transmit data time ,  
unsigned char R_Buff[DATA_LENGTH];              //the buffer of receive data    
unsigned char T_Buff[DATA_LENGTH];              //the buffer of transmit data    


void Ready_Trans(unsigned char commd, unsigned char chksum);
void BlueTooth(void);

void CheckSum(void);                  //计算校验和




#endif	/* BLUETOOTH_H */
