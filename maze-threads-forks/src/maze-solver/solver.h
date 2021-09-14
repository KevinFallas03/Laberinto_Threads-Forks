#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct walker_unit {
   char  direction;
   int   start_col;
   int   start_row;
   int   current_col;
   int   current_row;
   int   steps;
   char  color;
} walker_unit;

typedef struct walker_unit* Walker;

typedef struct Thread {
   pthread_t id; 
   Walker walker;
} Thread;

#define COLORS_AMOUNT 6
#define RESET "\x1B[0m"

char* colores[COLORS_AMOUNT]={
    "\x1B[36m", 
    "\x1B[31m", 
    "\x1B[32m", 
    "\x1B[33m", 
    "\x1B[34m", 
    "\x1B[35m"
};

/* MAZE LOGIC DEFINITIONS */
// maze
#define FREE_SPACE ' '
#define WALL '*'
#define GOAL '/'

// walker
#define UP    'w'
#define LEFT  'a'
#define DOWN  's'
#define RIGHT 'd'

// display
#define clear_console() printf("\e[1;1H\e[2J");
#define show_wall() printf("\u2592");
#define UPDATE_RATE_IN_SECONDS 0

#define show_trace_with_color(index) printf("%s\u2588%s", colores[index], RESET)
#define show_available_space(value) printf("%c", value)

// validation
#define in_range(pos,min,max) pos>=min&&pos<max

// flags
#define SHOULD_DIE   1
#define SHOULD_ALIVE 0

#define FINISHED   1
#define NOT_FINISHED 0

#define DIRECTION 0
#define LIMIT 1

#define DIM_CONSTRAINT 0
#define PROPOSED_DIRECTION 1

// movements
#define MOVEMENT_AMOUNT 4

// w, a, s, d
const int ROW_MOVEMENT[] = {-1, 0, 1,  0};
const int COL_MOVEMENT[] = {0, -1, 0,  1};

/* FUNCTION HEADERS */
void *walk_with_threads( void *walker );
void *walk_with_forks( void *walker );

void solve_with_threads(char direction, int start_row, int start_col, int current_row, int current_column, int steps);
void solve_with_forks(char direction, int start_row, int start_col, int current_row, int current_column, int steps);

void print_maze();
void show_stats();

int  is_at_finish(int row, int column);
void handle_winner(Walker walker);
Walker build_walker(char direction, int start_row, int start_col, int current_row, int current_column, int steps);
