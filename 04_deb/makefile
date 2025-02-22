TARGET = calculator

CC = gcc

CFLAGS = -g -Wall

SRC = calculator.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

debug: CFLAGS += -DDEBUG
debug: clean $(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)
