#include <stdint.h>
#include <stdlib.h>
#include "ip.h"

IPH * iph_init( void ){
	return malloc( sizeof(IPH) );
}

void iph_free( IPH * this){
	free(this);
	return;
}

int iph_encode( void *buffer, const IPH *this ){
	if(!buffer) {
		return 0;
	}
	return 1;
}

int iph_decode( const void *buffer, IPH *this ){
	if(!buffer) {
		return 0;
	}
	return 1;
}

