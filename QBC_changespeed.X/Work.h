#ifndef WORK_H
#define WORK_H



unsigned char Flag_ready_fetch_tube;     //׼��ȡ��



unsigned char Flag_first_move;         //��һ���ƶ�
unsigned char Flag_first_camera;       //��һ�ν�������


unsigned char Flag_move_error;         //�ƶ������־
unsigned char Flag_camera_error;       //���մ���

unsigned char Camera_count;            //���մ���

unsigned char Flag_P1;                 //1��λ��
unsigned char Flag_P2;                 //2��λ��
unsigned char Flag_P3;                 //3��λ��
unsigned char Flag_P4;                 //4��λ��
unsigned char Flag_P5;                 //5��λ��
unsigned char Flag_Init_Tube;          //1��λ��--ȡ��
unsigned char Flag_first_P4;           //��һ�ε�4��λ������

//unsigned char Freq_count;             //���Ƶ�ʼ��ټ���
unsigned char To_position;            //Ҫ�����λ��


void Working(void);       
void Camera(void);                     //����

void Error(void) ;
void Init_Tube(void); 


void Test_25(void);



#endif
