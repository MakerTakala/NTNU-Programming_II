#include <stdint.h>
#include <stdlib.h>
#include "ip.h"

IPH * iph_init( void ){
	return calloc( sizeof(IPH), 1 );
}

void iph_free( IPH *this){
	free(this);
	return;
}

int iph_encode( void *buffer, const IPH *this ){
	if(!buffer||!this) {
		return 0;
	}
	*((uint8_t*)buffer+0) = 0;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 0)))!=0)<<7;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 0)))!=0)<<6;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 0)))!=0)<<5;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 0)))!=0)<<4;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 1)))!=0)<<3;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 1)))!=0)<<2;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 1)))!=0)<<1;
	*((uint8_t*)buffer+0) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 1)))!=0)<<0;
	*((uint8_t*)buffer+1) = 0;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 2)))!=0)<<7;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 2)))!=0)<<6;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 2)))!=0)<<5;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 2)))!=0)<<4;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 2)))!=0)<<3;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 2)))!=0)<<2;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 2)))!=0)<<1;
	*((uint8_t*)buffer+1) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 2)))!=0)<<0;
	*((uint8_t*)buffer+2) = 0;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 3)))!=0)<<7;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 3)))!=0)<<6;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 3)))!=0)<<5;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 3)))!=0)<<4;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 3)))!=0)<<3;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 3)))!=0)<<2;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 3)))!=0)<<1;
	*((uint8_t*)buffer+2) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 3)))!=0)<<0;
	*((uint8_t*)buffer+3) = 0;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 4)))!=0)<<7;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 4)))!=0)<<6;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 4)))!=0)<<5;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 4)))!=0)<<4;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 4)))!=0)<<3;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 4)))!=0)<<2;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 4)))!=0)<<1;
	*((uint8_t*)buffer+3) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 4)))!=0)<<0;
	*((uint8_t*)buffer+4) = 0;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 5)))!=0)<<7;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 5)))!=0)<<6;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 5)))!=0)<<5;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 5)))!=0)<<4;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 5)))!=0)<<3;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 5)))!=0)<<2;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 5)))!=0)<<1;
	*((uint8_t*)buffer+4) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 5)))!=0)<<0;
	*((uint8_t*)buffer+5) = 0;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 6)))!=0)<<7;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 6)))!=0)<<6;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 6)))!=0)<<5;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 6)))!=0)<<4;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 6)))!=0)<<3;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 6)))!=0)<<2;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 6)))!=0)<<1;
	*((uint8_t*)buffer+5) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 6)))!=0)<<0;
	*((uint8_t*)buffer+6) = 0;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 7)))!=0)<<7;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 7)))!=0)<<6;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 7)))!=0)<<5;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 8)))!=0)<<4;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 8)))!=0)<<3;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 8)))!=0)<<2;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 8)))!=0)<<1;
	*((uint8_t*)buffer+6) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 8)))!=0)<<0;
	*((uint8_t*)buffer+7) = 0;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 8)))!=0)<<7;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 8)))!=0)<<6;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 8)))!=0)<<5;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 9)))!=0)<<4;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 9)))!=0)<<3;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 9)))!=0)<<2;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 9)))!=0)<<1;
	*((uint8_t*)buffer+7) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 9)))!=0)<<0;
	*((uint8_t*)buffer+8) = 0;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 10)))!=0)<<7;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 10)))!=0)<<6;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 10)))!=0)<<5;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 10)))!=0)<<4;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 10)))!=0)<<3;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 10)))!=0)<<2;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 10)))!=0)<<1;
	*((uint8_t*)buffer+8) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 10)))!=0)<<0;
	*((uint8_t*)buffer+9) = 0;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 11)))!=0)<<7;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 11)))!=0)<<6;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 11)))!=0)<<5;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 11)))!=0)<<4;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 11)))!=0)<<3;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 11)))!=0)<<2;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 11)))!=0)<<1;
	*((uint8_t*)buffer+9) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 11)))!=0)<<0;
	*((uint8_t*)buffer+10) = 0;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 12)))!=0)<<7;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 12)))!=0)<<6;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 12)))!=0)<<5;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 12)))!=0)<<4;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 12)))!=0)<<3;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 12)))!=0)<<2;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 12)))!=0)<<1;
	*((uint8_t*)buffer+10) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 12)))!=0)<<0;
	*((uint8_t*)buffer+11) = 0;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 13)))!=0)<<7;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 13)))!=0)<<6;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 13)))!=0)<<5;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 13)))!=0)<<4;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 13)))!=0)<<3;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 13)))!=0)<<2;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 13)))!=0)<<1;
	*((uint8_t*)buffer+11) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 13)))!=0)<<0;
	*((uint8_t*)buffer+12) = 0;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 14)))!=0)<<7;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 14)))!=0)<<6;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 14)))!=0)<<5;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 14)))!=0)<<4;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 14)))!=0)<<3;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 14)))!=0)<<2;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 14)))!=0)<<1;
	*((uint8_t*)buffer+12) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 14)))!=0)<<0;
	*((uint8_t*)buffer+13) = 0;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 15)))!=0)<<7;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 15)))!=0)<<6;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 15)))!=0)<<5;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 15)))!=0)<<4;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 15)))!=0)<<3;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 15)))!=0)<<2;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 15)))!=0)<<1;
	*((uint8_t*)buffer+13) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 15)))!=0)<<0;
	*((uint8_t*)buffer+14) = 0;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 16)))!=0)<<7;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 16)))!=0)<<6;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 16)))!=0)<<5;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 16)))!=0)<<4;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 16)))!=0)<<3;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 16)))!=0)<<2;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 16)))!=0)<<1;
	*((uint8_t*)buffer+14) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 16)))!=0)<<0;
	*((uint8_t*)buffer+15) = 0;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 17)))!=0)<<7;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 17)))!=0)<<6;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 17)))!=0)<<5;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 17)))!=0)<<4;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 17)))!=0)<<3;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 17)))!=0)<<2;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 17)))!=0)<<1;
	*((uint8_t*)buffer+15) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 17)))!=0)<<0;
	*((uint8_t*)buffer+16) = 0;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 18)))!=0)<<7;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 18)))!=0)<<6;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 18)))!=0)<<5;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 18)))!=0)<<4;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 18)))!=0)<<3;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 18)))!=0)<<2;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 18)))!=0)<<1;
	*((uint8_t*)buffer+16) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 18)))!=0)<<0;
	*((uint8_t*)buffer+17) = 0;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 19)))!=0)<<7;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 19)))!=0)<<6;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 19)))!=0)<<5;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 19)))!=0)<<4;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 19)))!=0)<<3;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 19)))!=0)<<2;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 19)))!=0)<<1;
	*((uint8_t*)buffer+17) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 19)))!=0)<<0;
	*((uint8_t*)buffer+18) = 0;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 20)))!=0)<<7;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 20)))!=0)<<6;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 20)))!=0)<<5;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 20)))!=0)<<4;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 20)))!=0)<<3;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 20)))!=0)<<2;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 20)))!=0)<<1;
	*((uint8_t*)buffer+18) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 20)))!=0)<<0;
	*((uint8_t*)buffer+19) = 0;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 21)))!=0)<<7;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 21)))!=0)<<6;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 21)))!=0)<<5;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 21)))!=0)<<4;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 21)))!=0)<<3;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 21)))!=0)<<2;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 21)))!=0)<<1;
	*((uint8_t*)buffer+19) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 21)))!=0)<<0;
	*((uint8_t*)buffer+20) = 0;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 22)))!=0)<<7;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 22)))!=0)<<6;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 22)))!=0)<<5;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 22)))!=0)<<4;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 22)))!=0)<<3;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 22)))!=0)<<2;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 22)))!=0)<<1;
	*((uint8_t*)buffer+20) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 22)))!=0)<<0;
	*((uint8_t*)buffer+21) = 0;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 23)))!=0)<<7;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 23)))!=0)<<6;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 23)))!=0)<<5;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 23)))!=0)<<4;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 23)))!=0)<<3;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 23)))!=0)<<2;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 23)))!=0)<<1;
	*((uint8_t*)buffer+21) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 23)))!=0)<<0;
	*((uint8_t*)buffer+22) = 0;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 24)))!=0)<<7;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 24)))!=0)<<6;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 24)))!=0)<<5;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 24)))!=0)<<4;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 24)))!=0)<<3;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 24)))!=0)<<2;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 24)))!=0)<<1;
	*((uint8_t*)buffer+22) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 24)))!=0)<<0;
	*((uint8_t*)buffer+23) = 0;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<0)&(*((uint8_t*)this + 25)))!=0)<<7;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<1)&(*((uint8_t*)this + 25)))!=0)<<6;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<2)&(*((uint8_t*)this + 25)))!=0)<<5;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<3)&(*((uint8_t*)this + 25)))!=0)<<4;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<4)&(*((uint8_t*)this + 25)))!=0)<<3;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<5)&(*((uint8_t*)this + 25)))!=0)<<2;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<6)&(*((uint8_t*)this + 25)))!=0)<<1;
	*((uint8_t*)buffer+23) += ((((uint8_t)1<<7)&(*((uint8_t*)this + 25)))!=0)<<0;
	return 1;
}

