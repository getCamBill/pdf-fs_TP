CC=gcc
CFLAGS=-Wextra -Wall #-ansi -pedantic

gateau: tac tac2

tac: tac.c 
	$(CC) $(CFLAGS) tac.c -o tac

tac2: tac2.c
	$(CC) $(CFLAGS) tac2.c -o tac2

karcher:
	rm -rf *.o

.PHONY: gateau
