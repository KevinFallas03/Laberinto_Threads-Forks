#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define __SOLVER__ 


typedef struct Thread {
   pthread_t id; 
   char  direction;
   int   col_start;
   int   row_start;
   int   steps;
   char  color;
}* Thread;

char* colores[6]={"\x1B[36m", "\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m"};
#define RESET "\x1B[0m"

int total_rows = 10;
int total_columns = 10;

// void create_thread(char, int, int, int);

void *walk( void *thread ){
    struct Thread *t = (struct Thread*)thread;
    for (int row = (*t).row_start; row < total_rows; row++ ) {
       for (int column = (*t).col_start; column < total_columns; column++ ) {
           //FALTA VALIDAR BORDES
           if(original_maze->map[row-1][column] == '/' || original_maze->map[row][column-1] == '/' || original_maze->map[row+1][column] == '/' || original_maze->map[row][column+1] == '/'){
               //SALIO
           }else{ 
                if (original_maze->map[row-1][column] == ' ' && (*t).direction != 'w'){
                   create_thread('w',row,column,(*t).steps);
                }
                if (original_maze->map[row][column-1] == ' ' && (*t).direction != 'a'){
                    create_thread('a',row,column,(*t).steps);
                }
                if (original_maze->map[row+1][column] == ' ' && (*t).direction != 's'){
                    create_thread('s',row,column,(*t).steps);
                }
                if (original_maze->map[row][column+1] == ' ' && (*t).direction != 'd'){
                    create_thread('d',row,column,(*t).steps);
                } 

                if((*t).direction == 'w' && original_maze->map[row-1][column] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                }
                else if((*t).direction == 'a' && original_maze->map[row][column-1] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                } 
                else if((*t).direction == 's' && original_maze->map[row+1][column] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                } 
                else if((*t).direction == 'd' && original_maze->map[row][column+1] != ' '){
                    pthread_join( (*t).id, NULL); //Muere el hilo
                }else{
                    (*t).steps++;

                    if((*t).direction == 'w'){
                        original_maze->map[row-1][column] = (char) (*t).color;
                    }
                    else if((*t).direction == 'a'){
                        original_maze->map[row][column-1] = (char) (*t).color;
                    } 
                    else if((*t).direction == 's'){
                        original_maze->map[row+1][column] = (char) (*t).color;
                    } 
                    else if((*t).direction == 'd'){
                        original_maze->map[row][column+1] = (char) (*t).color;
                    }
                }
           }
       }
    }
}
void create_thread(char direction, int row, int column, int steps){
    pthread_t thread1;
    int  iret1;
    Thread first_thread;
    first_thread->id = thread1;
    first_thread->direction = direction;
    first_thread->row_start = row;
    first_thread->col_start = column;
    first_thread->steps = steps;
    first_thread->color = rand()%6;

    iret1 = pthread_create( &thread1, NULL, walk, (void*) first_thread);
    // pthread_join( (*t).id, NULL);
}

void print_maze(Maze original_maze){
	for (int row = 0; row < total_rows; row++ ) {
       for (int column = 0; column < total_columns; column++ ) {
           if(original_maze->map[row][column] == '*'){
                printf("\u2592");    
           }else if (original_maze->map[row][column] == ' ' || original_maze->map[row][column] == '/'){
               printf("%c", original_maze->map[row][column]);
           }else{
                printf("%s\u2588%s", colores[original_maze->map[row][column]],RESET);
            }
		}
		printf("\n");
	}
	printf("\n");
}
