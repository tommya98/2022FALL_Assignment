CC = gcc
TARGET = testlib
OBJS = main.o bitmap.o debug.o hash.o hex_dump.o list.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o : main.c
	$(CC) -c main.c

bitmap.o : bitmap.c
	$(CC) -c bitmap.c

debug.o : debug.c
	$(CC) -c debug.c

hash.o : hash.c
	$(CC) -c hash.c

hex_dump.o : hex_dump.c
	$(CC) -c hex_dump.c

list.o : list.c
	$(CC) -c list.c

clean :
	rm -f $(OBJS) $(TARGET)