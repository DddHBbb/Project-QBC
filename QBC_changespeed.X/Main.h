#ifndef MAIN_H
#define MAIN_H

#include "Gloablevariable.h"


//  编译器C30

#ifdef PLL_XT
    _FOSCSEL (IESO_ON & FNOSC_PRIPLL & SOSCSEL_SOSCLP);           //使能切换，外部倍频
    _FOSC (FCKSM_CSECMD & POSCMOD_XT & OSCIOFNC_ON & POSCFREQ_MS); //使能切换，主震荡为XT
    
    _FWDT(0XFFD6);   //WDT  RCONbits.SWDTEN 256MS
    _FPOR(0XFFFF);   //欠压复位最低  RCONbits.SBOREN
    _FICD(ICS_PGx2); //PGEC2,PGED2
#else
    _FOSCSEL (IESO_ON & FNOSC_PRI & SOSCSEL1_SOSCLP);              //使能切换，外部不倍频 
    _FOSC (FCKSM_CSDCMD & POSCMOD_XT & OSCIOFNC_ON & POSCFREQ_MS); //使能切换，主震荡为XT 
    
    _FWDT(0XFFD6);   //WDT  RCONbits.SWDTEN 256MS
    _FPOR(0XFFFF);   //欠压复位最低  RCONbits.SBOREN
    _FICD(ICS_PGx2); //PGEC2,PGED2
#endif    
    
    

//unsigned int prog_time;
//unsigned int prog_cnt;
//unsigned int prog_cnt_copy;


#endif	/* MAIN_H */