int iph_decode( const void *buffer, IPH *this ){
	if(!buffer||!this) {
		return 0;
	}
	*((uint8_t*)this+0) = 0;
	*((uint8_t*)this+0) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 0)))!=0)<<0;
	*((uint8_t*)this+0) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 0)))!=0)<<1;
	*((uint8_t*)this+0) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 0)))!=0)<<2;
	*((uint8_t*)this+0) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 0)))!=0)<<3;
	*((uint8_t*)this+1) = 0;
	*((uint8_t*)this+1) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 0)))!=0)<<0;
	*((uint8_t*)this+1) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 0)))!=0)<<1;
	*((uint8_t*)this+1) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 0)))!=0)<<2;
	*((uint8_t*)this+1) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 0)))!=0)<<3;
	*((uint8_t*)this+2) = 0;
	*((uint8_t*)this+2) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 1)))!=0)<<0;
	*((uint8_t*)this+2) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 1)))!=0)<<1;
	*((uint8_t*)this+2) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 1)))!=0)<<2;
	*((uint8_t*)this+2) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 1)))!=0)<<3;
	*((uint8_t*)this+2) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 1)))!=0)<<4;
	*((uint8_t*)this+2) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 1)))!=0)<<5;
	*((uint8_t*)this+2) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 1)))!=0)<<6;
	*((uint8_t*)this+2) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 1)))!=0)<<7;
	*((uint8_t*)this+3) = 0;
	*((uint8_t*)this+3) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 2)))!=0)<<0;
	*((uint8_t*)this+3) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 2)))!=0)<<1;
	*((uint8_t*)this+3) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 2)))!=0)<<2;
	*((uint8_t*)this+3) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 2)))!=0)<<3;
	*((uint8_t*)this+3) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 2)))!=0)<<4;
	*((uint8_t*)this+3) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 2)))!=0)<<5;
	*((uint8_t*)this+3) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 2)))!=0)<<6;
	*((uint8_t*)this+3) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 2)))!=0)<<7;
	*((uint8_t*)this+4) = 0;
	*((uint8_t*)this+4) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 3)))!=0)<<0;
	*((uint8_t*)this+4) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 3)))!=0)<<1;
	*((uint8_t*)this+4) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 3)))!=0)<<2;
	*((uint8_t*)this+4) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 3)))!=0)<<3;
	*((uint8_t*)this+4) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 3)))!=0)<<4;
	*((uint8_t*)this+4) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 3)))!=0)<<5;
	*((uint8_t*)this+4) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 3)))!=0)<<6;
	*((uint8_t*)this+4) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 3)))!=0)<<7;
	*((uint8_t*)this+5) = 0;
	*((uint8_t*)this+5) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 4)))!=0)<<0;
	*((uint8_t*)this+5) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 4)))!=0)<<1;
	*((uint8_t*)this+5) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 4)))!=0)<<2;
	*((uint8_t*)this+5) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 4)))!=0)<<3;
	*((uint8_t*)this+5) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 4)))!=0)<<4;
	*((uint8_t*)this+5) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 4)))!=0)<<5;
	*((uint8_t*)this+5) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 4)))!=0)<<6;
	*((uint8_t*)this+5) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 4)))!=0)<<7;
	*((uint8_t*)this+6) = 0;
	*((uint8_t*)this+6) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 5)))!=0)<<0;
	*((uint8_t*)this+6) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 5)))!=0)<<1;
	*((uint8_t*)this+6) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 5)))!=0)<<2;
	*((uint8_t*)this+6) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 5)))!=0)<<3;
	*((uint8_t*)this+6) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 5)))!=0)<<4;
	*((uint8_t*)this+6) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 5)))!=0)<<5;
	*((uint8_t*)this+6) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 5)))!=0)<<6;
	*((uint8_t*)this+6) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 5)))!=0)<<7;
	*((uint8_t*)this+7) = 0;
	*((uint8_t*)this+7) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 6)))!=0)<<0;
	*((uint8_t*)this+7) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 6)))!=0)<<1;
	*((uint8_t*)this+7) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 6)))!=0)<<2;
	*((uint8_t*)this+8) = 0;
	*((uint8_t*)this+8) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 6)))!=0)<<0;
	*((uint8_t*)this+8) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 6)))!=0)<<1;
	*((uint8_t*)this+8) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 6)))!=0)<<2;
	*((uint8_t*)this+8) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 6)))!=0)<<3;
	*((uint8_t*)this+8) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 6)))!=0)<<4;
	*((uint8_t*)this+8) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 7)))!=0)<<5;
	*((uint8_t*)this+8) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 7)))!=0)<<6;
	*((uint8_t*)this+8) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 7)))!=0)<<7;
	*((uint8_t*)this+9) = 0;
	*((uint8_t*)this+9) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 7)))!=0)<<0;
	*((uint8_t*)this+9) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 7)))!=0)<<1;
	*((uint8_t*)this+9) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 7)))!=0)<<2;
	*((uint8_t*)this+9) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 7)))!=0)<<3;
	*((uint8_t*)this+9) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 7)))!=0)<<4;
	*((uint8_t*)this+10) = 0;
	*((uint8_t*)this+10) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 8)))!=0)<<0;
	*((uint8_t*)this+10) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 8)))!=0)<<1;
	*((uint8_t*)this+10) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 8)))!=0)<<2;
	*((uint8_t*)this+10) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 8)))!=0)<<3;
	*((uint8_t*)this+10) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 8)))!=0)<<4;
	*((uint8_t*)this+10) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 8)))!=0)<<5;
	*((uint8_t*)this+10) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 8)))!=0)<<6;
	*((uint8_t*)this+10) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 8)))!=0)<<7;
	*((uint8_t*)this+11) = 0;
	*((uint8_t*)this+11) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 9)))!=0)<<0;
	*((uint8_t*)this+11) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 9)))!=0)<<1;
	*((uint8_t*)this+11) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 9)))!=0)<<2;
	*((uint8_t*)this+11) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 9)))!=0)<<3;
	*((uint8_t*)this+11) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 9)))!=0)<<4;
	*((uint8_t*)this+11) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 9)))!=0)<<5;
	*((uint8_t*)this+11) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 9)))!=0)<<6;
	*((uint8_t*)this+11) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 9)))!=0)<<7;
	*((uint8_t*)this+12) = 0;
	*((uint8_t*)this+12) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 10)))!=0)<<0;
	*((uint8_t*)this+12) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 10)))!=0)<<1;
	*((uint8_t*)this+12) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 10)))!=0)<<2;
	*((uint8_t*)this+12) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 10)))!=0)<<3;
	*((uint8_t*)this+12) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 10)))!=0)<<4;
	*((uint8_t*)this+12) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 10)))!=0)<<5;
	*((uint8_t*)this+12) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 10)))!=0)<<6;
	*((uint8_t*)this+12) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 10)))!=0)<<7;
	*((uint8_t*)this+13) = 0;
	*((uint8_t*)this+13) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 11)))!=0)<<0;
	*((uint8_t*)this+13) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 11)))!=0)<<1;
	*((uint8_t*)this+13) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 11)))!=0)<<2;
	*((uint8_t*)this+13) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 11)))!=0)<<3;
	*((uint8_t*)this+13) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 11)))!=0)<<4;
	*((uint8_t*)this+13) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 11)))!=0)<<5;
	*((uint8_t*)this+13) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 11)))!=0)<<6;
	*((uint8_t*)this+13) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 11)))!=0)<<7;
	*((uint8_t*)this+14) = 0;
	*((uint8_t*)this+14) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 12)))!=0)<<0;
	*((uint8_t*)this+14) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 12)))!=0)<<1;
	*((uint8_t*)this+14) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 12)))!=0)<<2;
	*((uint8_t*)this+14) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 12)))!=0)<<3;
	*((uint8_t*)this+14) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 12)))!=0)<<4;
	*((uint8_t*)this+14) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 12)))!=0)<<5;
	*((uint8_t*)this+14) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 12)))!=0)<<6;
	*((uint8_t*)this+14) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 12)))!=0)<<7;
	*((uint8_t*)this+15) = 0;
	*((uint8_t*)this+15) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 13)))!=0)<<0;
	*((uint8_t*)this+15) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 13)))!=0)<<1;
	*((uint8_t*)this+15) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 13)))!=0)<<2;
	*((uint8_t*)this+15) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 13)))!=0)<<3;
	*((uint8_t*)this+15) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 13)))!=0)<<4;
	*((uint8_t*)this+15) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 13)))!=0)<<5;
	*((uint8_t*)this+15) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 13)))!=0)<<6;
	*((uint8_t*)this+15) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 13)))!=0)<<7;
	*((uint8_t*)this+16) = 0;
	*((uint8_t*)this+16) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 14)))!=0)<<0;
	*((uint8_t*)this+16) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 14)))!=0)<<1;
	*((uint8_t*)this+16) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 14)))!=0)<<2;
	*((uint8_t*)this+16) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 14)))!=0)<<3;
	*((uint8_t*)this+16) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 14)))!=0)<<4;
	*((uint8_t*)this+16) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 14)))!=0)<<5;
	*((uint8_t*)this+16) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 14)))!=0)<<6;
	*((uint8_t*)this+16) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 14)))!=0)<<7;
	*((uint8_t*)this+17) = 0;
	*((uint8_t*)this+17) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 15)))!=0)<<0;
	*((uint8_t*)this+17) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 15)))!=0)<<1;
	*((uint8_t*)this+17) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 15)))!=0)<<2;
	*((uint8_t*)this+17) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 15)))!=0)<<3;
	*((uint8_t*)this+17) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 15)))!=0)<<4;
	*((uint8_t*)this+17) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 15)))!=0)<<5;
	*((uint8_t*)this+17) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 15)))!=0)<<6;
	*((uint8_t*)this+17) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 15)))!=0)<<7;
	*((uint8_t*)this+18) = 0;
	*((uint8_t*)this+18) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 16)))!=0)<<0;
	*((uint8_t*)this+18) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 16)))!=0)<<1;
	*((uint8_t*)this+18) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 16)))!=0)<<2;
	*((uint8_t*)this+18) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 16)))!=0)<<3;
	*((uint8_t*)this+18) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 16)))!=0)<<4;
	*((uint8_t*)this+18) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 16)))!=0)<<5;
	*((uint8_t*)this+18) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 16)))!=0)<<6;
	*((uint8_t*)this+18) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 16)))!=0)<<7;
	*((uint8_t*)this+19) = 0;
	*((uint8_t*)this+19) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 17)))!=0)<<0;
	*((uint8_t*)this+19) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 17)))!=0)<<1;
	*((uint8_t*)this+19) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 17)))!=0)<<2;
	*((uint8_t*)this+19) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 17)))!=0)<<3;
	*((uint8_t*)this+19) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 17)))!=0)<<4;
	*((uint8_t*)this+19) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 17)))!=0)<<5;
	*((uint8_t*)this+19) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 17)))!=0)<<6;
	*((uint8_t*)this+19) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 17)))!=0)<<7;
	*((uint8_t*)this+20) = 0;
	*((uint8_t*)this+20) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 18)))!=0)<<0;
	*((uint8_t*)this+20) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 18)))!=0)<<1;
	*((uint8_t*)this+20) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 18)))!=0)<<2;
	*((uint8_t*)this+20) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 18)))!=0)<<3;
	*((uint8_t*)this+20) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 18)))!=0)<<4;
	*((uint8_t*)this+20) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 18)))!=0)<<5;
	*((uint8_t*)this+20) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 18)))!=0)<<6;
	*((uint8_t*)this+20) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 18)))!=0)<<7;
	*((uint8_t*)this+21) = 0;
	*((uint8_t*)this+21) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 19)))!=0)<<0;
	*((uint8_t*)this+21) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 19)))!=0)<<1;
	*((uint8_t*)this+21) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 19)))!=0)<<2;
	*((uint8_t*)this+21) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 19)))!=0)<<3;
	*((uint8_t*)this+21) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 19)))!=0)<<4;
	*((uint8_t*)this+21) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 19)))!=0)<<5;
	*((uint8_t*)this+21) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 19)))!=0)<<6;
	*((uint8_t*)this+21) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 19)))!=0)<<7;
	*((uint8_t*)this+22) = 0;
	*((uint8_t*)this+22) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 20)))!=0)<<0;
	*((uint8_t*)this+22) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 20)))!=0)<<1;
	*((uint8_t*)this+22) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 20)))!=0)<<2;
	*((uint8_t*)this+22) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 20)))!=0)<<3;
	*((uint8_t*)this+22) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 20)))!=0)<<4;
	*((uint8_t*)this+22) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 20)))!=0)<<5;
	*((uint8_t*)this+22) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 20)))!=0)<<6;
	*((uint8_t*)this+22) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 20)))!=0)<<7;
	*((uint8_t*)this+23) = 0;
	*((uint8_t*)this+23) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 21)))!=0)<<0;
	*((uint8_t*)this+23) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 21)))!=0)<<1;
	*((uint8_t*)this+23) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 21)))!=0)<<2;
	*((uint8_t*)this+23) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 21)))!=0)<<3;
	*((uint8_t*)this+23) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 21)))!=0)<<4;
	*((uint8_t*)this+23) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 21)))!=0)<<5;
	*((uint8_t*)this+23) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 21)))!=0)<<6;
	*((uint8_t*)this+23) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 21)))!=0)<<7;
	*((uint8_t*)this+24) = 0;
	*((uint8_t*)this+24) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 22)))!=0)<<0;
	*((uint8_t*)this+24) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 22)))!=0)<<1;
	*((uint8_t*)this+24) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 22)))!=0)<<2;
	*((uint8_t*)this+24) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 22)))!=0)<<3;
	*((uint8_t*)this+24) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 22)))!=0)<<4;
	*((uint8_t*)this+24) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 22)))!=0)<<5;
	*((uint8_t*)this+24) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 22)))!=0)<<6;
	*((uint8_t*)this+24) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 22)))!=0)<<7;
	*((uint8_t*)this+25) = 0;
	*((uint8_t*)this+25) += ((((uint8_t)1<<7)&(*((uint8_t*)buffer + 23)))!=0)<<0;
	*((uint8_t*)this+25) += ((((uint8_t)1<<6)&(*((uint8_t*)buffer + 23)))!=0)<<1;
	*((uint8_t*)this+25) += ((((uint8_t)1<<5)&(*((uint8_t*)buffer + 23)))!=0)<<2;
	*((uint8_t*)this+25) += ((((uint8_t)1<<4)&(*((uint8_t*)buffer + 23)))!=0)<<3;
	*((uint8_t*)this+25) += ((((uint8_t)1<<3)&(*((uint8_t*)buffer + 23)))!=0)<<4;
	*((uint8_t*)this+25) += ((((uint8_t)1<<2)&(*((uint8_t*)buffer + 23)))!=0)<<5;
	*((uint8_t*)this+25) += ((((uint8_t)1<<1)&(*((uint8_t*)buffer + 23)))!=0)<<6;
	*((uint8_t*)this+25) += ((((uint8_t)1<<0)&(*((uint8_t*)buffer + 23)))!=0)<<7;
	return 1;
}

