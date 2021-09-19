#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h> 

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

#define COLORS_AMOUNT 14

#define RED             "\x1b[31m"
#define LIGHT_RED       "\x1b[91m"
#define GREEN           "\x1b[32m"
#define LIGHT_GREEN     "\x1b[92m"
#define YELLOW          "\x1b[33m"
#define LIGHT_YELLOW    "\x1b[93m"
#define BLUE            "\x1b[34m"
#define LIGHT_BLUE      "\x1b[94m"
#define MAGENTA         "\x1b[35m"
#define LIGHT_MAGENTA   "\x1b[95m"
#define CYAN            "\x1b[36m"
#define LIGHT_CYAN      "\x1b[96m"
#define WHITE           "\x1b[37m"
#define LIGHT_WHITE     "\x1b[97m"

#define RESET           "\x1B[0m"

char* colores[COLORS_AMOUNT]={ 
    RED,
    LIGHT_RED,
    GREEN,
    LIGHT_GREEN,
    YELLOW,
    LIGHT_YELLOW,
    BLUE,
    LIGHT_BLUE,
    MAGENTA,
    LIGHT_MAGENTA,
    CYAN,
    LIGHT_CYAN,
    WHITE,
    LIGHT_WHITE
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
#define UPDATE_RATE_IN_SECONDS 1

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

#define WAIT    0
#define NO_WAIT 1

// movements
#define MOVEMENT_AMOUNT 4

// w, a, s, d
const int ROW_MOVEMENT[] = {-1, 0, 1,  0};
const int COL_MOVEMENT[] = {0, -1, 0,  1};

/* FUNCTION HEADERS */
void *walk_with_threads( void *walker );
void *walk_with_forks( void *walker);

pthread_t solve_with_threads(char direction, int start_row, int start_col, int current_row, int current_column, int steps, int waiting_flag);

//pthread_t solve_with_threads_aux(char direction, int start_row, int start_col, int current_row, int current_column, int steps);

pid_t solve_with_forks(char direction, int start_row, int start_col, int current_row, int current_column, int steps,int waiting_flag);
// pid_t solve_with_forks_aux(char direction, int start_row, int start_col, int current_row, int current_column, int steps);


void print_maze();
void show_stats();

int  is_at_finish(int row, int column);
void handle_winner(Walker walker, Maze maze);
Walker build_walker(char direction, int start_row, int start_col, int current_row, int current_column, int steps);


