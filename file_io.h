#ifndef FILE_IO_H
#define FILE_IO_H

#include "sudoku.h"

bool save_game(SudokuBoard* board, const char* filename);
SudokuBoard* load_game(const char* filename);

#endif
