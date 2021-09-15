#include "file_handler.h"

void write_file(char *filename, char *content) 
{
   FILE *file;

   file = fopen(filename, "w+");
   fputs(content, file);
   
   fclose(file);
}

char* read_file(char *filename) 
{
    FILE *file;
    file = fopen(filename, "r+");
    
    char *str, c;
    int i = 0;
    str = (char*) malloc(sizeof(char));

    while((c = getc(file)) != EOF)
    {
      str[i] = c;
      i++;
      realloc(str, i*sizeof(char));
    }
    
    str[i] = '\0';

    fclose(file);

    return str;
}


