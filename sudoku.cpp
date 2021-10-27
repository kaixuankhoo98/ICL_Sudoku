#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/* Function to determine if board is full. Takes the board.
Returns true if yes, false if no */
bool is_complete(char board[9][9]) {
  bool flag = true;
  if (board[9][9] == '0') {
    flag = false;
  }
  int row_count, col_count;
  for (row_count = 0; row_count <= 8; row_count++) {
    for (col_count = 0; col_count <= 8; col_count++) {
      char digit;
      if ((digit = board[row_count][col_count]) == '.') {
        flag = false;
      }
    }
  }
  return flag;
}

/* Gets the cell number (1-9) of which 3x3 cell we are in. Takes the row and column index. 
  Returns the cell number from the following array:
  0 1 2
  3 4 5
  6 7 8 */
int get_cell(int rowIndex, int colIndex) {
  int cell;
  cell = ((rowIndex) / 3) * 3 + ((colIndex) / 3);
  return cell;
}

/* Checks if move is legal. Takes indices, a digit, and the board.
  Returns true if legal move, false otherwise. */
bool is_legal(int rowIndex, int colIndex, char digit, char board[9][9]) {
  bool legal = true;
  for (int row = 0; row <= 8; row++) {
    if (board[row][colIndex] == digit)
      legal = false;
  }
  for (int col = 0; col <= 8; col++) {
    if (board[rowIndex][col] == digit)
      legal = false;
  } // Checks if any matching digits in the same row or column

  int cell = get_cell(rowIndex, colIndex);
  for (int cellRows = 3*(cell / 3); cellRows <= 3*(cell / 3) + 2; cellRows++) {
    for (int cellCols = 3*(cell % 3); cellCols <= 3*(cell % 3) + 2; cellCols++) {
      if (board[cellRows][cellCols] == digit)
        legal = false;
    }
  } // Checks if any matching digits in the same 3x3 cell
  return legal;
}

/* Make move function. Takes coordinate, a digit, and the board.
  Returns if the move is legal, and alters the board if legal. */
bool make_move(char const position[3], char digit, char board[9][9]) {
  int rowIndex, colIndex;
  rowIndex = static_cast<int>(position[0]-'A');
  colIndex = static_cast<int>(position[1]-'1');
  
  bool legal = true;
  legal = is_legal(rowIndex, colIndex, digit, board);

  if (legal == true)
    board[rowIndex][colIndex] = digit; // Insert new number into board
  return legal;
}

/* Save board function. Takes input for filename (max 80 chars) and the board.
  Saves the board input to that file. */
bool save_board(char const filename[80], char board[9][9]) {
  ofstream output;
  output.open(filename);
  bool flag = true;

  if (output.fail()) {
        cerr << "Cannot open file" << filename << endl;
        flag = false;
  } 

  for (int row = 0; row <= 8; row++) {
    for (int col = 0; col <= 8; col++) {
      output << board[row][col];
    } output << endl;
  } 
  output.close();

  return flag;
} 

/* Recursive function to solve board. Takes the board.
  Returns true and updates board to solution if there is one.
  Returns false and reflects the original board if no solution is found. */
bool solve_board(char board[9][9]) {
  int rowIndex = 0;
  int colIndex = 0;
  char nextPosition [3];
  
  next_empty(rowIndex, colIndex, board);
  convert_to_string(nextPosition, rowIndex, colIndex);

  // cout << "Next empty position is " << nextPosition << endl;

  if (rowIndex == 9) 
    return true;
  
  for (char tryInput = '1'; tryInput <= '9'; tryInput++) {
    if (make_move(nextPosition, tryInput, board))
      if(solve_board(board) == true) {
        
        return true;
      } // Recursive backtracking checks if next iteration of solve_board returns true
  }
  board[rowIndex][colIndex] = '.'; // Resets the previous number to an empty position
  return false; // Otherwise returns if no legal move is present
}

/* Functions to get the next row and column */
int get_next_row(int row, int col) {
  return row + (col + 1) / 9;
}
int get_next_col(int col) {
  return (col + 1) % 9;
}

/* Uses the get_next_row and get_next_column functions to update
 rowIndex and colIndex to the next empty position on the board */
void next_empty(int& rowIndex, int& colIndex, char board[9][9]) {
  while (board[rowIndex][colIndex] >= '1' && board[rowIndex][colIndex] <= '9') {
    // next_position(rowIndex, colIndex); 
    rowIndex = get_next_row(rowIndex, colIndex);
    colIndex = get_next_col(colIndex);
  }
}

/* Converts the current row and column index into a string that can be used for make_move */
void convert_to_string(char nextPosition[3], int rowIndex, int colIndex) {
  nextPosition[0] = static_cast<char>(rowIndex + static_cast<int>('A'));
  nextPosition[1] = static_cast<char>(colIndex + static_cast<int>('1'));
  nextPosition[2] = '\0';
}

bool solve_board_tester(char board[9][9], int& recursion_counter) {
  int rowIndex = 0;
  int colIndex = 0;
  char nextPosition [3];
  
  next_empty(rowIndex, colIndex, board);
  convert_to_string(nextPosition, rowIndex, colIndex);

  //cout << "Next empty position is " << nextPosition << endl;

  if (rowIndex == 9) 
    return true;
  
  for (char tryInput = '1'; tryInput <= '9'; tryInput++) {
    if (make_move(nextPosition, tryInput, board))
      if(solve_board_tester(board, recursion_counter) == true) {
        
        return true;
      } // Recursive backtracking checks if next iteration of solve_board returns true
  } recursion_counter += 1;
  board[rowIndex][colIndex] = '.'; // Resets the previous number to an empty position
  return false; // Otherwise returns if no legal move is present
}