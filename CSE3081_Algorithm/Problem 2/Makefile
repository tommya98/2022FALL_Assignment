CC = gcc
TARGET = mp2_20181536
OBJS = main.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o : main.c
	$(CC) -c main.c

clean :
	rm -f $(OBJS) $(TARGET)