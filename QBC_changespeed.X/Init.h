#ifndef INIT_H
#define INIT_H


unsigned int Restreg;



unsigned int rest(void);
void InitDevices(void);
void InitIO(void);
void InitTimer1(void);
void InitTimer2(void);
void InitOSCCON(void);
void InitUart1(void);
void Init_Tube(void);
void InitVar(void);
void InitAdc(void);

#endif	/* INIT_H */

