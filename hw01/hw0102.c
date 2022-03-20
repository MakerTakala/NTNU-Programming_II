#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
 
#define MAX_LENGTH 4097

void string_tolower( char sentence[] ) {
    for( int i = 0; i < strlen(sentence); i++ ) {
        sentence[i] = tolower(sentence[i]);
    }
    return;
}

void print_sentence( char sentence[], char word[] ) {
    char *sentence_ptr = sentence;
    char *word_ptr = word;
    char *start = strstr( sentence, word );
    while( start ) {
        while( sentence_ptr != start ) {
            printf( "%c", ( *sentence_ptr ) );
            sentence_ptr++;
        }
        for( int i = 0; i < strlen(word); i++ ) {
            printf( "\033[31m%c\033[m", *sentence_ptr );
            sentence_ptr++;
        }
        start = strcasestr( sentence_ptr, word );
    }
    printf( "%s", sentence_ptr );
}

int main() {
    char sentence[MAX_LENGTH] = {0};
    char *sentence_ptr = sentence;
    char new_sentence[MAX_LENGTH] = {0};
    char *new_sentence_ptr = new_sentence;
    char key_word[MAX_LENGTH] = {0};
    char new_word[MAX_LENGTH] = {0};


    printf( "Please enter the string: " );
    fgets( sentence, MAX_LENGTH - 1, stdin );

    printf( "Please enter the keyword: " );
    fgets( key_word, MAX_LENGTH - 1, stdin );
    key_word[strlen( key_word ) - 1] = 0;
    string_tolower(key_word);

    printf( "Please enter the new word: " );
    fgets( new_word, MAX_LENGTH - 1, stdin );
    new_word[strlen(new_word) - 1] = 0;

    
    char *start = strstr( sentence_ptr, key_word );
    while( start ) {
        while( sentence_ptr != start ) {
            *new_sentence_ptr = *sentence_ptr;
            new_sentence_ptr++;
            sentence_ptr++;
        }
        strcat( new_sentence, new_word );
        new_sentence_ptr += strlen(new_word);
        sentence_ptr += strlen(key_word);
        start = strcasestr( sentence_ptr, key_word );
    }
    strcat( new_sentence, sentence_ptr );

    printf("Original:\n");
    print_sentence( sentence, key_word );
    printf("New:\n");
    print_sentence( new_sentence, new_word );

    return 0;
}
