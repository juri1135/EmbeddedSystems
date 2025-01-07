CC = gcc
CFLAGS = -lwiringPi 
OBJS = switchPolling.o
TARGET = switchPolling

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm	-f	*.o
	rm	-f	$(TARGET)