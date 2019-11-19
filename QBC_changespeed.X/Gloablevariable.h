#ifndef GLOABLEVARIABLE_H
#define GLOABLEVARIABLE_H

#include "Gloabledefine.h"

#define CM_XG



//*==============================================================================
// *    ȫ�ֱ�������
//==============================================================================*/
extern unsigned int systemtime;            //1ms��ʱ���ۼ�
extern unsigned int SystemTime1ms;         //1ms��ʱ���ۼ�
extern unsigned int systemtime1;           //1ms��ʱ���ۼ�

extern unsigned char Freq_count;           //���Ƶ�ʼ��ټ���

extern unsigned char  Flag_ReceivOver;         //finish Receiving data , set this flag


extern unsigned char  Flag_start_detect;      //set flag  �����������
extern unsigned char  Flag_end_camera;        //set flag  ���ս�������
extern unsigned char  Flag_finish_detect;     //set flag  ��ɼ������
extern unsigned char  Flag_test;              //set flag  �����������յ���������������=1���յ��˳������������=0
extern unsigned char  Flag_aging;             //set flag  ����ϻ�����
extern unsigned char  Flag_stop;              //set flag  ��ֹ�������


extern unsigned int Count_Re;                //the counter of receive data
extern unsigned int Count_Tr;                //the counter of transmit data    
extern unsigned int Count_TransTime;         //the counter of transmit data time ,  
extern unsigned char R_Buff[DATA_LENGTH];              //the buffer of receive data    
extern unsigned char T_Buff[DATA_LENGTH];              //the buffer of transmit data    




extern void Ready_Trans(unsigned char commd, unsigned char chksum);
extern void BlueTooth(void);


extern unsigned char Flag_ready_fetch_tube;        //׼��ȡ��

extern unsigned char Flag_close_ok;              //1�����Źرգ�0��δ�ر�


extern unsigned char Flag_first_move;         //��һ���ƶ�
extern unsigned char Flag_move_error;         //�ƶ������־
extern unsigned char Flag_first_camera;       //��һ�ν�������
extern unsigned char Flag_camera_error;       //���մ���
//extern unsigned char Flag_error;              //����

extern unsigned char Camera_count;            //���մ���
extern unsigned char Flag_error;              //�����־

extern unsigned char Flag_close_ok;            //1�����Ŵ򿪣������ֹرգ�0��δ�򿪹���δ�ر�



extern unsigned char Flag_P1;                 //1��λ��
extern unsigned char Flag_P2;                 //2��λ��
extern unsigned char Flag_P3;                 //3��λ��
extern unsigned char Flag_P4;                 //4��λ��
extern unsigned char Flag_P5;                 //5��λ��
extern unsigned char Flag_Init_Tube;          //1��λ��
extern unsigned char Flag_first_P4;           //��һ�ε�4��λ������


extern void Working(void);


extern void Door_check(void); 
extern void Testing(void); 


extern void Test_25(void);

extern void delaynms(unsigned int n);
extern void Delay(unsigned int n);
extern void Init_Tube(void); 
extern void InitVar(void);

#endif

