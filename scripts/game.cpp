#include <iostream> // Library for input output features
#include <array> // Library for dynamic arrays

#include <SFML/Graphics.hpp> // SFML library

// Libraries 
#include "libs/board/board.h"
#include "libs/ai/ai.h"

using namespace std;
using namespace sf;

class Game {
    public:
        // On game instantiation create window
        Game() : window(sf::VideoMode(window_size[0], window_size[1]), window_caption) {};

        /**
         * @brief Run game with all sfml components.
         */
        void run() {
            // Start game loop
            while (window.isOpen()){
                sf::Event event; // Create empty event

                // Assign empty event some event
                while (window.pollEvent(event)) {
                    handle_event(event); // Handle all events
                }

                window.clear(sf::Color::White);  // Clear frame to default black color

                

                window.display(); // Update frame
            }
        }

        /**
         * @brief Display grid 
         */
        void display() {

        }

        void handle_event(sf::Event& event) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    private:
        array<unsigned int, 2> window_size = {900, 900};
        string window_caption = "Tic-Tac-Toe";

        sf::RenderWindow window;
};

int main() {
    Game game;
    game.run();

    return 0;
}