CC=gcc
CFLAGS=-Werror -Wall
LIBS=-lm

objects = p1 p2 p3 p4

all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
