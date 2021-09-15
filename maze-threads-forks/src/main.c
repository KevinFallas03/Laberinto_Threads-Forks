#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "loader/loader.c"

Maze original_maze = NULL;
int winners = 0;

#include "solver/solver.c"
#include "utils/file_handler.c"

void run_solver_with_threads(char *filename);
void run_solver_with_forks(char *filename);

void test_write_file();

int main() {

    // set random number seed
    srand(time(NULL));
    
    char* filename = "../files/lab1.txt";

    run_solver_with_threads(filename);
    run_solver_with_forks(filename);
}

void run_solver_with_threads(char *filename) 
{
    original_maze = load_maze(filename);

    solve_with_threads(
        DOWN, // direction (DOWN by default)
        0,    // initial x position
        0,    // initial y position
        0,    // current x position
        0,    // current y position
        0     // initial steps amount
    );
    
    show_stats();
}

void run_solver_with_forks(char *filename)
{
    original_maze = load_maze(filename);

    solve_with_forks(
        DOWN, // direction (DOWN by default)
        0,    // initial x position
        0,    // initial y position
        0,    // current x position
        0,    // current y position
        0     // initial steps amount
    );

    show_stats();
}

void manual_test() 
{
    original_maze->map[0][0] = 1;
    print_maze(original_maze);
    original_maze->map[1][0] = 1;
    print_maze(original_maze);
    original_maze->map[2][0] = 1;
    print_maze(original_maze);
    original_maze->map[2][1] = 2;
    print_maze(original_maze);
    original_maze->map[2][2] = 2;
    print_maze(original_maze);
    original_maze->map[1][2] = 3;
    print_maze(original_maze);
    original_maze->map[0][2] = 3;
    print_maze(original_maze);
    original_maze->map[0][3] = 4;
    print_maze(original_maze);
    original_maze->map[0][4] = 4;
    print_maze(original_maze); 
}

// void test_write_file() 
// {
//     char *filename = "../xd.txt";
//     char *content = "Hola mundo desde C";

//     write_file(filename, content);

//     char *file_content = NULL;
//     file_content = read_file(filename);
//     printf("%sasdasd\n", file_content);
// }