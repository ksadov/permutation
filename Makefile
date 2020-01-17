CC=g++
CFLAGS=-std=c++17

demo: demo.cpp permutation.cpp
	@$(CC) $(CFLAGS) -o demo.exe demo.cpp permutation.cpp
	@./demo.exe

clean:
	rm demo.exe
