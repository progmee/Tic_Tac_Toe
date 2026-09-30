# Tic-Tac-Toe (C++ / SFML)

A clean implementation of the classic Tic-Tac-Toe game built in C++. The core design principle of this project is a strict separation between **game logic** and **user interface**, allowing the game to run seamlessly in either a traditional console mode or a graphical SFML mode.

## Features

* **Decoupled Architecture:** Core game rules and state management are fully separated from the rendering layer.
* **Dual Interface Modes:** 
  * **Graphical Mode:** Built using **SFML** (Simple and Fast Multimedia Library) for a clean visual experience.
  * **Console Mode:** Play directly inside your terminal using text-based input/output.
* **Modern C++:** Written with clean structure and modular organization.

## Project Structure

* `game.cpp` — Core game logic, state machine, and rules validation.
* `console.cpp` — CLI interface implementation.
* `assets/` — Visual assets and resources for the SFML mode.
* `libs/` — External libraries and dependencies.
* `.vscode/` — Workspace and editor configurations.

## Getting Started

### Prerequisites
* A C++ compiler supporting C++11 or higher.
* SFML library installed locally (for graphical mode).

### Building and Running
Clone the repository and compile the source files along with the SFML flags:

```bash
g++ game.cpp console.cpp -o tic_tac_toe -lsfml-graphics -lsfml-window -lsfml-system
