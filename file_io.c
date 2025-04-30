#include "file_io.h"
#include "sudoku.h"
#include <stdio.h>

bool save_game(SudokuBoard* board, const char* filename) {
    if (!board || !filename) return false;

    FILE* file = fopen(filename, "wb");
    if (!file) return false;

    if (fwrite(&board->size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return false;
    }

    for (int i = 0; i < board->size; i++) {
        if (fwrite(board->solution[i], sizeof(int), board->size, file) != board->size) {
            fclose(file);
            return false;
        }
    }

    for (int i = 0; i < board->size; i++) {
        if (fwrite(board->player_board[i], sizeof(int), board->size, file) != board->size) {
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

SudokuBoard* load_game(const char* filename) {
    if (!filename) return NULL;

    FILE* file = fopen(filename, "rb");
    if (!file) return NULL;

    int size;
    if (fread(&size, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    if (size != SIZE_4x4 && size != SIZE_9x9 && size != SIZE_16x16) {
        fclose(file);
        return NULL;
    }

    SudokuBoard* board = create_board(size);
    if (!board) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (fread(board->solution[i], sizeof(int), size, file) != size) {
            fclose(file);
            free_board(board);
            return NULL;
        }
    }

    for (int i = 0; i < size; i++) {
        if (fread(board->player_board[i], sizeof(int), size, file) != size) {
            fclose(file);
            free_board(board);
            return NULL;
        }
    }

    fclose(file);
    return board;
}