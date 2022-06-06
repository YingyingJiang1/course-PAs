SRC := $(wildcard *.cc)
OBJ := $(patsubst %.cc, %.o, $(SRC))
CC = gcc
CCLINK = g++
CFLAGS = -g -Wall
OUTNAME := main

all: $(OBJ)
	$(CCLINK) $(CFLAGS) $^ -o $(OUTNAME)

$(OBJ): %.o:%.cc
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY:clean
clean:
	rm *.o $(OUTNAME)