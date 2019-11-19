
#include "Delay.h"




void Delay(unsigned int n)        //1.5us*4, 4MHz
{
    while(n)
    {
        n--;
    }
}


void delaynms(unsigned int n)      //1ms*4, 4MHz
{
	unsigned int i,j;
    
		for(i=0;i<n;i++)
			for(j=0;j<1600;j++);
}
