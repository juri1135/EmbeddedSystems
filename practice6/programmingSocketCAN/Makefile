CC = gcc
CFLAGS = -lwiringPi
SRCS = receiver.c sender.c
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGETS) *.o
