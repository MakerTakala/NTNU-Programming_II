#pragma once

#include <stdint.h>
#include <stdio.h>

typedef struct {
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__)) BmpHeader;

FILE *open_file( char question[], char permission[], uint64_t max_name_size );
void stdin_input_string( char *buffer, uint64_t max_name_size );
double ask_angle();
void count_width_height( uint32_t width, uint32_t height, double angle, uint32_t *new_width, uint32_t *new_height );
uint64_t ask( char question[] );
void print_menu();