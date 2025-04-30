#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

SudokuBoard* create_board(int size) {
    SudokuBoard* board = malloc(sizeof(SudokuBoard));
    if (!board) return NULL;

    board->size = size;
    board->box_size = (int)sqrt(size);
    board->start_time = 0;
    board->end_time = 0;
    board->moves_count = 0;

    board->solution = malloc(size * sizeof(int*));
    board->puzzle = malloc(size * sizeof(int*));
    board->player_board = malloc(size * sizeof(int*));

    if (!board->solution || !board->puzzle || !board->player_board) {
        free_board(board);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        board->solution[i] = calloc(size, sizeof(int));
        board->puzzle[i] = calloc(size, sizeof(int));
        board->player_board[i] = calloc(size, sizeof(int));

        if (!board->solution[i] || !board->puzzle[i] || !board->player_board[i]) {
            free_board(board);
            return NULL;
        }
    }

    return board;
}

void free_board(SudokuBoard* board) {
    if (!board) return;

    for (int i = 0; i < board->size; i++) {
        free(board->solution[i]);
        free(board->puzzle[i]);
        free(board->player_board[i]);
    }
    free(board->solution);
    free(board->puzzle);
    free(board->player_board);
    free(board);
}

bool is_valid_placement(int** grid, int size, int box_size, int row, int col, int num) {
    // Check row for duplicate
    for (int x = 0; x < size; x++) {
        if (grid[row][x] == num) return false;
    }

    // Check column for duplicate
    for (int x = 0; x < size; x++) {
        if (grid[x][col] == num) return false;
    }

    // Check box for duplicate
    int box_start_row = row - row % box_size;
    int box_start_col = col - col % box_size;

    for (int i = 0; i < box_size; i++) {
        for (int j = 0; j < box_size; j++) {
            if (grid[box_start_row + i][box_start_col + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Recursive backtracking solver with random number selection
bool solve_board(SudokuBoard* board, int row, int col) {
    int size = board->size;
    int box_size = board->box_size;

    // Base case: reached end of board
    if (row == size) return true;
    if (col == size) return solve_board(board, row + 1, 0);
    if (board->solution[row][col] != 0) return solve_board(board, row, col + 1);

    // Create and shuffle numbers array for random selection
    int numbers[size];
    for (int i = 0; i < size; i++) numbers[i] = i + 1;

    // Fisher-Yates shuffle
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // Try each number in random order
    for (int i = 0; i < size; i++) {
        int num = numbers[i];
        if (is_valid_placement(board->solution, size, box_size, row, col, num)) {
            board->solution[row][col] = num;
            if (solve_board(board, row, col + 1)) return true;
            board->solution[row][col] = 0; // Backtrack
        }
    }

    return false;
}

void generate_solution(SudokuBoard* board) {
    int size = board->size;
    int box_size = board->box_size;

    // Initialize board with zeros
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board->solution[i][j] = 0;
        }
    }

    // Fill diagonal boxes first (they are independent in Sudoku)
    for (int box = 0; box < size; box += box_size) {
        for (int i = 0; i < box_size; i++) {
            for (int j = 0; j < box_size; j++) {
                int num;
                do {
                    num = (rand() % size) + 1;
                } while (!is_valid_placement(board->solution, size, box_size, box + i, box + j, num));

                board->solution[box + i][box + j] = num;
            }
        }
    }

    // Solve the rest of the board
    if (!solve_board(board, 0, 0)) {
        // If solution fails, try again (should be rare with diagonal pre-fill)
        generate_solution(board);
    }
}

void generate_puzzle(SudokuBoard* board, Difficulty difficulty) {
    int size = board->size;
    int cells_to_remove;

    // Determine how many cells to remove based on size and difficulty
    if (size == 4) {
        switch (difficulty) {
            case EASY:   cells_to_remove = 6; break;
            case MEDIUM: cells_to_remove = 8; break;
            case HARD:   cells_to_remove = 10; break;
        }
    } else {
        switch (difficulty) {
            case EASY:   cells_to_remove = size * size / 2; break;
            case MEDIUM: cells_to_remove = size * size * 2 / 3; break;
            case HARD:   cells_to_remove = size * size * 3 / 4; break;
        }
    }

    // Copy solution to puzzle and player board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board->puzzle[i][j] = board->solution[i][j];
            board->player_board[i][j] = board->solution[i][j];
        }
    }

    // Remove cells randomly
    while (cells_to_remove > 0) {
        int row = rand() % size;
        int col = rand() % size;

        if (board->puzzle[row][col] != 0) {
            board->puzzle[row][col] = 0;
            board->player_board[row][col] = 0;
            cells_to_remove--;
        }
    }
}

bool is_valid_move(SudokuBoard* board, int row, int col, int num) {
    if (num == 0) return true; // Clearing a cell is always valid
    return board->solution[row][col] == num;
}

bool is_board_complete(SudokuBoard* board) {
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->player_board[i][j] != board->solution[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void print_board(SudokuBoard* board) {
    int size = board->size;
    int box_size = board->box_size;

    for (int i = 0; i < size; i++) {
        if (i % box_size == 0 && i != 0) {
            for (int j = 0; j < size + box_size - 1; j++) {
                printf("- ");
            }
            printf("\n");
        }

        for (int j = 0; j < size; j++) {
            if (j % box_size == 0 && j != 0) {
                printf("| ");
            }

            if (board->player_board[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", board->player_board[i][j]);
            }
        }
        printf("\n");
    }
}

void start_game_timer(SudokuBoard* board) {
    board->start_time = time(NULL);
    board->moves_count = 0;
}

void end_game_timer(SudokuBoard* board) {
    board->end_time = time(NULL);
}

void increment_move_count(SudokuBoard* board) {
    board->moves_count++;
}

void print_stats(const SudokuBoard* board) {
    if (board->start_time == 0) {
        printf("Game not started yet.\n");
        return;
    }

    time_t end = board->end_time;
    if (end == 0) end = time(NULL);

    int seconds = (int)difftime(end, board->start_time);
    printf("Time: %02d:%02d\n", seconds / 60, seconds % 60);
    printf("Moves: %d\n", board->moves_count);
}
