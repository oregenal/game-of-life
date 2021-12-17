CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

DESTDIR=/usr/local

BIN=game

.PHONY:default release install clean

default:$(BIN)

$(BIN):main.c
	$(CC) $(CFLAGS) -o $@ $<

release:CFLAGS=-std=c11 -O2 -DNDEBUG
release:clean
release:$(BIN)

install:$(BIN)
	mkdir -p $(DESTDIR)/bin
	cp -f $(BIN) $(DESTDIR)/bin
	chmod 755 $(DESTDIR)/bin/$(BIN)

clean:
	rm -f $(BIN)
