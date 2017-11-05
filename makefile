CC=gcc
CFLAGS=-Werror -Wall
LIBS=-lm

objects = p1 p2 p3 p4 p5 p6 p7 p8 p9

all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
