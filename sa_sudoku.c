#include "sa_sudoku.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static int calculate_cost(SudokuBoard* board) {
    int cost = 0;
    int size = board->size;
    
    for (int row = 0; row < size; row++) {
        for (int col1 = 0; col1 < size; col1++) {
            for (int col2 = col1 + 1; col2 < size; col2++) {
                if (board->player_board[row][col1] != 0 && 
                    board->player_board[row][col1] == board->player_board[row][col2]) {
                    cost++;
                }
            }
        }
    }
    
    for (int col = 0; col < size; col++) {
        for (int row1 = 0; row1 < size; row1++) {
            for (int row2 = row1 + 1; row2 < size; row2++) {
                if (board->player_board[row1][col] != 0 && 
                    board->player_board[row1][col] == board->player_board[row2][col]) {
                    cost++;
                }
            }
        }
    }
    
    return cost;
}

static void generate_neighbor(SudokuBoard* board, SudokuBoard* neighbor) {
    int size = board->size;
    int box_size = board->box_size;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            neighbor->player_board[i][j] = board->player_board[i][j];
        }
    }

    int box_row = rand() % box_size;
    int box_col = rand() % box_size;

    int free_cells[size][2];
    int count = 0;

    for (int i = box_row * box_size; i < (box_row + 1) * box_size; i++) {
        for (int j = box_col * box_size; j < (box_col + 1) * box_size; j++) {
            if (board->puzzle[i][j] == 0) {
                free_cells[count][0] = i;
                free_cells[count][1] = j;
                count++;
            }
        }
    }

    if (count < 2) return;

    int idx1 = rand() % count;
    int idx2;
    do {
        idx2 = rand() % count;
    } while (idx2 == idx1);

    int temp = neighbor->player_board[free_cells[idx1][0]][free_cells[idx1][1]];
    neighbor->player_board[free_cells[idx1][0]][free_cells[idx1][1]] = 
        neighbor->player_board[free_cells[idx2][0]][free_cells[idx2][1]];
    neighbor->player_board[free_cells[idx2][0]][free_cells[idx2][1]] = temp;
}

bool solve_sudoku_sa(SudokuBoard* board) {
    srand(time(NULL));
    
    double T_start = 10.0;
    double T_end = 0.00001;
    double alpha = 0.995;
    int max_iterations = 500000;
    
    double T = T_start;
    int iteration = 0;
    
    int size = board->size;
    int box_size = board->box_size;
    
    for (int box_row = 0; box_row < box_size; box_row++) {
        for (int box_col = 0; box_col < box_size; box_col++) {

            int missing[size];
            int missing_count = 0;
            
            for (int num = 1; num <= size; num++) {
                bool found = false;
                for (int i = box_row * box_size; i < (box_row + 1) * box_size && !found; i++) {
                    for (int j = box_col * box_size; j < (box_col + 1) * box_size && !found; j++) {
                        if (board->puzzle[i][j] == num) {
                            found = true;
                        }
                    }
                }
                if (!found) {
                    missing[missing_count++] = num;
                }
            }
            
            for (int i = missing_count - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                int temp = missing[i];
                missing[i] = missing[j];
                missing[j] = temp;
            }
            
            int missing_idx = 0;
            for (int i = box_row * box_size; i < (box_row + 1) * box_size; i++) {
                for (int j = box_col * box_size; j < (box_col + 1) * box_size; j++) {
                    if (board->puzzle[i][j] == 0) {
                        board->player_board[i][j] = missing[missing_idx++];
                    }
                }
            }
        }
    }
    
    int current_cost = calculate_cost(board);
    int best_cost = current_cost;
    
    SudokuBoard* neighbor = create_board(size);
    if (!neighbor) return false;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            neighbor->puzzle[i][j] = board->puzzle[i][j];
        }
    }
    
    printf("Initial cost: %d\n", current_cost);
    
    while (T > T_end && iteration < max_iterations && current_cost > 0) {
        generate_neighbor(board, neighbor);
        int neighbor_cost = calculate_cost(neighbor);
        int delta_E = neighbor_cost - current_cost;
        
        if (delta_E < 0 || 
            (delta_E > 0 && exp(-delta_E / T) > (double)rand() / RAND_MAX)) {

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    board->player_board[i][j] = neighbor->player_board[i][j];
                }
            }
            current_cost = neighbor_cost;
            
            if (current_cost < best_cost) {
                best_cost = current_cost;
            }
        }
        
        T *= alpha;
        iteration++;
        
        if (iteration % 1000 == 0) {
            printf("Iteration: %d, Temperature: %.5f, Current cost: %d, Best cost: %d\n",
                   iteration, T, current_cost, best_cost);
        }
    }
    
    free_board(neighbor);
    
    printf("Final cost: %d\n", current_cost);
    return current_cost == 0;
}