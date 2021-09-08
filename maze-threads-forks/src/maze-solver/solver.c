#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define __SOLVER__ 


typedef struct Thread {
   pthread_t id; 
   char  direction;
   int   start_col;
   int   start_row;
   int   current_col;
   int   current_row;
   int   steps;
   char  color;
} Thread;

char* colores[6]={"\x1B[36m", "\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m"};
#define RESET "\x1B[0m"

/* HEADERS */
void *walk( void *thread );
void create_thread( char, int, int , int, int , int );
void print_maze();

int should_die(char direction, int row, int column){
    int to_return = 0;
    if( direction == 'w' && (row <= 0 || original_maze->map[row-1][column] != ' ') ){
        to_return = 1;
    }
    else if( direction == 'a' && (column <= 0 || original_maze->map[row][column-1] != ' ') ){
        to_return = 1;
    } 
    else if(direction == 's' && 
            ( row >= original_maze->height-1 || original_maze->map[row+1][column] != ' ') ){
        to_return = 1;
    } 
    else if(direction == 'd' && 
            ( column >= original_maze->width-1 || original_maze->map[row][column+1] != ' ') ){
        to_return = 1;
    }
    return to_return;
}

void paint_path(int color, int row, int column){
    if(row < original_maze->height && column < original_maze->width && row >= 0 && column >= 0){
        original_maze->map[row][column] = (char) color;
        print_maze();
    }
}

void take_a_step(Thread *thread){
    // printf("Take a step\n");
    thread->steps++;
    if(thread->direction == 'w'){
        thread->current_row--;
    }
    else if(thread->direction == 'a'){
        thread->current_col--;
    } 
    else if(thread->direction == 's'){
        thread->current_row++;
    } 
    else if(thread->direction == 'd'){
        thread->current_col++;
    }
    
}

int is_at_finish(int row, int column){
    if( (row > 0 && row < original_maze->height-1  && original_maze->map[row-1][column] == '/') 
        || (column > 0 && row < original_maze->width-1 && original_maze->map[row][column-1] == '/') 
        || (row < original_maze->height-1 && row > 0 && original_maze->map[row+1][column] == '/') 
        || (column < original_maze->width-1 && column > 0 && original_maze->map[row][column+1] == '/') ){
        return 1;
    }else{
        return 0;
    }
    return 0;
}

void *walk( void *thread ){
    
    int total_rows = original_maze->height;
    int total_columns = original_maze->width;
    
    Thread *current_thread = (Thread*) thread;

    int row = current_thread->current_row;
    int column = current_thread->current_col;

    int is_death = 0;

    while(!is_death){
        paint_path(current_thread->color, row, column);
        if(is_at_finish(row, column)){
            printf("Congrats");
            // break;
        } 
        //CREAR NUEVOS CAMINOS
        if (row != 0 && original_maze->map[row-1][column] == ' ' && (current_thread->direction != 'w')){
            //printf("%c CREAR CAMINO ARRIBA\n",current_thread->direction);
            create_thread('w', row, column, row-1, column, current_thread->steps);
        }
        if (column != 0 && original_maze->map[row][column-1] == ' ' && (current_thread->direction != 'a')){
            //printf("%c CREAR CAMINO IZQUIERDA\n",current_thread->direction);
            create_thread('a', row, column, row, column-1, current_thread->steps);
        }
        if (row != total_rows-1 && original_maze->map[row+1][column] == ' ' && (current_thread->direction != 's')){
            //printf("CREAR CAMINO ABAJO\n");
            create_thread('s', row, column, row+1, column, current_thread->steps);
        }
        if (column != total_columns-1, original_maze->map[row][column+1] == ' ' && (current_thread->direction != 'd')){
            //printf("CREAR CAMINO DERECHA\n");
            create_thread('d', row, column, row, column+1, current_thread->steps);
        } 
        
        is_death = should_die( current_thread->direction, row, column);
        //CAMINA EL HILO ACTUAL
        if(!is_death){
            take_a_step(current_thread);
            row = current_thread->current_row;
            column = current_thread->current_col;
        }
        // printf("%d\n",current_thread->color);
    }
    // printf("%d %d\n",current_thread->current_row,current_thread->current_col);
}

void create_thread(char direction, int start_row, int start_col, int current_row, int current_col, int steps){
    pthread_t thread1;
    int  iret1;

    Thread first_thread;

    first_thread.id = thread1;
    first_thread.direction = direction;
    first_thread.start_row = start_row;
    first_thread.start_col = start_col;
    first_thread.current_row = current_row;
    first_thread.current_col = current_col;
    first_thread.steps = steps;
    first_thread.color = rand()%6;

    iret1 = pthread_create( &thread1, NULL, walk, (void*) &first_thread);
    pthread_join( thread1, NULL);
}

void print_maze(){
    sleep(1);
    printf("\e[1;1H\e[2J");   
	for (int row = 0; row < original_maze->height; row++ ) {
       for (int column = 0; column < original_maze->width; column++ ) {
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
