#include "file_handler.h"
#include <stdio.h>

void write_file(char *filename, char *content){
    FILE *file;

    file = fopen(filename, "w+");
    fputs(content, file);
   
    fclose(file);
}

char* read_file(char *filename){
    FILE *file;
    file = fopen(filename, "r+");
    
    char *str, c;
    int i = 0;
    str = (char*) malloc(sizeof(char));

    while((c = getc(file)) != EOF)
    {
      str[i] = c;
      i++;
      str = realloc(str, i*sizeof(char));
    }
    
    str[i] = '\0';

    fclose(file);

    return str;
}
void clean_directory(){
    DIR *d;
    struct dirent *dir;
    const char path[50] = "../files/solutions/";
    char path_tmp[50];
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL ){
        if(strcasecmp(dir->d_name, ".") != 0 &
			strcasecmp(dir->d_name, "..") != 0 &
			strcasecmp(dir->d_name, "count.txt") != 0 & 
            strcasecmp(dir->d_name, ".gitignore") != 0){
            strcpy(path_tmp, path);
            strcat(path_tmp, dir->d_name);

            remove(path_tmp);
          }
        }
        closedir(d);
        write_file( "../files/solutions/count.txt", "0");
    }
}

void show_results(){
	DIR *d;
	struct dirent *dir;
	const char path[50] = "../files/solutions/";
	char path_tmp[50];
	d = opendir(path);
	if (d) {
	while ((dir = readdir(d)) != NULL ){
		if(strcasecmp(dir->d_name, ".") != 0 & strcasecmp(dir->d_name, "..") != 0){
			strcpy(path_tmp, path);
			strcat(path_tmp, dir->d_name);

			print_file_content(path_tmp);
			printf("%s", "\n");
		}
	}
    closedir(d);
  }
}

void print_file_content(char *filename){
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    // Read contents from file
    char c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

  	fclose(fptr);
}

void get_last_file(char *filename){
    char path[50] = "../files/solutions/count.txt";
	FILE *fptr;
    fptr = fopen(path, "r");
    if (fptr == NULL)
    {
        printf("Cannot open count file \n");
        exit(0);
    }
	char buffer[20] = "";
    // Read contents from file
    fgets(buffer,20,fptr);

	fclose(fptr);

	//printf("%s", "Count: ");
	//printf("%s", buffer);
	//printf("%s", "\n");
	
	int i = 0;
	sscanf(buffer, "%4d", &i);
	i++;
	sprintf(buffer, "%d", i);

	//printf("%s", "New count: ");
	//printf("%s", buffer);
	//printf("%s", "\n");

	
	write_file(path, buffer);

	strcpy(filename, buffer);
  	
}