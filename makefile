CC=gcc
CFLAGS=-Wall -g
LIBS=-lncurses

SRC=Show.c
OBJ=$(SRC:.c=.o)
EXEC=Show

# Правило для компиляции программы
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

# Правило для компиляции исходных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Правило для очистки
clean:
	rm -f $(OBJ) $(EXEC)
