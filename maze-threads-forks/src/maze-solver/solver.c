#include "solver.h"

#define __SOLVER__ 

int should_die(char direction, int row, int column) 
{
    int result = SHOULD_ALIVE;
    
    // check for surviveness of the current walker
    result =
        (direction == UP    && (row <= 0 || original_maze->map[row - 1][column] != FREE_SPACE)) ||
        (direction == LEFT  && (column <= 0 || original_maze->map[row][column-1] != FREE_SPACE))    || 
        (direction == DOWN  && (row >= original_maze->height - 1 || original_maze->map[row+1][column] != FREE_SPACE)) ||
        (direction == RIGHT && (column >= original_maze->width - 1 || original_maze->map[row][column+1] != FREE_SPACE));

    return result;
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

        // new walker in UP direction
        if (row != 0 && 
            original_maze->map[row-1][column] == FREE_SPACE &&
            current_thread->direction != UP)
            create_thread(UP, row, column, row-1, column, current_thread->steps);

        // new walker in LEFT direction
        if (column != 0 &&
            original_maze->map[row][column-1] == FREE_SPACE &&
            current_thread->direction != LEFT)
        {
            create_thread(LEFT, row, column, row, column-1, current_thread->steps);
        }

        // new walker in DOWN direction
        if (row != total_rows-1 &&
            original_maze->map[row+1][column] == FREE_SPACE &&
            current_thread->direction != DOWN)
        {
            create_thread(DOWN, row, column, row+1, column, current_thread->steps);
        }
        
        // new walker in RIGHT direction
        if (
            column != total_columns-1 && 
            original_maze->map[row][column+1] == FREE_SPACE && 
            current_thread->direction != RIGHT)
        {
            create_thread(RIGHT, row, column, row, column+1, current_thread->steps);
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

void create_thread(char direction, int start_row, int start_col, int current_row, int current_col, int steps)
{    
    pthread_t child_thread;

    // set the initial properties
    Thread parent_thread;
    parent_thread.id = child_thread;
    parent_thread.direction = direction;
    parent_thread.start_row = start_row;
    parent_thread.start_col = start_col;
    parent_thread.current_row = current_row;
    parent_thread.current_col = current_col;
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
