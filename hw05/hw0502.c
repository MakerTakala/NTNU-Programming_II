#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

#include "file_processing.h"
#include "genre.h"

bool title = false, track = false, artist = false, album = false, year = false, comment = false, genre = false, lists = false, deletes = false;
char modify_title[31] = {0}, modify_artist[31] = {0}, modify_album[31] = {0}, modify_comment[31] = {0}, modify_year[4] = {0};
uint8_t modify_genre = 0, modify_track = 0;
uint8_t option_count = 0;

void read_option( int argc, char *argv[] ) {
    char c = 0;
    int n = 0;
    while( ( c = getopt( argc, argv, "t:T:a:A:y:c:g:ldh" ) ) != -1 ) {
        switch( c ) {
            case 't':
                title = true;
                n = strlen( optarg );
                if( n > 30 ) {
                    printf( "Title only sccept 30 byte!\n" );
                    exit(0);
                }
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalnum( optarg[i] ) && !optarg[i] == ' ' ) {
                        printf( "Wrong Title Name!(Only accept English)\n" );
                        exit(0);
                    }
                }
                strncpy( modify_title, optarg, 30 );
                option_count++;
                break;
            case 'a':
                artist = true;

                n = strlen( optarg );
                if( n > 30 ) {
                    printf( "Artist only sccept 30 byte!\n" );
                    exit(0);
                }
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalnum( optarg[i] ) && !optarg[i] == ' ' ) {
                        printf( "Wrong Artist Name!(Only accept English)\n" );
                        exit(0);
                    }
                }
                strncpy( modify_artist, optarg, 30 );
                option_count++;
                break;
            case 'A':
                album = true;
                n = strlen( optarg );
                if( n > 30 ) {
                    printf( "Album only sccept 30 byte!\n" );
                    exit(0);
                }
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalnum( optarg[i] ) && !optarg[i] == ' ' ) {
                        printf( "Wrong Album Name!(Only accept English)\n" );
                        exit(0);
                    }
                }
                strncpy( modify_album, optarg, 30 );
                option_count++;
                break;
            case 'c':
                comment = true;
                n = strlen( optarg );
                if( n > 30 ) {
                    printf( "Comment only sccept 30 byte!\n" );
                    exit(0);
                }
                if( n >= 29 ) {
                    printf( "[Warning]Because your Comment over 28 byte!, Track data will be invaild!\n" );
                }
                for( int i = 0 ;i < n; i++ ) {
                    if( !isalnum( optarg[i] ) && !optarg[i] == ' '  ) {
                        printf( "Wrong Comment Name!(Only accept English)\n" );
                        exit(0);
                    }
                }
                strncpy( modify_comment, optarg, n );
                option_count++;
                break;
            case 'y':
                year = true;
                n = strlen( optarg );
                if( n > 4 ) {
                    printf( "Wrong Year!\n" );
                    exit(0);
                }
                for( int i = 0 ;i < n; i++ ) {
                    if( !isdigit( optarg[i] ) ) {
                        printf( "Wrong Year Name!\n" );
                        exit(0);
                    }
                    modify_year[4 - n + i] = optarg[i];
                }
                option_count++;
                break;
            case 'g':
                genre = true;
                printf("%s\n", optarg);
                for( int i = 0; i <= 126; i++ ) {
                    if( i == 126 ) {
                        printf( "Wrong Genre Name!\n" );
                        exit(0);
                    }
                    if( !strcmp( optarg, genre_name[i] ) ) {
                        modify_genre = i;
                        break;
                    }
                }
                option_count++;
                break;
            case 'T':
                track = true;
                n = strlen( optarg );
                printf( "[Warning]If your comment over 30 byte, modify this will cover comment.\n" );
                for( int i = 0 ;i < n; i++ ) {
                    if( !isdigit( optarg[i] ) ) {
                        printf( "Wrong Track Number!\n" );
                        exit(0);
                    }
                }
                int64_t tmp_modify_track = strtol( optarg, NULL, 10 );

                if( tmp_modify_track < 0 || 255 < tmp_modify_track ) {
                    printf( "Wrong Year Name!\n" );
                    exit(0);
                }
                modify_track = tmp_modify_track;
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
    char year[4];
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
    if( argc < 3 ) {
        printf( "Need more arg!\n" );
    }
    char file_name[10][4097] = {{0}};
    FILE *file[10] = {NULL};
    int8_t count_file = argc - 3 + ( lists || deletes );
    if( count_file > 10 ) {
        printf( "Too many file!\n" );
        exit(0);
    }
    for( int i = 0; i < count_file; i++ ) {
        strcpy( file_name[i], argv[i + 3 - ( lists || deletes )] );
        file[i] = open_file( file_name[i], "r" );
    }

    
    bool has_ID3[10] = {false};
    
    for( int i = 0; i < count_file; i++ ) {
        struct stat st;
        stat( file_name[i], &st );
        if( st.st_size > 128) {
            fseek( file[i], -128, SEEK_END );
            uint8_t tag[3] = {0};
            fread( &tag, sizeof(uint8_t), 3, file[i] );
            if( !strncmp( tag, "TAG", 3 ) ){
                has_ID3[i] = true;
            }
            fseek( file[i], 0, SEEK_SET );
        }
    }

    ID3v1 ID3_data[10] = {0};
    char tmp_file_name[10][4097] = {{0}};
    FILE *new_file[10] = {NULL};
    for( int i = 0; i < count_file; i++ ) {
        memset( &ID3_data[i], 0, sizeof( ID3v1 ) );
        ID3_data->genre = 126;
        strcpy( tmp_file_name[i], file_name[i] );
        strcat( tmp_file_name[i], ".tmp" );
        new_file[i] = open_file( tmp_file_name[i], "w" );

        struct stat st;
        stat( file_name[i], &st );
        
        if( has_ID3[i] == true ) {
            for( uint64_t j = 0; j < st.st_size - 128; j++ ) {
                uint8_t m = 0;
                fread( &m, sizeof(uint8_t), 1, file[i] );
                fwrite( &m, sizeof(uint8_t), 1, new_file[i] );
            }
            fread( &ID3_data[i], sizeof( ID3v1 ), 1, file[i] );
            
        }
        else {
            for( uint64_t j = 0; j < st.st_size; j++ ) {
                uint8_t m = 0;
                fread( &m, sizeof(uint8_t), 1, file[i] );
                fwrite( &m, sizeof(uint8_t), 1, new_file[i] );
            }
        }
    }


    for( int i = 0 ; i < count_file; i++ ) {
        ID3_data[i].TAG[0] = 'T';
        ID3_data[i].TAG[1] = 'A';
        ID3_data[i].TAG[2] = 'G';
        bool add_new_tag = false;
        if( lists ) {
            printf( "%s:\n", file_name[i] );
            if( !has_ID3[i] ) {
                printf( "  This file doesn't have ID3v1 tag!\n" );
            }
            else {
                printf( "  Title: " );
                if( ID3_data[i].title[0] == 0 ) {
                    printf( "NULL" );
                }
                else {
                    for( int j = 0; j < 30; j++ ) {
                        printf( "%c", ID3_data[i].title[j] );
                    }
                }

                printf( "\n  Artist: " );
                if( ID3_data[i].artist[0] == 0 ) {
                    printf( "NULL" );
                }
                else {
                    for( int j = 0; j < 30; j++ ) {
                        printf( "%c", ID3_data[i].artist[j] );
                    }
                }

                printf( "\n  Album: ");
                if( ID3_data[i].album[0] == 0 ) {
                    printf( "NULL" );
                }
                else {
                    for( int j = 0; j < 30; j++ ) {
                        printf( "%c", ID3_data[i].album[j] );
                    }
                }
                printf( "\n  Year: " );
                if( ID3_data[i].year[0] == 0 ) {
                    printf( "NULL" );
                }
                else {
                    for( int j = 0; j < 4; j++ ) {
                        printf( "%c", ID3_data[i].year[j] );
                    }
                }
                if( ID3_data[i].genre == 126  ) {
                    printf( "\n  Genre: NULL\n" );
                }
                else {
                    printf( "\n  Genre: %s (%hhu)\n", genre_name[ID3_data[i].genre], ID3_data[i].genre );
                }
                
                printf( "  Comment: " );
                if( ID3_data->byte0 == 0 ) {
                    if( ID3_data[i].comment[0] == 0 ) {
                        printf( "NULL" );
                    }
                    else {
                        for( int j = 0; j < 28; j++ ) {
                            printf( "%c", ID3_data[i].comment[j] );
                        }
                    }
                    printf( "\n  Track: %hhu\n", ID3_data[i].track );
                }
                else {
                    if( ID3_data[i].comment[0] == 0 ) {
                        printf( "NULL" );
                    }
                    else {
                        for( int j = 0; j < 30; j++ ) {
                            printf( "%c", ID3_data[i].comment[j] );
                        }
                    }
                    printf( "\n  Track: Comment occupy Track space, so track is invalid.\n" );
                }
            }
        }
        if( title ) {
            strncpy( ID3_data[i].title, modify_title, 30 );
            add_new_tag = true;
        }
        if( track ) {
            ID3_data[i].byte0 = 0;
            ID3_data[i].track = modify_track;
            add_new_tag = true;
        }
        if( artist ) {
            strncpy( ID3_data[i].artist, modify_artist, 30 );
            add_new_tag = true;
        }
        if( album ) {
            strncpy( ID3_data[i].album, modify_album, 30 );
            add_new_tag = true;
        }
        if( year ) {
            strncpy( ID3_data[i].year, modify_year, 4 );
            add_new_tag = true;
        }
        if( comment ) {
            strncpy( ID3_data[i].comment, modify_comment, strlen( modify_comment ) );
            add_new_tag = true;
        }
        if( genre ) {
            ID3_data[i].genre = modify_genre;
            add_new_tag = true;
        }
        if( !deletes && ( has_ID3[i] || add_new_tag ) ) {
            fwrite( &ID3_data[i], sizeof(ID3v1), 1, new_file[i] );
        }
        char command1[4120] = {0};
        strcat( command1, "rm " );
        strcat( command1, file_name[i] );
        system( command1 );
        char command2[4120] = {0};
        strcat( command2, "mv " );
        strcat( command2, tmp_file_name[i] );
        strcat( command2, " " );
        strcat( command2, file_name[i] );
        system( command2 );
    }
    
    for( int i = 0; i < count_file; i++ ) {
        fclose( file[i] );
    }
    return 0;
}