
#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

    
unsigned char  Flag_ReceivOver;         //finish Receiving data , set this flag

unsigned char  Flag_start_detect;       //set flag  �����������
unsigned char  Flag_end_camera;         //set flag  ���ս�������
unsigned char  Flag_finish_detect;      //set flag  ��ɼ������
unsigned char  Flag_test;               //set flag  �����������յ���������������=1���յ��˳������������=0
unsigned char  Flag_aging;              //set flag  ����ϻ�����
unsigned char  Flag_stop;               //set flag  ��ֹ�������


unsigned int Count_Re=0;                //the counter of receive data
unsigned int Count_Tr=0;                //the counter of transmit data    
unsigned int Count_TransTime;         //the counter of transmit data time ,  
unsigned char R_Buff[DATA_LENGTH];              //the buffer of receive data    
unsigned char T_Buff[DATA_LENGTH];              //the buffer of transmit data    


void Ready_Trans(unsigned char commd, unsigned char chksum);
void BlueTooth(void);

void CheckSum(void);                  //����У���




#endif	/* BLUETOOTH_H */
