CC=gcc
TARGET=chash

all: $(TARGET)

$(TARGET): chash.o
	$(CC) -o $(TARGET) chash.o

chash.o: chash.c
	$(CC) -c chash.c

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
