#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 20
#define FPS 30

int main(void)
{
	for(;;) {
		for(int row = 0; row < HEIGHT; ++row) {
			for(int col = 0; col < WIDTH; ++col) {
					printf("*");
			}
			printf("\n");
		}

		usleep(1000 * 1000 / FPS);

		printf("\033[%dA", HEIGHT);
		printf("\033[%dD", WIDTH);
	}
	return 0;
}
