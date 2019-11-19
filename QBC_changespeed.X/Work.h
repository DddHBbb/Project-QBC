#ifndef WORK_H
#define WORK_H



unsigned char Flag_ready_fetch_tube;     //准备取管



unsigned char Flag_first_move;         //第一次移动
unsigned char Flag_first_camera;       //第一次进入拍照


unsigned char Flag_move_error;         //移动错误标志
unsigned char Flag_camera_error;       //拍照错误

unsigned char Camera_count;            //拍照次数

unsigned char Flag_P1;                 //1号位置
unsigned char Flag_P2;                 //2号位置
unsigned char Flag_P3;                 //3号位置
unsigned char Flag_P4;                 //4号位置
unsigned char Flag_P5;                 //5号位置
unsigned char Flag_Init_Tube;          //1号位置--取管
unsigned char Flag_first_P4;           //第一次到4号位置拍照

//unsigned char Freq_count;             //电机频率加速计数
unsigned char To_position;            //要到达的位置


void Working(void);       
void Camera(void);                     //拍照

void Error(void) ;
void Init_Tube(void); 


void Test_25(void);



#endif
