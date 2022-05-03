#include <stdio.h>
#include <stdlib.h>
#include "ip.h"

int main() {
    IPH object = {
        .version = 0b1111,
        .ihl = 0b1111,
	    .typeofservice = 0b10101010,
	    .totallength = 0b0101010101010101,
	    .identification = 0b1010101010101010,
	    .flags = 0b111,
        .fragmentoffset = 0b0000000000000,
	    .timetolive = 0b10011001,
        .protocol = 0b01100110,
	    .headerchecksum = 0b1111111111111111,
	    .sourceaddress = 0b00000000000000001111111111111111,
	    .destinationaddress = 0b11111111111111110000000000000000,
        .options[0] = 0b11111111,
        .options[1] = 0b00000000,
        .options[2] = 0b11111111,
	    .padding = 0b00000000
    };
    IPH new_object;
    void *buffer = calloc( sizeof(uint8_t), 24 );
    iph_encode( buffer, &object );
    iph_decode( buffer, &new_object );
    printf( "version: %hhu\n", new_object.version);
    printf( "ihl: %hhu\n", new_object.ihl );
    printf( "typeofservice: %hhu\n", new_object.typeofservice );
    printf( "totallength: %hu\n", new_object.totallength );
    printf( "identification: %hu\n", new_object.identification );
    printf( "flags: %hhu\n", new_object.flags );
    printf( "fragmentoffset: %hu\n", new_object.fragmentoffset );
    printf( "timetolive: %hu\n", new_object.timetolive );
    printf( "protocal: %hhu\n", new_object.protocol );
    printf( "headerchecksum: %hu\n", new_object.headerchecksum );
    printf( "sourcesaddress %u\n", new_object.sourceaddress );
    printf( "destinationaddress: %u\n", new_object.destinationaddress );
    printf( "option[0]: %hhu\n", new_object.options[0] );
    printf( "option[1]: %hhu\n", new_object.options[1] );
    printf( "option[2]: %hhu\n", new_object.options[2] );
    printf( "padding: %hhu\n", new_object.padding );

    return 0;
}