#include "solver.h"
#include "../utils/maze_utils.c"
#include "../utils/file_handler.c"

#define __SOLVER__ 

int should_die(char direction, int row, int column) 
{
    int die_map[][2] = { // { <direction match>, <dimension constraint> }
        { direction == UP   , row <= 0                           },
        { direction == LEFT , column <= 0                        },
        { direction == DOWN , row >= original_maze->height - 1   },
        { direction == RIGHT, column >= original_maze->width - 1 }
    };

    // check for surviveness of the current walker
    for (int i = 0; i < MOVEMENT_AMOUNT; i++)
    {
        if (
            die_map[i][DIRECTION] && (
                die_map[i][LIMIT] || 
                original_maze->map[row + ROW_MOVEMENT[ i ]][column + COL_MOVEMENT[ i ]] != FREE_SPACE
            )
        )
            return SHOULD_DIE;
    }

    return SHOULD_ALIVE;
}

void paint_path(int color, int row, int column) 
{
    // paint the path of the current walker 
    if (in_range(row, 0, original_maze->height) && in_range(column, 0, original_maze->width))
    {
        original_maze->map[row][column] = (char) color;
        print_maze();
    }
}

void take_a_step(Walker current_walker) 
{
    // add another step
    current_walker->steps++;
    
    // using the thread direction, go to the next cell
    switch (current_walker->direction)
    {
        case UP   : current_walker->current_row--; break;
        case LEFT : current_walker->current_col--; break;
        case DOWN : current_walker->current_row++; break;
        case RIGHT: current_walker->current_col++; break;
        default: printf("\nThread direction not allowed\n"); break;
    }
}

int is_at_finish(int row, int column)
{
    // check if the walker finally reach the goal
    for (int i = 0; i < MOVEMENT_AMOUNT; i++)
    {
        if (in_range(row, 1, original_maze->height-1) &&
            in_range(column, 1, original_maze->width-1) &&
            original_maze->map[row + ROW_MOVEMENT[i]][column + COL_MOVEMENT[i]] == GOAL
        )
            return FINISHED;
    }

    return NOT_FINISHED;
}

void *walk_with_threads(void *_walker) 
{    
    // void pointer casting for currrent walker
    Walker current_walker = (Walker) _walker;

    int total_rows = original_maze->height;
    int total_columns = original_maze->width;

    int row = current_walker->current_row;
    int column = current_walker->current_col;

    int is_death = 0;

    pthread_t pid_list[original_maze->height*original_maze->width*2];
    int pid_counter = 0;

    while(!is_death) {

        paint_path(current_walker->color, row, column);

        if(is_at_finish(row, column))
        {
            handle_winner(current_walker, original_maze, THREADS_STRATEGY);
        } 

        int walker_map[][2] = // {<dimension constraint>, <propossed direction>}
        {
            { row != 0,                  UP    },
            { column != 0,               LEFT  },
            { row != total_rows-1,       DOWN  },
            { column != total_columns-1, RIGHT }
        };

        // for every possible direction
        for (int i = 0; i < MOVEMENT_AMOUNT; i++)
        {
            // allow us to walk by w,a,s,d (UP, LEFT, DOWN, RIGHT) into the maze
            int row_shifted = row + ROW_MOVEMENT[i];
            int col_shifted = column + COL_MOVEMENT[i];

            // constraint evaluation, free space in the proposed direction, has a not equal direction
            if (
                walker_map[i][DIM_CONSTRAINT] && 
                original_maze->map[row_shifted][col_shifted] == FREE_SPACE &&
                current_walker->direction != walker_map[i][PROPOSED_DIRECTION]
            )
            {
                pthread_t tid = 
                    solve_with_threads(
                        walker_map[i][PROPOSED_DIRECTION], 
                        row, column, 
                        row_shifted, col_shifted, 
                        current_walker->steps,
                        NO_WAIT
                    );

                pid_list[ pid_counter++ ] = tid;
            }
        }
        
        // check if the thread should die
        is_death = should_die(current_walker->direction, row, column);

        if(!is_death)
        {
            // continue walking in the maze
            take_a_step(current_walker);

            row = current_walker->current_row;
            column = current_walker->current_col;
        }
        else
        {
            for(int tid = 0 ; tid < pid_counter ; tid++)
            {
                pthread_join(pid_list[tid], NULL);
            }
        }
    }
}

