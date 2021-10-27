void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

void print_frame(int row);
void print_row(const char* data, int row);

// Functions for questions 1-3
bool is_complete(char board[9][9]);
int get_cell(int rowIndex, int colIndex);
bool is_legal(int rowIndex, int colIndex, char digit, char board[9][9]);
bool make_move(char const position[3], char digit, char board[9][9]);
bool save_board(char const filename[80], char board[9][9]);

// Functions for solve_board 
bool solve_board(char board[9][9]);
void next_position(int& rowIndex, int& colIndex);
void next_empty(int& rowIndex, int& colIndex, char board[9][9]);
void convert_to_string(char nextPosition[3], int rowIndex, int colIndex);
bool solve_board_tester(char board[9][9], int& recursion_counter);