#ifndef FILE
    #include<stdio.h>
#endif

#ifndef free
    #include<stdlib.h>
#endif

typedef struct maze {
    int width;
    int height;
    char **map;
}* Maze;

#define ROW_FINISH_MARK '/n'

Maze load_maze(char *filename)
{
    Maze maze = NULL;

    FILE *file = fopen(filename, "r");
    if (file) {
        int c;
        
        while((c = getc(file)) != EOF)
            putchar(c);

        fclose(file);
    }

    return maze;
}

// int main() {

//     load_maze("xd.txt");    

//     return 0;
// }