#include <iostream> // Library for input output features
#include <array> // Library for dynamic arrays
#include <filesystem>

#include <SFML/Graphics.hpp> // SFML library

// Libraries 
#include "libs/board/board.h"
#include "libs/ai/ai.h"

using namespace std;
using namespace sf;

class Game {
    public:
        // On game instantiation create window
        Game() : window(sf::VideoMode(window_size.x, window_size.y), window_caption, sf::Style::Titlebar | sf::Style::Close) {
            font.loadFromFile("assets/JosefinSans-Regular.ttf"); // Load font on init
        };

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

                display(); // Display on screen
            }
        }

        void draw_rect(int position, int thickness, bool is_horizontal, sf::Color color) {
            sf::Vector2f line_vector = is_horizontal ? sf::Vector2f(window_size.x, thickness) : sf::Vector2f(thickness, window_size.y);
            sf::RectangleShape rect(line_vector);

            // Set line position depends if it horizontal or not
            is_horizontal ? rect.setPosition(0, position) : rect.setPosition(position, 0);
            rect.setFillColor(color);

            window.draw(rect);
        }

        void draw_outline(Vector2i virtual_pos, sf::Color color) {
            // Ignore not valide virtual position
            if (virtual_pos.x == -1) return;

            RectangleShape rect(Vector2f(cell_size, cell_size));

            // Set params for rectangle
            rect.setFillColor(outline_color);
            rect.setPosition(cell_size * virtual_pos.x + virtual_pos.x * grid_thickness, cell_size * virtual_pos.y + virtual_pos.y * grid_thickness);
            
            window.draw(rect);
        }

        void draw_grid(size_t thickness, float cell_size, sf::Color color) {
            for (float position = cell_size; position <= window_size.x; position += cell_size + thickness) {
                draw_rect(position, thickness, true, color); // Horizontal
                draw_rect(position, thickness, false, color); // Vertical
            }
        }

        void draw_cross(sf::Vector2f position, size_t length, size_t thickness, sf::Color color) {
            for (size_t i = 0; i <= 1; i++) {
                sf::RectangleShape line(sf::Vector2f(length, thickness));

                line.setFillColor(color);
                line.setOrigin(length / 2, thickness / 2);
                line.setPosition(position);
                line.setRotation(i == 0 ? -45 : 45);

                window.draw(line);
            }
        }

        void draw_circle(sf::Vector2f position, size_t radius, size_t thickness, sf::Color color) {
            radius -= thickness; // Reduce radius by thickness
            
            sf::CircleShape circle(radius, 60);

            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(color);
            circle.setOutlineThickness(thickness);

            circle.setOrigin(radius, radius);
            circle.setPosition(position);
            
            window.draw(circle);
        }

        void draw_game_over() {
            sf::Text text;

            text.setFont(font);
            text.setCharacterSize(60);

            string game_over;

            if (board.get_winner() == player_type) {
                game_over = "Congratulations, you won!";
            }
            else if (board.get_winner() == ai_type) {
                game_over = "Unfortunately, you lost.";
            }
            else {
                game_over = "It is a tie";
            }

            text.setString(game_over);

            // Get bounds of text box
            sf::FloatRect bounds = text.getLocalBounds();

            Vector2f panel_size = sf::Vector2f(bounds.width * 1.2, bounds.height * 1.6);

            sf::RectangleShape panel(panel_size);

            // Set origin at center
            panel.setOrigin(bounds.width * 0.6, bounds.height * 0.8);
            panel.setFillColor(sf::Color(0, 0, 0, 122));

            panel.setPosition((window_size.x / 2), window_size.y / 2);

            // Define center of text box
            text.setOrigin(bounds.width / 2, bounds.height / 2);
            // Set by origin point
            text.setPosition(window_size.x / 2, window_size.y / 2 - 10);

            window.draw(panel); // Show panel on window
            window.draw(text);
        }

        sf::Vector2i get_virtual_position(sf::Vector2i mouse_position) {
            // Mouse position outside of window return (-1, -1)
            if (mouse_position.x < 0 || mouse_position.x > window_size.x 
                || mouse_position.y < 0 || mouse_position.y > window_size.y) {
                    return sf::Vector2i(-1, -1);
                }
            
            return sf::Vector2i(
                (int) (mouse_position.x / (cell_size + grid_thickness)),
                (int) (mouse_position.y / (cell_size + grid_thickness))
            );
        }

        void display() {
            window.clear(background_color);  // Set background color

            // Not valide pos, use last virtual position
            if (virtual_position.x == -1 and virtual_position.y == -1) {
                draw_outline(last_virtual_position, outline_color);
            }
            else {
                draw_outline(virtual_position, outline_color);
            }

            // Draw grid
            draw_grid(grid_thickness, cell_size, grid_color);
            auto grid = board.get_grid();

            for (size_t column = 0; column <= grid.size(); column++) {
                for (size_t row = 0; row <= grid[0].size(); row++) {
                    sf::Vector2f position = sf::Vector2f(cell_size / 2 + cell_size * row + row * grid_thickness, cell_size / 2 + cell_size * column + column * grid_thickness);
                    
                    // Draw cross and circles
                    if (grid[column][row] == Board::PlayerType::X) {
                        draw_cross(position, 280, grid_thickness - 10, cross_color);
                    }
                    else if (grid[column][row] == Board::PlayerType::O) {
                        draw_circle(position, 120, grid_thickness - 10, circle_color);
                    }
                }
            }

            // When is game over, display game over sign
            if (is_game_over) draw_game_over();
            
            if (virtual_position.x != -1) last_virtual_position = virtual_position;
            window.display(); // Update frame
        }

        void handle_event(sf::Event& event) {
            // While game not over
            if (!is_game_over) {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

                virtual_position = get_virtual_position(mouse_position);
            }

            if (event.type == sf::Event::Closed)
                window.close();
            // Check that virtual position valide, while mouse pressed and game 
            else if (event.type == sf::Event::MouseButtonPressed && virtual_position.x != -1 && virtual_position.y != -1 && !is_game_over && board.is_free_coordinates(virtual_position.x, virtual_position.y)) {
                board.do_turn(virtual_position.x, virtual_position.y, Board::PlayerType::X); // Player do turn
                
                // Is was found a winner
                if (board.get_winner() != Board::PlayerType::None || board.is_full()) {
                    is_game_over = true;
                    return; // Avoid ai turn
                }

                ai.do_turn();

                // Is was found a winner
                if (board.get_winner() != Board::PlayerType::None || board.is_full()) {
                    is_game_over = true;
                    return; // Avoid ai turn
                }

            }
        }
    private:
        sf::Vector2i window_size = {900, 900};
        string window_caption = "Tic-Tac-Toe";

        // Ingame colors
        Color background_color {75, 186, 172, 255};
        Color grid_color {62, 158, 146, 255};
        Color cross_color {84, 84, 84, 255};
        Color circle_color {215, 213, 201, 255};
        Color outline_color {47, 172, 156, 255};

        Vector2i last_virtual_position {-1, -1}; // Store last cursor position
        Vector2i virtual_position {-1, -1}; // Current cursor position

        bool is_game_over = false;

        size_t grid_thickness = 30;
        float cell_size = (window_size.x - 2 * grid_thickness) / 3;

        Font font;

        // Player types
        Board::PlayerType player_type = Board::PlayerType::X;
        Board::PlayerType ai_type = Board::PlayerType::O;

        Board board;
        AI ai {board, ai_type};

        sf::RenderWindow window;
};

int main() {
    Game game;
    game.run();

    return 0;
}