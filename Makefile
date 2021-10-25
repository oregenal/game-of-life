CC=gcc
CFLAGS=-Wall -Wextra -pedantic

game:main.c
	$(CC) $(CFLAGS) -o $@ $<
