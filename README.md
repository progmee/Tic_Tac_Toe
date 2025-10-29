# Tic-Tac-Toe SFML

A **classic Tic-Tac-Toe game** implemented in **C++** using **SFML** for graphics.  
The project separates **game logic** (Board, AI) from **user interface**, allowing smooth integration of **console and graphical gameplay**.

---

## Features

- 3x3 Tic-Tac-Toe gameplay  
- Play against a simple AI that can **block** and **win**  
- Console and SFML graphical modes  
- Clean separation of **logic** and **frontend**  
- Handles **mouse clicks** and **window events** via SFML  

---

## Requirements

Install SFML on Ubuntu:

```bash
sudo apt update
sudo apt install libsfml-dev
```

---

## Compilation

Compile all source files with SFML:

```bash
g++ ./scripts/game.cpp ./scripts/libs/board/board.cpp ./scripts/libs/ai/ai.cpp \
    -o ./builds/game/tic-tac-toe \
    -lsfml-graphics -lsfml-window -lsfml-system
```
