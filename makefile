SOURCES = main.c game.c board.c
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -g
OUTPUT = game

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

main.o: main.c game.h
	$(CC) $(CFLAGS) -c -o $@ $<

game.o: game.c game.h board.h
	$(CC) $(CFLAGS) -c -o $@ $<

board.o: board.c board.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: run clean gdb valgrind

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	@rm -rf *.o $(OUTPUT)

gdb: $(OUTPUT)
	gdb ./$(OUTPUT)

valgrind: $(OUTPUT)
	valgrind --leak-check=full --show-leak-kinds=all ./$(OUTPUT)