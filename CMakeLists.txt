cmake_minimum_required(VERSION 3.30)
project(sudokuC C)

set(CMAKE_C_STANDARD 11)

add_executable(sudokuC main.c
        sudoku.h
        sudoku.c
        menu.h
        menu.c
        file_io.h
        file_io.c
        sa_sudoku.h
        sa_sudoku.c)
