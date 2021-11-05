CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic

game:main.c
	$(CC) $(CFLAGS) -o $@ $<
