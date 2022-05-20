#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "file_processing.h"

typedef struct wav_header {
    char riff_header[4];
    uint32_t wav_size;
    char wave_header[4];
    char fmt_header[4];
    uint32_t fmt_chunk_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t sample_alignment;
    uint16_t bit_depth;
    char data_header[4];
    uint32_t data_bytes;
} wav_header;

int main() {
    char str[51] = {0};
    printf( "input: " );
    fgets( str, 51, stdin );
    str[strlen(str) - 1] = 0;
    char word[51][51] = {{0}};
    char connection[50] = {0};
    int64_t word_count = 0;
    for( int i = 0, l = 0; str[i] != 0; i++ ) {
        if( str[i] == ' ' || str[i] == '-' || str[i] == '.' ) {
            connection[word_count++] = str[i];
            l = 0;
        }
        else{
            word[word_count][l++] = str[i];
        }
    }

    for( int i = 0; i < word_count - 1; i++ ) {
        char *tone = &(word[i][strlen(word[i]) - 1]);
        switch (*tone) {
            case '1':
                *tone = '7';
                break;
            case '2':
                *tone = '1';
                break;
            case '3':
                *tone = '2';
            break;
            case '4':
                if( word[i][strlen(word[i]) - 2] == 'p' || word[i][strlen(word[i]) - 1] == 't' || word[i][strlen(word[i]) - 1] == 'k' ) {
                    *tone = '8';
                }
                if( word[i][strlen(word[i]) - 1] == 'h' ){
                    *tone = '2';
                }
            break;
            case '5':
                *tone = '7';
            break;
            case '7':
                *tone = '3';
            break;
            case '8':
                if( word[i][strlen(word[i]) - 2] == 'p' || word[i][strlen(word[i]) - 1] == 't' || word[i][strlen(word[i]) - 1] == 'k' ) {
                    *tone = '4';
                }
                if( word[i][strlen(word[i]) - 1] == 'h' ){
                    *tone = '3';
                }
            break;
        }
    }
    
    printf( "output: " );
    for( int i = 0; i < word_count; i++ ) {
        printf( "%s. " ,word[i] );
    }
    printf( "%s\n", str );
    for( int i = 0; i < strlen(str); i++ ) {
        if( str[i] == ' ' ) {
            str[i] = '+';
        }
    }

    char command[300] = {0};
    sprintf( command, "%s%s %s", "wget https://hapsing.ithuan.tw/bangtsam?taibun=", str, "-O ./file0.wav");
    system( command );
    for( int i = 0; i < word_count; i++ ) {
        memset( command, 0, 300 );
        sprintf( command, "%s%s %s%d%s", "wget https://hapsing.ithuan.tw/bangtsam?taibun=", word[i], "-O ./file", i + 1, ".wav" );
        system( command );
    }
   
    FILE *output = open_file( "out.wav", "w" );
    FILE *file[word_count + 1];
    wav_header file_header[word_count + 1];

    uint64_t outpute_size = 0;
    for( int i = 0; i <= word_count; i++ ) {
        char file_name[20] = {0};
        sprintf( file_name, "file%d.wav", i );
        file[i] = open_file( file_name, "r" );
        fread( &file_header[i], sizeof( wav_header ), 1, file[i] );
        outpute_size += file_header[i].wav_size;
    }
    file_header[0].wav_size = outpute_size + 36;
    file_header[0].data_bytes = outpute_size;
    fwrite( &file_header[0], sizeof( wav_header ), 1, output );

    uint8_t data = 0;
    for( int i = 1; i <= word_count; i++ ) {
        for( int j = 0 ; j < file_header[i].wav_size; j++ ) {
            fread( &data, sizeof( uint8_t ), 1, file[i] );
            fwrite( &data, sizeof( uint8_t ), 1, output );
        }
    }
    for( int i = 0; i < file_header[0].wav_size; i++ ) {
        fread( &data, sizeof( uint8_t ), 1, file[0] );
        fwrite( &data, sizeof( uint8_t ), 1, output );
    }

    for( int i = 0; i <= word_count; i++ ) {
        fclose( file[i] );
        char command[300] = {0};
        sprintf( command, "rm file%d.wav", i );
        system( command );
    }
    fclose( output );
    return 0;
}