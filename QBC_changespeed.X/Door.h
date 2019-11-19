#ifndef DOOR_H
#define DOOR_H


unsigned char Flag_close_ok;              //1、仓门打开，仓门又关闭；0，未打开过，未关闭
unsigned char Flag_open;                 //1，仓门打开；0，未打开过
unsigned char Flag_close;                 //1，仓门打开；0，未打开过

void Door_check(void);       




#endif
