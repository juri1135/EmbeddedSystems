CC = gcc
CFLAGS = -lwiringPi 
OBJS = servomotor_sw.o
TARGET = executable

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm	-f	*.o
	rm	-f	$(TARGET)