#pragma once // Avoid double inclusion of files

#include <array>
#include <vector>

class Board {
    public:
        Board() {
            // On init reset board
            reset();
        }

        enum PlayerType { None, X, O };

        /**
         * @brief Reset current board to default values.
         */
        void reset() {
            grid = {{
                {{PlayerType::None, PlayerType::None, PlayerType::None}},
                {{PlayerType::None, PlayerType::None, PlayerType::None}},
                {{PlayerType::None, PlayerType::None, PlayerType::None}}
            }};
        };

        /**
         * @brief Check that selected coordinate can give win
         * @return If true win coordinate
         */
        bool is_win_coordinate(size_t x, size_t y, PlayerType type);

        /**
         * @brief Get a copy of board.
         * @return Nested array with size 3x3.
         */
        std::array<std::array<PlayerType, 3>, 3> get_grid() {return grid; };

        /**
         * @brief Coordinates verification.
         * @param x The row index (0-2)
         * @param y The column index (0-2)
         * @return true if coordinates correct
         * @return false if coordinates were invalid
         */
        bool is_valid_coordinates(size_t x, size_t y);

        /**
         * @brief Coordinates verification and check that selected cell is free.
         * @param x The row index (0-2)
         * @param y The column index (0-2)
         * @return true if coordinates correct and cell is free
         * @return false if coordinates were invalid or cell occupied
         */
        bool is_free_coordinates(size_t x, size_t y);

        /**
         * @brief Get all free coordinates.
         */
        std::vector<std::array<size_t, 2>> get_free_coordinates();

        /**
         * @brief Makes a move at the specified position.
         * 
         * @param x The row index (0-2)
         * @param y The column index (0-2)
         * @param type The player making the move (X, O)
         * @return true if the move was successful
         * @return false if the move was invalid
         */
        bool do_turn(size_t x, size_t y, PlayerType type);
        
        /**
         * @brief Checks if the board is completely filled.
         * @return true if full
         * @return false otherwise
         */
        bool is_full();

        /**
         * @brief Returns the winner of the game.
         * @return PlayerType representing the winner (None, X, O)
         */
        PlayerType get_winner();
    private:
        size_t turns = 0;
        std::array<std::array<PlayerType, 3>, 3> grid;
};