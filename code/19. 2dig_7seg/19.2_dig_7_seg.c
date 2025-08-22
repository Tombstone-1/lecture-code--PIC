#include<p18f4580.h>

#define dir_s1 TRISDbits.RD1
#define dir_s2 TRISDbits.RD0
#define s1 	   PORTDbits.RD1
#define s2     PORTDbits.RD0

void delay(int x);

void main(){
	int i,temp;
	int cathode_hex[]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
 
	TRISC = 0x00;
	dir_s1 = 0;
	dir_s2 = 0;

	while(1){
		for(i=0; i<100; i++){
			s1 = 1;
			s2 = 0;
			temp = i/10;
			PORTC = cathode_hex[temp];
			delay(100);

			s1 = 0;
			s2 = 1;
			temp = i%10;
			PORTC = cathode_hex[temp];
			delay(100);
		}
	}
}

void delay(int x){
	int i,j;
	for(i=0;i<x;i++){
		for(j=0; j<i;j++);
	}
}
		
		
