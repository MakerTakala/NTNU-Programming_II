#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#include "file_processing.h"
#include "genre.h"

bool title = false, track = false, artist = false, album = false, year = false, comment = false, genre = false, lists = false, deletes = false;
char modify_title[40] = {0}, modify_artist[40] = {0}, modify_album[40] = {0}, modify_comment[40] = {0};
int64_t modify_year = 0, modify_genre = 0, modify_track = 0;
uint8_t option_count = 0;
void remove_optarg_colon(){
    for( int i = 1; i < strlen(optarg) - 2; i++ ) {
        optarg[i - 1] = optarg[i];
    }
    optarg[strlen(optarg) - 1] = 0;
}

void read_option( int argc, char *argv[] ) {
    char c = 0;
    int n = 0;
    while( ( c = getopt( argc, argv, "t:T:a:A:y:c:g:ldh" ) ) != -1 ) {
        switch( c ) {
            case 't':
                title = true;
                remove_optarg_colon();
                n = strlen( optarg );
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalpha( optarg[i] ) ) {
                        printf( "Wrong Title Name!\n" );
                        exit(0);
                    }
                }
                strcpy( modify_title, optarg );
                option_count++;
                break;
            case 'a':
                artist = true;
                remove_optarg_colon();
                n = strlen( optarg );
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalpha( optarg[i] ) ) {
                        printf( "Wrong Title Name!\n" );
                        exit(0);
                    }
                }
                strcpy( modify_artist, optarg );
                option_count++;
                break;
            case 'A':
                album = true;
                remove_optarg_colon();
                n = strlen( optarg );
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalpha( optarg[i] ) ) {
                        printf( "Wrong Title Name!\n" );
                        exit(0);
                    }
                }
                strcpy( modify_album, optarg );
                option_count++;
                break;
            case 'c':
                comment = true;
                remove_optarg_colon();
                n = strlen( optarg );
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalpha( optarg[i] ) ) {
                        printf( "Wrong Title Name!\n" );
                        exit(0);
                    }
                }
                strcpy( modify_comment, optarg );
                option_count++;
                break;
            case 'y':
                year = true;
                remove_optarg_colon();
                n = strlen( optarg );
                if( n > 4 ) {
                    printf( "Wrong Year Name!\n" );
                    exit(0);
                }
                for( int i = 0 ;i < n; i++ ) {
                    if( !isdigit( optarg[i] ) ) {
                        printf( "Wrong Year Name!\n" );
                        exit(0);
                    }
                }
                modify_year = strtol( optarg, NULL, 10 );
                if( modify_year < 0 || 9999 < modify_year ) {
                    printf( "Wrong Year Name!\n" );
                    exit(0);
                }
                option_count++;
                break;
            case 'g':
                genre = true;
                remove_optarg_colon();
                for( int i = 0; i <= 126; i++ ) {
                    if( i == 126 ) {
                        printf( "Wrong Genre Name!\n" );
                        exit(0);
                    }
                    if( !strcmp( genre_name[i], optarg ) ) {
                        modify_genre = i;
                    }
                }
                option_count++;
                break;
            case 'T':
                track = true;
                remove_optarg_colon();
                n = strlen( optarg );
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalpha( optarg[i] ) ) {
                        printf( "Wrong Track Name!\n" );
                        exit(0);
                    }
                }
                modify_track = strtol( optarg, NULL, 10 );
                if( modify_track < 0 || 255 < modify_track ) {
                    printf( "Wrong Year Name!\n" );
                    exit(0);
                }
                option_count++;
                break;
            case 'l':
                lists = true;
                option_count++;
                break;
            case 'd':
                deletes = true;
                option_count++;
                break;
            case 'h':
                printf( "usage: hw0502 -[tTaAycg] \"value\" file1 [file2...]\n" );
                printf( "       hw0502 -d file1 [file2...]\n" );
                printf( "       hw0502 -l file1 [file2...]\n" );
                printf( "       hw0502 -h\n" );
                printf( " -t Modifies a Title tag\n" );
                printf( " -T Modifies a Track tag\n" );
                printf( " -a Modifies an Artist tag\n" );
                printf( " -A Modifies an Album tag\n" );
                printf( " -y Modifies a Year tag\n" );
                printf( " -c Modifies a Comment tag\n" );
                printf( " -g Modifies a Genre tag\n" );
                printf( " -l Lists an ID3 tag\n" );
                printf( " -d Deletes an ID3 tag\n" );
                printf( " -h Displays this help info\n" );
                exit(0);
                option_count++;
                break;
            case '?':
                printf( "Wrong option!\n" );
                exit(0);
                break;
        }
    }
    return ;
}

typedef struct{
    char TAG[3];
    char title[30];
    char artist[30];
    char album[30];
    uint8_t year[4];
    char comment[28];
    uint8_t byte0;
    uint8_t track;
    uint8_t genre;
}__attribute__ ((__packed__)) ID3v1;


int main( int argc, char *argv[] ) {
    read_option( argc, argv );
    if( option_count > 1 ) {
        printf( "Only accept one option.\n" );
        exit(0);
    }
    FILE *file[10] = {NULL};
    uint8_t count_file = argc - 3 + ( lists || deletes );
    if( count_file >= 10 ) {
        printf( "Too Many file!\n" );
        exit(0);
    }
    for( int i = 0; i < count_file; i++ ) {
        file[i] = open_file( argv[i + 3 - ( lists || deletes )], "r+" );
    }
    
    
    



    for( int i = 0; i < count_file; i++ ) {
        fclose( file[i] );
    }
    return 0;
}