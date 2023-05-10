PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CC :=gcc
CFLAGS := -Werror -Wall
LDFLAGS := -lrt -lpthread -g
OBJS  := Process1 Process2

all: Process1 Process2

Process1: Process1.c
	$(CC) $(CFLAGS) Process1.c -o Process1 $(LDFLAGS) -DSTART=startProcess1

Process2: Process2.c
	$(CC) $(CFLAGS) Process2.c -o Process2 $(LDFLAGS) -DSTART=startProcess2

run:
	./Process1

clean:
	rm -fr ASS4 $(OBJS)