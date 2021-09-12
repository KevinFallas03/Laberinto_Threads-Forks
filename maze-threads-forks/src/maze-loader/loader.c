#ifndef FILE
    #include<stdio.h>
#endif

#ifndef free
    #include<stdlib.h>
#endif

#ifndef isdigit
    #include<ctype.h>
#endif

#define __LOADER__ 

typedef struct maze {
    int width;
    int height;
    char **map;
}* Maze;

#define ROW_FINISH_MARK 10

int get_dimensions(Maze maze, char* filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) {return 0;}

    // check for dimension in the first row of the file
    int c, dimension_appeared = 0;
    
    while((c = getc(file)) != ROW_FINISH_MARK) {
        dimension_appeared |= isdigit(c);
    }

    fclose(file);
    file = fopen(filename, "r");

    maze->width = maze->height = 0;

    if (dimension_appeared) 
    {
        // using the first line like "10 10\n"

        short stop_detection = 0;
        // get the width dimension
        while ((c = getc(file)) != ' ')
        {
            if (isdigit(c) && !stop_detection)
            {
                maze->width = maze->width * 10 + (c - '0');
            } else
                stop_detection = 1;
        }

        stop_detection = 0;

        // get the height dimension
        while ((c = getc(file)) != ROW_FINISH_MARK)
        {
            if (isdigit(c) && !stop_detection)
            {
                maze->height = maze->height * 10 + (c - '0');
            }
            else
                stop_detection = 1;
        }

        fclose(file);

        return 1;
    }
    else
    {

        maze->width = maze->height = 0;

        // using the full maze to get their dimensions
        while ((c = getc(file)) != ROW_FINISH_MARK)
        {
            maze->width++;
        }

        maze->width -= 1;
        maze->height = 1;

        while ((c = getc(file)) != EOF)
        {
            maze->height = c == ROW_FINISH_MARK ? maze->height + 1 : maze->height;
        }

        maze->height++;

        fclose(file);

        return 0;
    }
}

Maze load_maze(char *filename)
{
    Maze maze = NULL;
    maze = (Maze) malloc(sizeof(struct maze));
    int is_dimensioned = get_dimensions(maze, filename);

    // allocate enough memory for the maze map
    maze->map = (char**) malloc(sizeof(char*) * maze->height);
    for (int i=0; i<maze->height; i++)
        maze->map[i] = (char*) malloc(sizeof(char) * maze->width);

    FILE *file = fopen(filename, "r");
    if (file) {

        int c, x = 0, y = 0;

        if (is_dimensioned) while ((c = getc(file))!=ROW_FINISH_MARK);

        while((c = getc(file)) != EOF && y != maze->height)
        {
            if (c == ROW_FINISH_MARK) {
                x=0;
                y++;
            }
            else
            {
                maze->map[y][x] = c;
                x++;
            }
        }

        fclose(file);
    }

    return maze;
}

void show_maze(Maze maze)
{
    printf("Width: %d, Height: %d\n", maze->width, maze->height);

    for (int y = 0; y < maze->height; y++)
    {
        for (int x = 0; x < maze->width; x++)
        {
            printf("%c", maze->map[y][x]);
        }

        printf("\n");
    }
}


// int main() {

//     Maze m = load_maze("../../utils/lab2.txt");    
//     show_maze(m);

//     return 0;
// }