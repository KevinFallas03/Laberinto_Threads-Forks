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
