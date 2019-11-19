#include "Main.h"
#include "Gloablevariable.h"
////version:  PRQBC-QDV1.0 20190329 WHQ 
extern unsigned char move;
int main(void)
{
    InitIO(); 
    motor_start_32();
    InitDevices();   
//    delaynms(500);
    InitTimer2();
    InitOutput();
    T2CONbits.TON = 1;
//    while(move == 0)
//    {
    Check_Sta();
//    }
    delaynms(30);
    motor_reset_5();  
   // delaynms(3000);
    uart_to_6755_cmguanbi();
    blueled_on();
    while(1)
    {
    //    Check_Sta();
        uart_from_6755();
    }
}

