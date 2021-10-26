functions: sudoku.cpp
	g++ -g -Wall sudoku.cpp -o functions

testmain: testmain.cpp sudoku.cpp
	g++ -g -Wall main.cpp sudoku.cpp -o testmain

main: main.cpp sudoku.cpp
	g++ -g -Wall main.cpp sudoku.cpp -o main

clean:
	rm *.o functions
