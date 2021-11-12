#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 104
#define HEIGHT 27
#define BUFFER_SIZE (HEIGHT*WIDTH)
#define FPS 5

#define LIVE '@'
#define DEAD '-'

void buffer_to_stage_callback(char *stage, char *buffer, int row, int col)
{
	stage[WIDTH*row+col] = buffer[WIDTH*row+col];
}

void print_stage_callback(char *stage, char *buffer, int row, int col)
{
	(void) buffer;

	putchar(stage[WIDTH*row+col]);
}

void randomise_stage_callback(char *stage, char *buffer, int row, int col)
{
	(void) buffer;
	int res = rand() % 2;

	if(res < 0.5) {
		stage[WIDTH*row+col] = DEAD;
	} else {
		stage[WIDTH*row+col] = LIVE;
	}
	putchar(stage[WIDTH*row+col]);

	if(col == WIDTH - 1)
		putchar('\n');
}

void next_stage_generator_callback(char *stage, char *buffer, int row, int col)
{
	int neighbor = 0, start_row = 0, end_row = 3,
		start_col = 0, end_col = 3;
	if(row == 0)
		start_row = 1;
	if(row == HEIGHT - 1)
		end_row = 2;
	if(col == 0)
		start_col = 1;
	if(col == WIDTH - 1)
		end_col = 2;
	for(int i = start_row; i < end_row; ++i) {
		for(int j = start_col; j < end_col; ++j) {
			if(stage[(row+i-1)*WIDTH+col+(j-1)] == LIVE)
				++neighbor;
		}
	}
	if(stage[WIDTH*row+col] == LIVE && 
			(neighbor == 3 + 1 || neighbor == 2 + 1)) {
		buffer[WIDTH*row+col] = LIVE;
	} else if(stage[WIDTH*row+col] == DEAD && neighbor == 3) {
		buffer[WIDTH*row+col] = LIVE;
	} else {
		buffer[WIDTH*row+col] = DEAD;
	}
	putchar(buffer[WIDTH*row+col]);

	if(col == WIDTH - 1)
		putchar('\n');
}

void buffer_traverse(char *stage, char *buffer, 
					void (*callback)(char *, char *, int, int))
{
	for(int row = 0; row < HEIGHT; ++row) {
		for(int col = 0; col < WIDTH; ++col) {
			callback(stage, buffer, row, col);
		}
	}
}

void reset_cursor(void)
{
	printf("\033[%dA", HEIGHT);
	printf("\033[%dD", WIDTH);
}

int main(void)
{
	char stage[BUFFER_SIZE], buffer[BUFFER_SIZE];
	unsigned int randseed = time(NULL);
	srand(randseed);

	buffer_traverse(stage, buffer, randomise_stage_callback);

	for(;;) {
		usleep(1000 * 1000 / FPS);

		reset_cursor();

		buffer_traverse(stage, buffer, next_stage_generator_callback);
		buffer_traverse(stage, buffer, buffer_to_stage_callback);
	}
	return 0;
}
