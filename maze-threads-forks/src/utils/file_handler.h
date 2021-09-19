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
void clean_directory();
void show_results();
void print_file_content(char *filename);
void get_last_file(char *filename);

void save_info(Walker walker, Maze maze);
void get_stats(Walker walker, char* result);