#include<p18f4580.h>

void delay(int x);

void main(){
	// make an array with hard encoded hex value for anode
	int i;
	int anode_hex[]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	
	// GPIO direction
	TRISC = 0x00;		// output
	
	while(1){
		for(i=9; i>=0; i--){
			PORTC = anode_hex[i];
			delay(200);
		}
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}