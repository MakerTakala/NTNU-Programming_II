# Homework01 4104702S 王重鈞

Use "make" to compile all program file

## 1.1 Another Character Encoding
---
Input a string, the program will seem two char as an hex number one by one, then exchange it to binary number and reverse it.
Output the char accroding to reverse number. The string should be end with "00". If there's any invaild input, porgram will print error.

## 1.2 Replacement
---
Input a string, a keyword and a newword, program will repalce keyword in the string to newword.
Then output the original string and new string, the keyword and newword will be marked with color.

## 1.3 My String Library v1
---
mystrtol - convert a string to a long integer.  
long int mystrtol(const char *nptr, char **endptr , int base);

## 1.4 My String Library v2
---
mystrchr - locate character in string and return the first occurrence of the char c in s string.  
char *mystrchr(const char *s, int c);

mystrrchr - locate character in string and return the last occurrence of the char c in s string.  
char *mystrrchr(const char *s, int c);

mystrspn - get length of a prefix substring and return calculates the length (in bytes) of the initial segment of s which consists entirely of bytes in accept.  
size_t mystrspn(const char *s, const char *accept);

mystrcspn - get length of a prefix substring and return calculates the length (in bytes) of the initial segment of s which consists entirely of bytes not in accept.  
size_t mystrcspn(const char *s, const char *reject);

mystrpbrk - search a string for any of a set of bytes and return a pointer to the byte in s that matches one of the bytes in accept, or NULL if no such byte is found.  
char *mystrpbrk(const char *s, const char *accept);

mystrstr - locate a substring and return the first occurrence of the substring needle in the string haystack.  
char *mystrstr(const char *haystack , const char *needle);

strtok - extract tokens from strings and return a pointer to the next token, or NULL if there are no more tokens.  
char *mystrtok(char *str, const char *delim);

## 1.5 Split
---
mystrsplit - split the string and return a 2D vector with splited string.  
int mystrsplit(char ***pppList , int *pCounter , const char *pStr, const char *pSeparator);