CC     = gcc
FLAG   = -Wall
SRC    = msgtest.c
OBJ    = $(SRC:.c=.o)
TARGET = msgtest

all:$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAG) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJ)
