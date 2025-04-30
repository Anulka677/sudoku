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

## Screenshots
<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 23 58" src="https://github.com/user-attachments/assets/92157b32-2e7a-463e-949e-24883e0bf820" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 24 13" src="https://github.com/user-attachments/assets/ed86fb26-06b4-4660-8280-e93ca677670a" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 24 34" src="https://github.com/user-attachments/assets/879cd567-882a-4644-add7-9f05c7a7781c" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 24 50" src="https://github.com/user-attachments/assets/d2d1d392-0a28-4f3e-bd2a-80adc8ef4cfa" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 24 59" src="https://github.com/user-attachments/assets/681655e8-6cd6-43d4-834b-f095afe12f14" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 25 19" src="https://github.com/user-attachments/assets/991f23af-a030-4e81-a74e-d38ebbecfcf0" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 25 30" src="https://github.com/user-attachments/assets/c78f33df-4f4e-411a-8401-409c8c01ab1e" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 25 53" src="https://github.com/user-attachments/assets/4daf64ee-f46e-406c-b150-1a22092a9827" />

<img width="1440" alt="Zrzut ekranu 2025-04-30 o 16 26 03" src="https://github.com/user-attachments/assets/af97f942-ec29-4676-b1df-82f94c75a4db" />


![IMG_6642](https://github.com/user-attachments/assets/eb76cdef-5d80-4914-86d0-56fcec740aeb)



   
