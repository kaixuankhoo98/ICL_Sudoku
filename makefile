functions: sudoku.cpp
	g++ -g -Wall sudoku.cpp -o functions

main: main.cpp sudoku.cpp
	g++ -g -Wall main.cpp sudoku.cpp -o main

clean:
	rm *.o functions
