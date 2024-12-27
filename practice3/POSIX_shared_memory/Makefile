CC = gcc
CFLAGS = -lrt
TARGETS = producer consumer
OBJS = shared_memory_producer.o shared_memory_consumer.o

all: $(TARGETS)

producer: shared_memory_producer.c
	$(CC) -o producer shared_memory_producer.c $(CFLAGS)

consumer: shared_memory_consumer.c
	$(CC) -o consumer shared_memory_consumer.c $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(TARGETS)
