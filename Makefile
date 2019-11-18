PROG = emulator

SOURCES = $(wildcard src/*.c)
OBJS = ${SOURCES:.c=.o}
INCLUDES = -Iinc

CFLAGS = -O2 -g -Wall

CC = gcc

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

all: $(OBJS)
	$(CC) $^ -o $(PROG) $(CFLAGS) $(INCLUDES)

clean:
	rm $(OBJS) $(PROG)

default: all
