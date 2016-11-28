# Variables Definition
version = gcc -std=gnu99
flags = -g -Wall -Wextra
clean = rm -rf *.o gameoflife keyboardTester

# Main compilation
gameoflife : main.o thread.o keyboard.o gfx.o display.o worker.o
	$(version) main.o thread.o keyboard.o gfx.o display.o worker.o -o gameoflife -lrt -lpthread -lSDL2
main.o : main.c
	$(version) -c main.c $(flags)

# Keyboard Tester
keyboardTester : keyboardTester.o keyboard.o gfx.o
	$(version) keyboardTester.o keyboard.o gfx.o $(flags) -o keyboardTester -lSDL2

keyboardTester.o : keyboardTester.c
	$(version) -c keyboardTester.c $(flags)
# Thread compilation
thread.o : thread.c thread.h gfx.c gfx.h
	$(version) -c gfx.c thread.c $(flags)

# Thread compilation
gfx.o : gfx.c gfx.h
	$(version) -c gfx.c $(flags)

# Keyboard compilation
keyboard.o : keyboard.c keyboard.h
	$(version) -c keyboard.c $(flags)
# Display compilation
display.o : display.c display.h
	$(version) -c display.c $(flags)
# Worker compilation
worker.o : worker.c worker.h
	$(version) -c worker.c $(flags)

# Clean part
clean:
	$(clean)
