sudoku: main.cpp sudoku.cpp
	g++ -g -Wall main.cpp sudoku.cpp -o sudoku

functions: sudoku.cpp
	g++ -g -Wall sudoku.cpp -o functions

testmain: testmain.cpp sudoku.cpp
	g++ -g -Wall main.cpp sudoku.cpp -o testmain

clean:
	rm *.o functions
