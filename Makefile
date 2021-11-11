CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

game:main.c
	$(CC) $(CFLAGS) -o $@ $<
