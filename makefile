# Variables Definition
version = gcc -std=gnu99
flags = -g -Wall -Wextra -LSDL2 -lpthread
clean = rm -rf *.o crack hash

# Main compilation
gameoflife : main.o
	$(version) main.o -lpthread
main.o : main.c
	$(version) -c main.c $(flags)

# Thread compilation
thread.o : thread.c thread.h  threadprivate.h
	$(version) -c thread.c $(flags) -lcrypt -lpthread

# Clean part
clean:
	$(clean)
