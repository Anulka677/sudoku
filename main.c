#include "sudoku.h"
#include "menu.h"
#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void display_game_stats(SudokuBoard* board) {
    printf("\n*** GAME STATISTICS ***\n");
    print_stats(board);
}

SudokuBoard* setup_new_game(void) {
    int choice, size;
    Difficulty difficulty;
    char input[100];

    do {
        show_size_menu();
        if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: size = SIZE_4x4; break;
            case 2: size = SIZE_9x9; break;
            case 3: size = SIZE_16x16; break;
            case 4: return NULL;
            default: printf("Invalid choice. Try again.\n"); break;
        }
    } while (choice < 1 || choice > 4);

    do {
        show_difficulty_menu();
        if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: difficulty = EASY; break;
            case 2: difficulty = MEDIUM; break;
            case 3: difficulty = HARD; break;
            case 4: return NULL;
            default: printf("Invalid choice. Try again.\n"); break;
        }
    } while (choice < 1 || choice > 4);

    SudokuBoard* board = create_board(size);
    if (!board) {
        printf("Failed to create board\n");
        return NULL;
    }

    generate_solution(board);
    generate_puzzle(board, difficulty);
    start_game_timer(board);

    return board;
}

void play_game(SudokuBoard* board) {
    int choice, row, col, num;
    char filename[100];
    char input[100];

    while (1) {
        system("clear || cls");
        print_board(board);
        show_game_menu(board);

        if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter row, column and number (1-%d): ", board->size);
                if (fgets(input, sizeof(input), stdin) == NULL ||
                    sscanf(input, "%d %d %d", &row, &col, &num) != 3) {
                    printf("Invalid input\n");
                    break;
                }

                row--; col--;
                if (row >= 0 && row < board->size && col >= 0 && col < board->size &&
                    num >= 0 && num <= board->size) {
                    if (board->puzzle[row][col] == 0) {
                        if (is_valid_move(board, row, col, num)) {
                            board->player_board[row][col] = num;
                            increment_move_count(board);

                            if (is_board_complete(board)) {
                                end_game_timer(board);
                                printf("\nCongratulations! You solved the puzzle!\n");
                                print_stats(board);
                                print_board(board);
                                return;
                            }
                        } else {
                            printf("Invalid move. Try again.\n");
                        }
                    } else {
                        printf("This cell is fixed. You can't change it.\n");
                    }
                } else {
                    printf("Invalid input.\n");
                }
                break;

            case 2:
                printf("Enter row and column to clear (1-%d): ", board->size);
                if (fgets(input, sizeof(input), stdin) == NULL ||
                    sscanf(input, "%d %d", &row, &col) != 2) {
                    printf("Invalid input.\n");
                    break;
                }

                row--; col--;
                if (row >= 0 && row < board->size && col >= 0 && col < board->size) {
                    if (board->puzzle[row][col] == 0) {
                        board->player_board[row][col] = 0;
                        increment_move_count(board);
                    } else {
                        printf("Can't clear fixed numbers.\n");
                    }
                } else {
                    printf("Invalid input.\n");
                }
                break;

            case 3:
                printf("Enter filename to save: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) {
                    printf("Invalid input.\n");
                    break;
                }
                filename[strcspn(filename, "\n")] = '\0';
                if (save_game(board, filename)) {
                    printf("Game saved successfully!\n");
                } else {
                    printf("Failed to save game!\n");
                }
                break;

            case 4:
                display_game_stats(board);
                break;

            case 5:
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}

int main(void) {
    srand(time(0));
    SudokuBoard* board = NULL;
    int choice;
    char filename[100];
    char input[100];

    while (1) {
        show_main_menu();
        if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                board = setup_new_game();
                if (board) {
                    play_game(board);
                    free_board(board);
                }
                break;

            case 2:
                printf("Enter filename to load: ");
                if (fgets(filename, sizeof(filename), stdin) == NULL) {
                    printf("Invalid input.\n");
                    break;
                }
                filename[strcspn(filename, "\n")] = '\0';
                board = load_game(filename);
                if (board) {
                    printf("Game loaded successfully!\n");
                    play_game(board);
                    free_board(board);
                } else {
                    printf("Failed to load game!\n");
                }
                break;

            case 3:
                show_instructions();
                break;

            case 4:
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. \n");
        }
    }
}
