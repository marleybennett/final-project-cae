PROG = emulator

TESTS_SRC = $(wildcard tests/*.c)
TESTS = $(addprefix test_,\
	$(notdir $(basename $(TESTS_SRC))))

SOURCES = $(wildcard src/*.c)
OBJS = ${SOURCES:.c=.o}
INCLUDES = -Iinc

CFLAGS = -O2 -g -Wall

CC = gcc

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(PROG): $(OBJS)
	$(CC) $^ -o $(PROG) $(CFLAGS) $(INCLUDES)

test_%: tests/%.c $(OBJS)
	echo $^
	$(CC) $^ -o $@ $(CFLAGS) $(INCLUDES)

tests: $(TESTS)
	echo $(TESTS) $(TESTS_SRC)

all: $(PROG)

clean:
	rm $(OBJS) $(PROG) $(TESTS)

default: all
