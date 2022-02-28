#pragma once
#include <stddef.h>

long int mystrtol( const char *, char ** , int );
char *mystrchr( const char *, int );
char *mystrrchr( const char *, int  );
size_t mystrspn( const char *, const char * );
size_t mystrcspn( const char *, const char * );
char *mystrpbrk( const char *, const char * );
char *mystrstr( const char * , const char * );
char *mystrtok( char *, const char * );