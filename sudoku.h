#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>
#include <time.h>

#define SIZE_4x4 4
#define SIZE_9x9 9
#define SIZE_16x16 16

typedef enum {
    EASY,
    MEDIUM,
    HARD
} Difficulty;

typedef struct {
    int size;
    int box_size;
    int** solution;
    int** puzzle;
    int** player_board;
    time_t start_time;
    time_t end_time;
    int moves_count;
} SudokuBoard;

SudokuBoard* create_board(int size);
void free_board(SudokuBoard* board);
void generate_solution(SudokuBoard* board);
void generate_puzzle(SudokuBoard* board, Difficulty difficulty);
bool is_valid_move(SudokuBoard* board, int row, int col, int num);
bool is_board_complete(SudokuBoard* board);
void print_board(SudokuBoard* board);
void start_game_timer(SudokuBoard* board);
void end_game_timer(SudokuBoard* board);
void increment_move_count(SudokuBoard* board);
void print_stats(const SudokuBoard* board);
bool is_valid_placement(int** grid, int size, int box_size, int row, int col, int num);
bool solve_board(SudokuBoard* board, int row, int col);
void solve_puzzle_option(SudokuBoard* board);
bool solve_sudoku_sa(SudokuBoard* board);

#endif
