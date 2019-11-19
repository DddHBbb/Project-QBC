#include "uart.h"
#include "Gloablevariable.h"
unsigned char CM=0;
extern  unsigned int  RESET_POS_AD;                       //��ʼλ��ADֵ
extern  unsigned int  POSADTEMP;                         //λ�ƴ�����adת�����
extern unsigned char  FLAG_POS_Reset;                   //�����λ��־λ
extern unsigned char  FLAG_POS_Reset_triger;                   //�����λ������־λ
extern unsigned char  FLAG_AD_TRIGER;
extern unsigned char  FLAG_PHOTO_END;
extern  unsigned int  RESET_POS_AD_CG;                       //��λ�ã�����λ��
//1mmλ������ӦADֵԼΪ15  ���Ծ��루�Դ�����������𣩣�5--35mm(377)  4--39mm(453)  3--51mm(705)  1--60mm(846)  2--66mm(971)
void motor_start_32()    // 0 0 0 0--full   0 1 0 0-32  ����оƬ32ϸ���������    1 1 1 1-16 
{
   // StepMotorStepOn;
    asm ("NOP");
    StepMotorVS=1;       //������оƬ�ϵ�
     asm ("NOP");
     asm ("NOP");
    StepMotorSTBY=1;
    asm ("NOP");         //��ʱ250ns
    StepMotorMODE1=1;     //ѡ��1/32ϸ��
     asm ("NOP");
    StepMotorMODE2=0;
     asm ("NOP");
    StepMotorMODE3=0;
     asm ("NOP");
    StepMotorMODE4=0;
    asm ("NOP");         //��ʱ250ns
    //StepMotorEnable;
    delaynms(1);        
}
void motor_turnon()   // �������
{
    delaynms(1);
     StepMotorEnable;
      delaynms(1); 
      T2CONbits.TON = 1;
      delaynms(30); 
}

void motor_turnoff()  //����رգ����ĵ�
{
//    delaynms(30);
    delaynms(1);
     StepMotorDisable;
     delaynms(1);
      T2CONbits.TON = 0;
     delaynms(30);
}

void motor_chuguan()   //������ܷ����˶�
{
// motor_turnoff();
// delaynms(30);
// motor_turnon();
// delaynms(30);  
    delaynms(1);
   StepMotorEnable;
   T2CONbits.TON = 1;
   delaynms(1);
   StepMotorReversal;    //˳ʱ��
   delaynms(30); 
}

void motor_jinguan()   //������ܷ����˶�
{
// motor_turnoff();
// delaynms(30);
// motor_turnon();
// delaynms(30);
    delaynms(1);
    StepMotorEnable;
    delaynms(1);
    T2CONbits.TON = 1;
    delaynms(1);
    StepMotorForeward;    //��ʱ��
    delaynms(30); 
}
void motor_reset_5()    //��5��λ�����λ
{
    FLAG_AD_TRIGER=1;
    while(1)
    {
      if(FLAG_POS_Reset_triger!=0)  break;
      if(FLAG_POS_Reset==1)
        {
          FLAG_POS_Reset=0;
          break;
        }
     }  
 if(FLAG_POS_Reset_triger==1)
   {
    motor_xto5(); 
    FLAG_POS_Reset_triger=1;
    motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         break;
        }
      }
    motor_turnoff();
   }
  if(FLAG_POS_Reset_triger==2)
   {
    motor_xto5();
       FLAG_POS_Reset_triger=2;
    motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         break;
        }
      }
    motor_turnoff();
   }
   if(FLAG_POS_Reset_triger==3)
    {
    motor_xto5();
    FLAG_POS_Reset_triger=3;
     motor_chuguan(); 
     while(1)
      {
         if(FLAG_POS_Reset==1)
         {
          FLAG_POS_Reset=0;
          FLAG_POS_Reset_triger=0;
          break;
         }
       }
        motor_turnoff();
    }
   
}

void motor_xto5()      //����λ���˶���5��λ�ã�������λ��
{
 RESET_POS_AD=RESET_POS_AD-469;  //60-35=25  25*15=375
 FLAG_POS_Reset_triger=4;
 motor_jinguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         RESET_POS_AD=RESET_POS_AD+469;
         break;
        }
      }
    motor_turnoff();
}
void More_Left()      //����λ���˶���5��λ�ã�������λ��
{
 RESET_POS_AD=RESET_POS_AD-440;  //60-35=25  25*15=375
 FLAG_POS_Reset_triger=4;
  motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+440;
         break;
        }
      }
    motor_turnoff();
}
void Less_Right()      //����λ���˶���5��λ�ã�������λ��
{
 RESET_POS_AD=RESET_POS_AD+100;  //60-35=25  25*15=375
 FLAG_POS_Reset_triger=4;
 motor_jinguan();
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD-100;
         break;
        }
      }
    motor_turnoff();
}
void motor_reset()    //�����λ��1��λ����һ�渴λ
{
              FLAG_AD_TRIGER=1;
           while(1)
           {
             if(FLAG_POS_Reset_triger!=0)  break;
             if(FLAG_POS_Reset==1)
                   {
                     FLAG_POS_Reset=0;
                     break;
                     }
            }  
 if(FLAG_POS_Reset_triger==1)
   {
    motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         break;
        }
      }
    motor_turnoff();
   }
  if(FLAG_POS_Reset_triger==2)
   {
    motor_jinguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         break;
        }
      }
    motor_turnoff();
   }
   if(FLAG_POS_Reset_triger==3)
       {
         FLAG_POS_Reset_triger=0;
         }
   
}
void motor_laohua()
{
  while(1)
    {
    motor_jinguan();
     delaynms(9000);
     motor_chuguan();
     delaynms(9000); 
    }   
}
void motor_move_12()            //��ʼλ���˶��������λ��1-2
{
 RESET_POS_AD=RESET_POS_AD+125;   //66-60=6 
 FLAG_POS_Reset_triger=4;
 motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD-125;
         break;
        }
      }
    motor_turnoff();
}

