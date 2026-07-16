# Tic-Tac-Toe

A console-based Tic-Tac-Toe game in C++ where a player competes against the computer.

## Features

- Coin toss to decide who goes first (Player or Computer)
- Computer AI that tries to win or block the player
- Input validation for player moves
- Supports positions 1–9 mapped to the 3x3 board

## Board Layout

```
1  2  3
4  5  6
7  8  9
```

## How to Play

1. Run the executable
2. A toss determines who plays first and assigns symbols (`X` / `O`)
3. On your turn, enter a number (1–9) to place your symbol
4. First to align 3 symbols in a row, column, or diagonal wins

## Build & Run

**Compile:**
```bash
g++ TicTacToe.cpp -o TicTacToe
```

**Run:**
```bash
./TicTacToe        # Linux/macOS
TicTacToe.exe      # Windows
```

## Requirements

- C++11 or later
- A C++ compiler (e.g., g++, MSVC)
