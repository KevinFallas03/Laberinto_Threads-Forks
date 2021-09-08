#include "solver.h"

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

void take_a_step(Thread *thread) 
{
    // add another step
    thread->steps++;
    
    // using the thread direction, go to the next cell
    switch (thread->direction)
    {
        case UP   : thread->current_row--; break;
        case LEFT : thread->current_col--; break;
        case DOWN : thread->current_row++; break;
        case RIGHT: thread->current_col++; break;
        default: printf("\nThread direction not allowed\n"); break;
    }
}

int is_at_finish(int row, int column)
{
    const int at_finish[] = {
        in_range(row, 1, original_maze->height   - 1),
        column > 0 && row < original_maze->width - 1 ,
        in_range(row, 1, original_maze->height   - 1),
        in_range(column, 1, original_maze->width - 1)
    };

    // check if the walker finally reach the goal
    for (int i = 0; i < MOVEMENT_AMOUNT; i++)
    {
        if (at_finish[i] &&
            original_maze->map[row + ROW_MOVEMENT[i]][column + COL_MOVEMENT[i]] == GOAL
        )
            return FINISHED;
    }

    return NOT_FINISHED;
}

void *walk(void *thread) 
{    
    Thread *current_thread = (Thread *) thread;

    int total_rows = original_maze->height;
    int total_columns = original_maze->width;

    int row = current_thread->current_row;
    int column = current_thread->current_col;

    int is_death = 0;

    while(!is_death) {
        
        paint_path(current_thread->color, row, column);
        
        if(is_at_finish(row, column)){
            printf("Congrats");
        } 

        int walker_map[][2] = // {<dimension constraint>, <not allowed direction>}
        {
            { row != 0,                  UP    },
            { column != 0,               LEFT  },
            { row != total_rows-1,       DOWN  },
            { column != total_columns-1, RIGHT }
        };

        // for every possible direction
        for (int i = 0; i < MOVEMENT_AMOUNT; i++)
        {
            // allow US to walk by w,a,s,d (UP, LEFT, DOWN, RIGHT) into the maze
            int row_shifted = row + ROW_MOVEMENT[i];
            int col_shifted = column + COL_MOVEMENT[i];

            if (
                walker_map[i][DIM_CONSTRAINT] && 
                original_maze->map[row_shifted][col_shifted] == FREE_SPACE &&
                current_thread->direction != walker_map[i][PROPOSED_DIRECTION]
            )
            {
                solve_with_threads(walker_map[i][PROPOSED_DIRECTION], row, column, row_shifted, col_shifted, current_thread->steps);
            }
        }
        
        // check if the thread should die
        is_death = should_die(current_thread->direction, row, column);

        if(!is_death)
        {
            // continue walking in the maze
            take_a_step(current_thread);
            row = current_thread->current_row;
            column = current_thread->current_col;
        }
    }
}

void solve_with_threads(char direction, int start_row, int start_col, int current_row, int current_column, int steps)
{    
    pthread_t child_thread;

    // set the initial properties
    Thread parent_thread;
    parent_thread.id = child_thread;
    parent_thread.direction = direction;
    parent_thread.start_row = start_row;
    parent_thread.start_col = start_col;
    parent_thread.current_row = current_row;
    parent_thread.current_col = current_column;
    parent_thread.steps = steps;
    parent_thread.color = rand() % COLORS_AMOUNT;

    // create the parent thread, invoking walk function
    int thread_id = pthread_create( &child_thread, NULL, walk, (void*) &parent_thread);
    
    // wait until his child thread end
    pthread_join(child_thread, NULL);
}

void print_maze() 
{
    sleep(UPDATE_RATE_IN_SECONDS);
    clear_console();
	
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
