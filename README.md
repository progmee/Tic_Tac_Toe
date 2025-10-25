# Tic-Tac-Toe SFML

![C++](https://img.shields.io/badge/C%2B%2B-17-blue) ![SFML](https://img.shields.io/badge/SFML-2.5-orange)

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

- **C++17 or later**  
- **SFML** (Simple and Fast Multimedia Library)  

Install SFML on Ubuntu:

```bash
sudo apt update
sudo apt install libsfml-dev
```

---

## Compilation

Compile all source files with SFML:

g++ ./scripts/game.cpp ./scripts/libs/board/board.cpp ./scripts/libs/ai/ai.cpp \
    -o ./builds/game/tic-tac-toe \
    -lsfml-graphics -lsfml-window -lsfml-system
