#include "menu.h"
#include "sudoku.h"
#include <stdio.h>

void show_main_menu(void) {
    printf("\n*** SUDOKU GAME ***\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Instructions\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

void show_size_menu(void) {
    printf("\n*** SELECT BOARD SIZE ***\n");
    printf("1. 4x4\n");
    printf("2. 9x9\n");
    printf("3. 16x16\n");
    printf("4. Back to Main Menu\n");
    printf("Choose an option: ");
}

void show_difficulty_menu(void) {
    printf("\n*** SELECT DIFFICULTY ***\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("4. Back to Main Menu\n");
    printf("Choose an option: ");
}

void show_game_menu(SudokuBoard* board) {
    (void)board;
    printf("\n*** GAME MENU ***\n");
    printf("1. Make a move\n");
    printf("2. Remove a number\n");
    printf("3. Save game\n");
    printf("4. Show statistics\n");
    printf("5. Return to Main Menu\n");
    printf("Choose an option: ");
}

void show_instructions(void) {
    printf("\n*** SUDOKU INSTRUCTIONS ***\n");
    printf("1. Fill the grid so that every row, column and box contains all numbers from 1 to N\n");
    printf("2. Each number can appear only once in each row, column and box\n");
    printf("3. To make a move, select the cell and enter the number\n");
    printf("4. Have fun\n");
}
