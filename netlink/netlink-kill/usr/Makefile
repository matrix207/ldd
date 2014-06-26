CC     = gcc
FLAG   = -Wall
SRC    = mykill.c
OBJ    = $(SRC:.c=.o)
TARGET = mykill

all:$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAG) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJ)
