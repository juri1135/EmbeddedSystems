CC = gcc
CFLAGS = -lwiringPi -lm
OBJS = rt_analyzer.o
TARGET = executable

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm	-f	*.o
	rm	-f	$(TARGET)