#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 104
#define HEIGHT 27
#define BUFFER_SIZE (HEIGHT*WIDTH)
#define FPS 5

#define LIVE '#'
#define DEAD '*'

char stage[BUFFER_SIZE], buffer[BUFFER_SIZE];

void buffer_to_stage_callback(int row, int col)
{
	stage[WIDTH*row+col] = buffer[WIDTH*row+col];
}

void print_stage_callback(int row, int col)
{
	putchar(stage[WIDTH*row+col]);
}

void randomise_stage_callback(int row, int col)
{
	int res = rand() % 2;
	if(res < 0.5) {
		stage[WIDTH*row+col] = DEAD;
	} else {
		stage[WIDTH*row+col] = LIVE;
	}
	putchar(stage[WIDTH*row+col]);
}

void next_stage_generator(int row, int col)
{
	int neighbor = 0, start_row = 0, end_row = 3,
		start_col = 0, end_col = 3;
	if(row == 0)
		start_row = 1;
	if(row == HEIGHT)
		end_row = 2;
	if(col == 0)
		start_col = 1;
	if(col == WIDTH)
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
}

void buffer_traverse(char *stage, char *buffer, 
					void (*callback)(int, int), 
					const int new_line)
{
	(void) stage;
	(void) buffer;

	for(int row = 0; row < HEIGHT; ++row) {
		for(int col = 0; col < WIDTH; ++col) {
			callback(row, col);
		}
		if(new_line)
			printf("\n");
	}
}
void reset_cursor(void)
{
	printf("\033[%dA", HEIGHT);
	printf("\033[%dD", WIDTH);
}

int main(void)
{
	unsigned int randseed = time(NULL);
	srand(randseed);
	buffer_traverse(stage, buffer, randomise_stage_callback, 1);
	reset_cursor();

	usleep(1000 * 1000 / FPS);

	for(;;) {
		buffer_traverse(stage, buffer, next_stage_generator, 1);
		buffer_traverse(stage, buffer, buffer_to_stage_callback, 0);

		usleep(1000 * 1000 / FPS);

		reset_cursor();
	}
	return 0;
}