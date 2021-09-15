#ifndef printf
    #include <stdio.h>
#endif

#ifndef FILE
    #include<stdio.h>
#endif

#ifndef strcat
    #include<string.h>
#endif

#define BUFFER_MAX_SIZE 255

char* read_file(char *filename);
void write_file(char *filename, char *content);