void *walk_with_forks(void *_walker) 
{    
    // void pointer casting for currrent walker
    Walker current_walker = (Walker) _walker;

    int total_rows = original_maze->height;
    int total_columns = original_maze->width;

    int row = current_walker->current_row;
    int column = current_walker->current_col;

    int is_death = 0;

    while(!is_death) {
        
        paint_path(current_walker->color, row, column);
        
        if(is_at_finish(row, column))
        {
            handle_winner(current_walker, original_maze, FORKS_STRATEGY);  
        } 

        int walker_map[][2] = // {<dimension constraint>, <propossed direction>}
        {
            { row != 0,                  UP    },
            { column != 0,               LEFT  },
            { row != total_rows-1,       DOWN  },
            { column != total_columns-1, RIGHT }
        };

        // for every possible direction
        for (int i = 0; i < MOVEMENT_AMOUNT; i++)
        {
            // allow us to walk by w,a,s,d (UP, LEFT, DOWN, RIGHT) into the maze
            int row_shifted = row + ROW_MOVEMENT[i];
            int col_shifted = column + COL_MOVEMENT[i];

            // constraint evaluation, free space in the proposed direction, has a not equal direction
            if (
                walker_map[i][DIM_CONSTRAINT] && 
                original_maze->map[row_shifted][col_shifted] == FREE_SPACE &&
                current_walker->direction != walker_map[i][PROPOSED_DIRECTION]
            )
            {
                solve_with_forks(
                    walker_map[i][PROPOSED_DIRECTION], 
                    row, column, 
                    row_shifted, col_shifted, 
                    current_walker->steps,
                    NO_WAIT
                );           
            }
        }
        
        // check if the forkS should die
        is_death = should_die(current_walker->direction, row, column);

        if(!is_death)
        {
            // continue walking in the maze
            take_a_step(current_walker);

            row = current_walker->current_row;
            column = current_walker->current_col;   
        }
        else {  
            while (wait(NULL) > 0);
            exit(0); // notify to the parent process
        }
    }
}

pthread_t solve_with_threads(char direction, int start_row, int start_col, int current_row, int current_column, int steps, int waiting_flag)
{    
    pthread_t child_thread;

    // create the parent walker
    Walker current_walker = build_walker(direction, start_row, start_col, current_row, current_column, steps);

    // create the parent thread, invoking walk function
    int thread_id = pthread_create( &child_thread, NULL, walk_with_threads, (void*) current_walker);

    // wait until his child thread end
    if (waiting_flag == WAIT) {
        pthread_join(child_thread, NULL);
    }

    return child_thread;
}

pid_t solve_with_forks(char direction, int start_row, int start_col, int current_row, int current_column, int steps, int waiting_flag)
{
    // create the parent walker
    Walker current_walker = 
        build_walker(direction, start_row, start_col, current_row, current_column, steps);
    
    pid_t pid = fork();

    if (pid == 0) // child
    {   
        walk_with_forks(current_walker);
    }
    else if (pid > 0 && waiting_flag == WAIT) // parent
    {   
        while (wait(NULL) > 0);
    }
}

void handle_winner(Walker walker, Maze maze, int mode) 
{    
    save_info(walker, maze); 
    record_solution_time(mode);
}

Walker build_walker(char direction, int start_row, int start_col, int current_row, int current_column, int steps)
{
    // set the initial properties
    Walker current_walker = (walker_unit *) malloc(sizeof(walker_unit));

    current_walker->direction = direction;
    current_walker->start_row = start_row;
    current_walker->start_col = start_col;
    current_walker->current_row = current_row;
    current_walker->current_col = current_column;
    current_walker->steps = steps;
    current_walker->color = rand() % COLORS_AMOUNT;

    return current_walker;
}

void print_maze() 
{
    sleep(UPDATE_RATE_IN_SECONDS);
    clear_console();
	
    // for every cell of the maze
    for (int row = 0; row < original_maze->height; row++) 
    {
       for (int column = 0; column < original_maze->width; column++) 
       {
           char current_position = original_maze->map[row][column];
           
           // show element using the current position in the maze
           switch (current_position)
           {
                case WALL: 
                    show_wall(); break;

                case FREE_SPACE: 
                case GOAL: 
                    show_available_space(current_position); break;

                default: show_trace_with_color(current_position); break;
           }
		}
		printf("\n");
	}
	printf("\n");
}
