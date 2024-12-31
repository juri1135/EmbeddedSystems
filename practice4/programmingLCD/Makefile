CC = gcc
CFLAGS = -lwiringPi
SRCS = lcd1.c lcd2.c
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGETS) *.o
