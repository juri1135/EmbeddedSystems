CC = gcc
CFLAGS = -lwiringPi
SRCS = server_receiver.c client_sender.c
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGETS) *.o