void motor_move_23()            //����λ���˶�����һ������λ��2-3
{
 RESET_POS_AD=RESET_POS_AD-141;   //60-51=9  9*15=135
 FLAG_POS_Reset_triger=4;
 FLAG_PHOTO_END=0;
 motor_jinguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+141;
         break;
        }
      }
    motor_turnoff();
    delaynms(500);
    uart_to_6755_paizhao(1);
    while(1)
    {
     uart_from_6755move();
     if(FLAG_PHOTO_END==2)
       {
         FLAG_PHOTO_END=0;
           motor_reset_5();  
         break;
       }
          if(FLAG_PHOTO_END==1)
       {
         FLAG_PHOTO_END=0;
         break;
       }
    }
}
void motor_move_34_JCB()            //����λ���˶����ڶ�������λ��3-4
{
 RESET_POS_AD=RESET_POS_AD-393;   //60-39=21  21*15=315
 FLAG_POS_Reset_triger=4;
 motor_jinguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+393;
         break;
        }
      }
    motor_turnoff();
}
void motor_move_43_JCB(unsigned char num)            //�ĺ�λ���˶�������λ��4-3
{
   RESET_POS_AD=RESET_POS_AD-149;   //66-60=6 
 FLAG_POS_Reset_triger=4;
 motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+149;
         break;
        }
      }
    motor_turnoff();
    delaynms(500);
    uart_to_6755_paizhao(num);
      while(1)
    {
     uart_from_6755move();
     if(FLAG_PHOTO_END==2)
       {
         motor_reset_5();
         break;
       }
       if(FLAG_PHOTO_END==1)
       {
         FLAG_PHOTO_END=0;
         break;
       }
    }
}



void motor_move_34(unsigned char num)            //����λ���˶����ڶ�������λ��3-4
{
 RESET_POS_AD=RESET_POS_AD-393;   //60-39=21  21*15=315
 FLAG_POS_Reset_triger=4;
 motor_jinguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+393;
         break;
        }
      }
    motor_turnoff();
    delaynms(500);
    uart_to_6755_paizhao(num);
   
      while(1)
    {    
     uart_from_6755move();
     if(FLAG_PHOTO_END==2)
       {
        // motor_reset_5();
         break;
       }
       if(FLAG_PHOTO_END==1)
       {
         FLAG_PHOTO_END=0;
         break;
       }
    }
}
void motor_move_43_XG()            //�ĺ�λ���˶�������λ��4-3
{
 RESET_POS_AD=RESET_POS_AD-149;   //66-60=6 
 FLAG_POS_Reset_triger=4;
 motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+149;
         break;
        }
      }
    motor_turnoff();
}

void motor_move_45()            //�ĺ�λ���˶�������λ��4-5
{
 RESET_POS_AD=RESET_POS_AD-469;  //60-35=25  25*15=375
 FLAG_POS_Reset_triger=4;
 motor_jinguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+469;
         break;
        }
      }
    motor_turnoff();
}



void motor_paizhao_7times()   
{ 
 unsigned char i;
if(CM == 0xAB)
{ 
  motor_move_43_XG();
  for(i=3;i<=9;i++)
   {
       motor_move_34(i);       
       delaynms(100);
       motor_move_43_XG();
       delaynms(100);
    }
  motor_reset_5();
  StepMotorVS = 0;
}
else if(CM == 0xBA)
{
  for(i=3;i<=9;i++)
   {
       motor_move_43_JCB(i);
       delaynms(100);
       motor_move_34_JCB();
       delaynms(100);
    }
 motor_reset_5();
 StepMotorVS = 0;
}

}


///led on off
void blueled_on()
{
  BLUE_ENable;
  delaynms(100);
  BLUE1_EN;
  delaynms(100);
}

void blueled_off()
{
  BLUE_DISable;
  delaynms(100);
  BLUE1_DIS;
  delaynms(100);
}


///////
void motor_move_54(unsigned char num)            //���λ���˶����ڶ�������λ��5-4
{
 RESET_POS_AD=RESET_POS_AD-469;
 FLAG_POS_Reset_triger=4;
 motor_chuguan(); 
    while(1)
     {
        if(FLAG_POS_Reset==1)
        {
         FLAG_POS_Reset=0;
         FLAG_POS_Reset_triger=0;
         RESET_POS_AD=RESET_POS_AD+469;
         break;
        }
      }
       motor_reset_5();  
    uart_to_6755_paizhao(num);
          while(1)
    {
     uart_from_6755move();
     if(FLAG_PHOTO_END==2)
       {
         motor_reset();
         break;
       }
            if(FLAG_PHOTO_END==1)
       {
         FLAG_PHOTO_END=0;
         break;
       }
    }
}