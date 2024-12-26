# Makefile for monte_carlo

CC = gcc 

CFLAGS = -W -Wall

OBJS = monte_carlo.o rand_between.o

.PHONY: all clean
all: montecarlo

clean:
	-rm -vf monte_carlo *.o

montecarlo: $(OBJS)
	# $(CC) $(CFLAGS) -o $@ $(OBJS) 

montecarlo.o: motecarlo.c rand_between.h
	$(CC) $(CFLAGS) -c -o $@ $<

rand_between.o: rand_between.c rand_between.h
	$(CC) $(CFLAGS) -c -o $@ rand_between.c