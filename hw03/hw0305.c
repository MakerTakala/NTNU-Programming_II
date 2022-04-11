#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 4097

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
}__attribute__ ((__packed__)) sBmpHeader;


void string_input_template( char input[] );
void swap( uint8_t *a, uint8_t *b );

int main() {
    printf( "Please enter the image: " );
    char image_name[MAX_STRING_SIZE] = {0};
    string_input_template( image_name );
    FILE *image;
    if( ( image = fopen( image_name, "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    sBmpHeader header;
    fread( &header, sizeof( header ), 1, image );
    if( strncmp( header.bm, "BM", 2 ) || header.bpp != 24 ) {
        printf("Wrong file format!\n");
        exit(0);
    } 
    uint64_t width = header.width, height = header.height;

    printf( "Please enter the puzzle: " );
    char puzzle_name[MAX_STRING_SIZE] = {0};
    string_input_template( puzzle_name );
    FILE *puzzle;
    if( ( puzzle = fopen( puzzle_name, "r" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        exit(0);
    }
    //preprocess

    uint64_t m = 0, n = 0, step = 0;
    char buffer[MAX_STRING_SIZE] = {0};
    fgets( buffer, MAX_STRING_SIZE, puzzle );
    char *end_ptr = NULL;
    m = strtoull( buffer, &end_ptr, 10 );
    if( *end_ptr != ' ' ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    n = strtoull( end_ptr, &end_ptr, 10 );
    if( *end_ptr != '\n' ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    if( width < m || height < n || n <= 0 || m <= 0 ) {
        printf("Wrong input!\n");
        exit(0);
    }
    uint64_t split_width = width / m, split_height = height / n;

    fgets( buffer, MAX_STRING_SIZE, puzzle );
    step = strtoull( buffer, &end_ptr, 10 );
    if( *end_ptr != '\n' ) {
        printf("Wrong input format!\n");
        exit(0);
    }
    if( step == 0 ) {
        printf("Wrong input!\n");
        exit(0);
    }
    
    

    int32_t cur_step_data[n][m];
    int32_t new_step_data[n][m];

    for( int i = 0; i < step; i++ ) {
        char new_image_name[MAX_STRING_SIZE];
        sprintf( new_image_name, "%d.bmp", i );
        FILE *new_image;
        if( ( new_image = fopen( new_image_name, "w" ) ) == NULL ) {
            printf( "File could not be opened!\n" );
            exit(0);
        }
        fwrite( &header, sizeof(header), 1, new_image );

        uint8_t cur_image_data[header.height][header.width][3];
        uint8_t new_image_data[header.height][header.width][3];

        if( i == 0 ) {
            fread( &cur_image_data, 3 * header.width * header.height, 1, image );
            for( int y = n - 1; y >= 0; y-- ) {
                for( int x = 0; x < m; x++ ) {
                    fscanf( puzzle, "%d", &new_step_data[y][x] );
                }
            }
            for( int y = 0; y < n; y++ ) {
                for( int x = 0; x < m; x++ ) {
                    if( new_step_data[y][x] != 0 ) {
                        for( int a = 0; a < split_height; a++ ) {
                            for( int b = 0; b < split_width; b++ ) {
                                new_image_data[y * split_height + a][x * split_width + b][0] = cur_image_data[y * split_height + a][x * split_width + b][0];
                                new_image_data[y * split_height + a][x * split_width + b][1] = cur_image_data[y * split_height + a][x * split_width + b][1];
                                new_image_data[y * split_height + a][x * split_width + b][2] = cur_image_data[y * split_height + a][x * split_width + b][2];
                            }
                        }
                    }
                    else {
                        for( int a = 0; a < split_height; a++ ) {
                            for( int b = 0; b < split_width; b++ ) {
                                new_image_data[y * split_height + a][x * split_width + b][0] = 0xFF;
                                new_image_data[y * split_height + a][x * split_width + b][1] = 0xFF;
                                new_image_data[y * split_height + a][x * split_width + b][2] = 0xFF;
                            }
                        }
                    }
                }
            }
            fclose( image );
        }
        else {
            int32_t swap1_x = -1, swap1_y = -1, swap2_x = -1, swap2_y = -1;
            for( int y = n - 1; y >= 0; y-- ) {
                for( int x = 0; x < m; x++ ) {
                    fscanf( puzzle, "%d", &new_step_data[y][x] );
                }
            }
            for( int y = 0; y < n; y++ ) {
                for( int x = 0; x < m; x++ ) {
                    if( new_step_data[y][x] != cur_step_data[y][x]  ) {
                        if( swap1_x == -1 ) {
                            swap1_y = y;
                            swap1_x = x;
                        }
                        else if( swap2_x == -1 ){
                            swap2_y = y;
                            swap2_x = x;
                        }
                        else {
                            printf("Wrong input!\n");
                            exit(0);
                        }
                    }
                }
            }
            if( swap1_x == -1 || swap2_x == -1 ) {
                printf("Wrong input!\n");
                exit(0);
            }
            
            if( abs( swap1_x - swap2_x ) + abs( swap1_y - swap2_y ) != 1 ) {
                printf("Wrong input!\n");
                exit(0);
            }
            if( cur_step_data[swap1_y][swap1_x] != new_step_data[swap2_y][swap2_x] || new_step_data[swap1_y][swap1_x] != cur_step_data[swap2_y][swap2_x] ) {
                printf("Wrong input!\n");
                exit(0);
            }

            for( int y = 0; y < header.height; y++ ) {
                for( int x = 0; x < header.width; x++ ) {
                    new_image_data[y][x][0] = cur_image_data[y][x][0];
                    new_image_data[y][x][1] = cur_image_data[y][x][1];
                    new_image_data[y][x][2] = cur_image_data[y][x][2];
                }
            }
            for( int a = 0; a < split_height; a++ ) {
                for( int b = 0; b < split_width; b++ ) {
                    swap( &(new_image_data[swap1_y * split_height + a][swap1_x * split_width + b ][0]), &(new_image_data[swap2_y * split_height + a][swap2_x * split_width + b ][0]) );
                    swap( &(new_image_data[swap1_y * split_height + a][swap1_x * split_width + b ][1]), &(new_image_data[swap2_y * split_height + a][swap2_x * split_width + b ][1]) );
                    swap( &(new_image_data[swap1_y * split_height + a][swap1_x * split_width + b ][2]), &(new_image_data[swap2_y * split_height + a][swap2_x * split_width + b ][2]) );
                }
            }
        }

        for( int y = 0; y < n; y++ ) {
            for( int x = 0; x < m; x++ ) {
                cur_step_data[y][x] = new_step_data[y][x];
            }
        }
        for( int y = 0; y < height; y++ ) {
            for( int x = 0; x < width; x++ ) {
                for(int k = 0; k < 3; k++) {
                    cur_image_data[y][x][k] = new_image_data[y][x][k];
                }
            }
        }

        for( int x = 0; x < header.width; x++ ) {
            for( int k = 0; k <= 2; k++ ) {
                new_image_data[k][x][0] = 0;
                new_image_data[k][x][1] = 0;
                new_image_data[k][x][2] = 0xFF;
            }
        }
        for( int y = 0; y < header.width; y++ ) {
            for( int k = 0; k <= 2; k++ ) {
                new_image_data[y][k][0] = 0;
                new_image_data[y][k][1] = 0;
                new_image_data[y][k][2] = 0xFF;
            }
        }
        for( int y = 1; y < n; y++ ) {
            for( int x = 0; x < header.width; x++ ) {
                for( int k = -1; k <= 1; k++ ) {
                    new_image_data[y * split_height + k][x][0] = 0;
                    new_image_data[y * split_height + k][x][1] = 0;
                    new_image_data[y * split_height + k][x][2] = 0xFF;
                }
            }
        }
        for( int x = 1; x < m; x++ ) {
            for( int y = 0; y < header.height; y++ ) {
                for( int k = -1; k <= 1; k++ ) {
                    new_image_data[y][x * split_width + k][0] = 0;
                    new_image_data[y][x * split_width + k][1] = 0;
                    new_image_data[y][x * split_width + k][2] = 0xFF;
                }
            }
        }
        for( int x = 0; x < header.width; x++ ) {
            for( int k = -3; k <= -1 ; k++ ) {
                new_image_data[header.height + k][x][0] = 0;
                new_image_data[header.height + k][x][1] = 0;
                new_image_data[header.height + k][x][2] = 0xFF;
            }
        }
        for( int y = 0; y < header.width; y++ ) {
            for( int k = -3; k <= -1 ; k++ ) {
                new_image_data[y][header.width + k][0] = 0;
                new_image_data[y][header.width + k][1] = 0;
                new_image_data[y][header.width + k][2] = 0xFF;
            }
        }
        fwrite( &new_image_data, 3 * header.width * header.height, 1, new_image );
        fclose( new_image );
    }


    fclose( puzzle );
    return 0;
}

void string_input_template( char input[] ) {
    if( fgets( input, MAX_STRING_SIZE, stdin ) == NULL ) {
        printf( "Error!\n" );
        exit(0);
    }
    if( input[ strlen( input ) - 1 ] == '\n' ) {
        input[ strlen( input ) - 1 ] = 0;
    }
    else {
        uint32_t c = 0;
        while( ( c = fgetc( stdin ) ) != '\n' && c != EOF ){}
    }
}

void swap( uint8_t *a, uint8_t *b ) {
    uint8_t tmp = *a;
    *a = *b;
    *b = tmp;
}