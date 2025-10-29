#pragma once // Avoid double inclusion of files

#include <array>
#include <vector>
#include "../board/board.h"

class AI {
    public:
        AI(Board& _board, Board::PlayerType _type) : board(_board), type(_type) { }

        /**
         * @brief Find win coordinates.
         * @return Return all possible win coordinates.
         */
        std::vector<std::array<size_t, 2>> find_win_coordinates(Board::PlayerType player_type);

        /**
         * @brief Do turn by AI. Try to win or block. In other case, take random.
         */
        bool do_turn();

        /**
         * @brief Choose random turn and set.
         * @param coordinates Collection of win coordinates.
         */
        bool do_random_turn(std::vector<std::array<size_t, 2>> coordinates);
    private:
        Board::PlayerType type;
        Board& board;
};