CC = gcc
CFLAGS = -Wall -g
TARGET = main

all: $(TARGET)

$(TARGET): main.o filme.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o filme.o

main.o: main.c filme.h
	$(CC) $(CFLAGS) -c main.c

filme.o: filme.c filme.h
	$(CC) $(CFLAGS) -c filme.c

clean:
	rm -f *.o $(TARGET)