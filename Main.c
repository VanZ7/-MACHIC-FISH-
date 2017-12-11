#include <STC12C5A60S2.H>
#include <stdio.h>
unsigned char flag_uart,flag_on,a,Angle;
void ESinit()
{
	SCON = 0x50;  //REN=1�����н���״̬�����ڹ���ģʽ2     	   
	TMOD |= 0x20;  //��ʱ��������ʽ2       8λ �Զ���װ�ض�ʱ��  ʵ�ֲ�����                
	PCON |= 0x00;  //�����ʲ���                                                    
	TH1 = 0xFd;	  //���ò�����Ϊ9600
	TL1 = 0xFd;   //��ʽ Ϊ  TH1=256-(����ֵ(11.0592M)/32/12/Ԥ���ò�����(9600))
								//TH1=256-(11059200/32/12/9600)=256-3=253  0XFD
	TR1  = 1;     //������ʱ��1                                                      
	ES   = 1;     //�������ж�                  
	EA   = 1;     //�����ж� 
}
void Receive()interrupt 4 
{ 
	RI=0; 
	a=SBUF; 
	flag_uart=1; 
	if(a==1) 
	flag_on=0; 
	else if(a==2) 
	flag_on=1; 
	else 
	flag_on=2; 
} 
void main ()
{
	ESinit();
	if(flag_uart==1) 
	{ 
		flag_uart=0; 
		ES=0; 
		TI=1; 
			switch(flag_on) 
			{ 
				case 0:
				Angle=10;
				printf("1");
				TR0=1; 
				break; 
				case 1:
				Angle=20;
				printf("2"); 
				TR0=0; 
				break; 
				case 2:
				Angle=30;	
				printf("3"); 
				break; 
			} 
		while(!TI); 
		TI=0; 
		ES=1; 
	} 
}