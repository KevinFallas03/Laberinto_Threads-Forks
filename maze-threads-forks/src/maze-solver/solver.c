#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../maze-loader/loader.c"
#include <time.h>
#include <unistd.h>

typedef struct Thread {
   pthread_t id; 
   char  direction;
   int   col_start;
   int   row_start;
   int   steps;
   char  color;
}Thread;

Maze maze = NULL;
// int total_rows = maze->height;
// int total_columns = maze->width;

char* colores[6]={"\x1B[36m", "\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m"};

int total_rows = 10;
int total_columns = 10;

void create_thread(char direction, int row, int column, int steps);

void *walk( void *thread ){
    struct Thread *t = (struct Thread*)thread;
    for (int row = (*t).row_start; row < total_rows; row++ ) {
       for (int column = (*t).col_start; column < total_columns; column++ ) {
           //FALTA VALIDAR BORDES
           if(maze->map[row-1][column] == '/' || maze->map[row][column-1] == '/' || maze->map[row+1][column] == '/' || maze->map[row][column+1] == '/'){
               //SALIO
           }else{ 
                if (maze->map[row-1][column] == ' ' && (*t).direction != 'w'){
                   create_thread('w',row,column,(*t).steps);
                }
                if (maze->map[row][column-1] == ' ' && (*t).direction != 'a'){
                    create_thread('a',row,column,(*t).steps);
                }
                if (maze->map[row+1][column] == ' ' && (*t).direction != 's'){
                    create_thread('s',row,column,(*t).steps);
                }
                if (maze->map[row][column+1] == ' ' && (*t).direction != 'd'){
                    create_thread('d',row,column,(*t).steps);
                } 

                if((*t).direction == 'w' && maze->map[row-1][column] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                }
                else if((*t).direction == 'a' && maze->map[row][column-1] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                } 
                else if((*t).direction == 's' && maze->map[row+1][column] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                } 
                else if((*t).direction == 'd' && maze->map[row][column+1] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                }else{
                    (*t).steps++;

                    if((*t).direction == 'w'){
                        maze->map[row-1][column] = (char) (*t).color;
                    }
                    else if((*t).direction == 'a'){
                        maze->map[row][column-1] = (char) (*t).color;
                    } 
                    else if((*t).direction == 's'){
                        maze->map[row+1][column] = (char) (*t).color;
                    } 
                    else if((*t).direction == 'd'){
                        maze->map[row][column+1] = (char) (*t).color;
                    }
                }
           }
       }
    }
}
void create_thread(char direction, int row, int column, int steps){
    pthread_t thread1;
    int  iret1;
    Thread *first_thread;
    first_thread->id = thread1;
    first_thread->direction = direction;
    first_thread->row_start = row;
    first_thread->col_start = column;
    first_thread->steps = steps;
    first_thread->color = colores[rand()%6];

    iret1 = pthread_create( &thread1, NULL, walk, (void*) first_thread);
    // pthread_join( (*t).id, NULL);
}


