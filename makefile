# Variables Definition
version = gcc -std=gnu99
flags = -g -Wall -Wextra
clean = rm -rf *.o gameoflife keyboardTester

# Main compilation
gameoflife : main.o thread.o keyboard.o gfx.o
	$(version) main.o thread.o keyboard.o gfx.o -lrt -lpthread -lSDL2
main.o : main.c
	$(version) -c main.c $(flags)

# Keyboard Tester
keyboardTester : keyboardTester.c keyboard.o
	$(version) -c keyboardTester.c keyboard.o $(flags) -o keyboardTester

# Thread compilation
thread.o : thread.c thread.h gfx.c gfx.h
	$(version) -c gfx.c thread.c $(flags)

# Thread compilation
gfx.o : gfx.c gfx.h
	$(version) -c gfx.c $(flags)

# Keyboard compilation
keyboard.o : keyboard.c keyboard.h
	$(version) -c keyboard.c $(flags)

# Clean part
clean:
	$(clean)
