SOURCES = main.c game.c board.c bot.c network.c
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -g
OUTPUT = game

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^ -lpthread

main.o: main.c game.h
	$(CC) $(CFLAGS) -c -o $@ $<

game.o: game.c game.h board.h bot.h network.h
	$(CC) $(CFLAGS) -c -o $@ $<

board.o: board.c board.h
	$(CC) $(CFLAGS) -c -o $@ $<

bot.o: bot.c bot.h board.h
	$(CC) $(CFLAGS) -c -o $@ $<

network.o: network.c network.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: run clean gdb valgrind valgrind-client

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	@rm -rf *.o $(OUTPUT)

gdb: $(OUTPUT)
	gdb ./$(OUTPUT)

valgrind: $(OUTPUT)
	valgrind --leak-check=full --show-leak-kinds=all ./$(OUTPUT)

valgrind-client: $(OUTPUT)
	valgrind --leak-check=full --show-leak-kinds=all ./$(OUTPUT) 127.0.0.1 1234