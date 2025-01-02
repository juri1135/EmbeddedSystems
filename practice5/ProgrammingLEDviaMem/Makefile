CC = gcc
CFLAGS = -lwiringPi 
OBJS = led_mmap.o
TARGET = executable

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm	-f	*.o
	rm	-f	$(TARGET)