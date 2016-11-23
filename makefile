# Variables Definition
version = gcc -std=gnu99
flags = -g -Wall -Wextra -LSDL2
clean = rm -rf *.o crack hash

# Main compilation
gameoflife : main.o
	$(version) main.o -lpthread
main.o : main.c
	$(version) -c main.c $(flags)

# Thread compilation
thread.o : thread.c thread.h  threadprivate.h
	$(version) -c thread.c $(flags) -lpthread

# Keyboard compilation
keyboard.o : keyboard.c keyboard.h
	$(version) -c thread.c $(flags)


# Clean part
clean:
	$(clean)
