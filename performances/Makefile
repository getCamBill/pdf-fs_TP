CC=gcc
CFLAGS=-Wextra -Wall# -ansi -pedantic

gateau: mcat

mcat: mcat.c
	$(CC) $(CFLAGS) mcat.c -o mcat

karcher:
	rm -rf mcat

.PHONY: gateau
