# Variables Definition
version = gcc -std=gnu99
flags = -g -Wall -Wextra
clean = rm -rf *.o gameoflife keyboardTester

# Main compilation
gameoflife : main.o thread.o keyboard.o gfx.o display.o worker.o
	$(version) $^ -o gameoflife -lrt -lpthread -lSDL2

main.o : main.c
	$(version) -c $^ $(flags)

# Keyboard Tester
keyboardTester : keyboardTester.o keyboard.o gfx.o
	$(version) $^ $(flags) -o keyboardTester -lSDL2

keyboardTester.o : keyboardTester.c
	$(version) -c $^ $(flags)

# Thread compilation
thread.o : thread.c thread.h
	$(version) -c $< $(flags)

# Gfx compilation
gfx.o : gfx.c gfx.h
	$(version) -c $< $(flags)

# Keyboard compilation
keyboard.o : keyboard.c keyboard.h
	$(version) -c $< $(flags)

# Display compilation
display.o : display.c display.h
	$(version) -c $< $(flags)

# Worker compilation
worker.o : worker.c worker.h
	$(version) -c $< $(flags)

# Clean part
clean:
	$(clean)
