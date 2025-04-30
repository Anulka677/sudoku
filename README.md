# Sudoku Game

A console-based Sudoku game with multiple board sizes (4x4, 9x9, 16x16) and difficulty levels (Easy, Medium, Hard). The game features save/load functionality, move tracking, and game statistics.

## Features

- **Multiple Board Sizes**: Play 4x4, 9x9, or 16x16 Sudoku puzzles
- **Difficulty Levels**: Choose between Easy, Medium, and Hard difficulties
- **Game Saving/Loading**: Save your progress and load it later
- **Game Statistics**: Track your time and number of moves
- **Clear Display**: Formatted board display with box boundaries

## How to Play

1. Select "New Game" from the main menu
2. Choose your preferred board size
3. Select a difficulty level
4. Enter moves by specifying row, column, and number
5. Use the in-game menu to save, view stats, or return to main menu

## Installation & Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/sudoku.git
   cd sudoku

2. Compile the program:
   ```bash
   gcc -o sudoku main.c menu.c sudoku.c file_io.c -lm

3. Run the game:
   ```bash
   ./sudoku

## File Structure

- **main.c**: Main game loop and logic
- **sudoku.c/sudoku.h**: Core Sudoku logic and board operations
- **menu.c/menu.h**: Menu display and navigation
- **file_io.c/file_io.h**: Game saving and loading functionality

## Known Issues

4x4 Board Generation:  
The initial implementation had an issue where selecting Easy difficulty for 4x4 boards would show all cells as empty. This was fixed by implementing predefined empty cell counts for 4x4 boards


   