#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>

#include "file_processing.h"

typedef struct{
    int64_t month;
    int64_t date;
    int64_t year;
}DAY;

char country_name[4098] = {0};
char output_file_name[4098] = {0};
DAY start_day = {1, 23, 2020}, end_day = {12, 31, 2021};
void read_option( int argc, char *argv[] ) {
    int l = 0;
    struct option long_options[] = {
        { "country", 1, NULL, 'c' },
        { "start", 1, NULL, 's' },
        { "end", 1, NULL, 'e' },
        { "output", 1, NULL, 'o' },
        { "help", 0, NULL, 'l' }, 
        { 0, 0, 0, 0 }
    };
    char c = 0;
    char str[100] = {0};
    while( ( c = getopt_long( argc, argv, "c:s:e:o:l", long_options, NULL ) ) != -1 ) {
        switch ( c ) {
            case 'c':
                strncpy( country_name, optarg, 4096 );
                if( country_name[strlen(country_name) - 1] == '*' )  {
                    country_name[strlen(country_name) - 1] = 0;
                }
                break;
                break;
            case 's':
                strncpy( str, optarg, 100 );
                sscanf( str, "%ld-%ld-%ld", &start_day.month, &start_day.date, &start_day.year );
                if( start_day.year < 2020 )
                    exit_program("Wrong input");
                if( start_day.year == 2020 && start_day.month == 1 && start_day.date < 23 )
                    exit_program("Wrong input");
                break;
            case 'e':
                strncpy( str, optarg, 100 );
                sscanf( str, "%02ld-%02ld-%04ld", &end_day.month, &end_day.date, &end_day.year );
                if( end_day.year < 2020 )
                    exit_program("Wrong input");
                if( end_day.year == 2020 && end_day.month == 1 && end_day.date < 23 )
                    exit_program("Wrong input");
                break;
            case 'o':
                strncpy( output_file_name, optarg, 4096 );
                break;
            case 'l':
                printf( "fin02:\n" );
                printf( "\t-c, --country: the country name. default: Taiwan\n" );
                printf( "\t-s, --start MM-DD-YYYY: the start date. default: 01-02-2020.\n" );
                printf( "\t-e, --end MM-DD-YYYY: the end date. default: 12-31-2021.\n" );
                printf( "\t-o, --output: output file name. default: output.csv\n" );
                printf( "--help: this message\n" );
                exit(0);
                break;
        }
    }
    return ;
}
int month_count[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main( int argc, char *argv[] ) {
    strcpy( country_name, "Taiwan" );
    strcpy( output_file_name, "output.bmp" );
    

    read_option( argc, argv );
    FILE *output_file = open_file( output_file_name, "w" );
    uint64_t total_people = 0;

    if( start_day.year > end_day.year  ) {
        exit_program( "Wrong input" );
    }
    else {
        if( start_day.month > end_day.month ){
            exit_program( "Wrong input" );
        }
        else {
            if( start_day.date > end_day.date ){
                exit_program( "Wrong input" );
            }
        }
    }


    DAY pre_day = start_day;
    pre_day.date--;
    if( pre_day.date == 0 ) {
        if( pre_day.month == 1 ) {
            pre_day.year--;
            pre_day.month = 12;
            pre_day.date = 31;
        }
        else {
            pre_day.month--;
            pre_day.date = month_count[pre_day.month - 1];
            if(pre_day.year == 2020 && pre_day.month == 2 ) {
                pre_day.date++;
            }
        }
    }
    end_day.date++;
    if( end_day.date > month_count[end_day.month] ) {
        if( end_day.year != 2020 || end_day.month != 2 || end_day.date != 28) {
            end_day.date = 1;
            end_day.month++;
        } 
    }
    if( end_day.month > 12 ) {
        end_day.month = 1;
        end_day.year++;
    }

    char download_command[4097];
    sprintf( download_command, "wget -P ./comfirmed_data_csv https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/%02ld-%02ld-%04ld.csv", pre_day.month, pre_day.date, pre_day.year );
    system( download_command );
    
    char file_position[4097];
    sprintf( file_position, "./comfirmed_data_csv/%02ld-%02ld-%04ld.csv", pre_day.month, pre_day.date, pre_day.year );
    FILE *pre_day_file = open_file( file_position, "r" );

    char one_line[4097];
    int64_t pre_people = 0;
    while( fgets( one_line, 4097, pre_day_file ) ) {
        int64_t tmp_people;
        if( one_line[0] == '\n' )
            break;
        char cur_country[4097] = {0};
        int comma_count = 0;
        int i = 0;
        for( i = 0 ; i < strlen(one_line); i++ ) {
            if( one_line[i] == ',' ) {
                comma_count++;
            }
            if( comma_count == 3)  {
                break;
            }
        }
        sscanf( one_line + i, ",%[^,],%*[^,],%*[^,],%*[^,],%ld,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,]", cur_country, &tmp_people );
        if( cur_country[strlen(cur_country) - 1] == '*' ) {
            cur_country[strlen(cur_country) - 1] = 0;
        }
        
        if( !strcmp( cur_country, country_name ) ) {
            pre_people += tmp_people;
        }
    }
    fclose( pre_day_file );
    uint64_t total_day = 0;

    while(start_day.year != end_day.year || start_day.month != end_day.month || start_day.date != end_day.date) {
        total_day++;
        sprintf( download_command, "wget -P ./comfirmed_data_csv https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/%02ld-%02ld-%04ld.csv", start_day.month, start_day.date, start_day.year );
        system( download_command );

        sprintf( file_position, "./comfirmed_data_csv/%02ld-%02ld-%04ld.csv", start_day.month, start_day.date, start_day.year );
        FILE *cur_day_data_file = fopen( file_position, "r" );
        
        int64_t people = 0;
        char one_line[4097];
        while( fgets( one_line, 4097, cur_day_data_file ) ) {
            int64_t tmp_people;
            if( one_line[0] == '\n' )
                break;
            char cur_country[4097];
            int comma_count = 0;
            int i = 0;
            for( i = 0 ; i < strlen(one_line); i++ ) {
                if( one_line[i] == ',' ) {
                    comma_count++;
                }
                if( comma_count == 3)  {
                    break;
                }
            }
            sscanf( one_line + i, ",%[^,],%*[^,],%*[^,],%*[^,],%ld,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,]", cur_country, &tmp_people );
            if( cur_country[strlen(cur_country) - 1] == '*' ) {
            cur_country[strlen(cur_country) - 1] = 0;
        }
            if( !strcmp( cur_country, country_name ) ) {
                people += tmp_people;
            }
        }
        fclose( cur_day_data_file );

        total_people += people - pre_people;
        fprintf( output_file, "%02ld-%02ld-%04ld,%ld\n", start_day.month, start_day.date, start_day.year, people - pre_people );
        pre_people = people;

        

        start_day.date++;
        if( start_day.date > month_count[start_day.month] ) {
            if( start_day.year != 2020 || start_day.month != 2 || start_day.date != 28) {
                start_day.date = 1;
                start_day.month++;
            }
        }
        if( start_day.month > 12 ) {
            start_day.month = 1;
            start_day.year++;
        }
    }
    fprintf( output_file, "Average ,%lf\n", (double)total_people / (double)total_day );
    fclose( output_file );
    

    return 0;
}