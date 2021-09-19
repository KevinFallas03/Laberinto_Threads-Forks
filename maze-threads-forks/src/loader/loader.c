#include "loader.h"

int get_dimensions(Dimension dim, char* filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) { return 0; }

    // check for dimension in the first row of the file
    int c, dimension_appeared = 0;
    
    while((c = getc(file)) != ROW_FINISH_MARK)
        dimension_appeared |= isdigit(c);

    fclose(file);
    file = fopen(filename, "r");

    dim->width = dim->height = 0;

    if (dimension_appeared) 
    {
        // using the first line like "10 10\n"

        short stop_detection = 0;
        // get the width dimension
        while ((c = getc(file)) != ' ')
            if (isdigit(c) && !stop_detection)
                dim->width = dim->width * 10 + (c - '0');
            else
                stop_detection = 1;

        stop_detection = 0;

        // get the height dimension
        while ((c = getc(file)) != ROW_FINISH_MARK)
            if (isdigit(c) && !stop_detection)
                dim->height = dim->height * 10 + (c - '0');
            else
                stop_detection = 1;

        fclose(file);

        return DIMENSION_MODE;
    }
    else
    {
        // using the full maze to get their dimensions
        dim->width = dim->height = 0;
     
        while ((c = getc(file)) != ROW_FINISH_MARK)
            dim->width++;

        dim->width -= 1;
        dim->height = 1;

        while ((c = getc(file)) != EOF)
        {
            dim->height = c == ROW_FINISH_MARK ? dim->height + 1 : dim->height;
        }

        dim->height++;

        fclose(file);

        return MATRIX_MODE;
    }
}

Maze load_maze(char *filename, int strategy_mode)
{    
    Dimension dim = (Dimension) malloc(sizeof(Dimension));
    int is_dimensioned = get_dimensions(dim, filename);

    Maze maze = strategy_mode == THREADS_MODE ? create_maze(dim) : create_shared_maze(dim);
    maze->height = dim->height;
    maze->width = dim->width;

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
            printf("%c", maze->map[y][x]);
    
        printf("\n");
    }
}
