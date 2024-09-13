# Memory Card Game

## Overview
This is a simple Memory Card Game implemented in C.<br>
The game challenges the player to remember and match pairs of cards.<br>
The objective is to find all the matching pairs as quickly and accurately as possible.

## Features
- **Grid of Cards:** Cards are arranged in a grid, initially hidden.
- **Turn-based Gameplay:** Players reveal two cards per turn.
- **Matching Logic:** If two cards match, they remain face up; otherwise, they are hidden again.
- **Win Condition:** The game ends when all pairs are found.
- **Score Tracking:** Keep track on each player score.

## How to Play
1. Run the program.
2. The cards will be shuffled and placed face down.
3. Select two cards to reveal them (write row-number space column-number).
4. If the cards match, they will remain face up.
5. Continue selecting pairs until all matches are found.

## Technologies Used
- **Language:** C
- **Concepts:** Arrays, Structs, Pointers, Game Loops

## Setup and Usage
1. Clone the repository:
   ```bash
   git clone https://github.com/Fisher-Shira/Memory_Card_Game.git
2. Navigate to the project directory:
   ```bash
    cd Memory_Card_Game
3. Compile the project:
   ```bash
    gcc -o memory_game memory_game.c
4. Run the executable:
   ```bash
    ./memory_game

## Project Structure
memory_game.c – The main file containing the game logic.<br>
memory_game.h - File contains declarations and definitions used throughout the project.<br>
README.md – This file.
