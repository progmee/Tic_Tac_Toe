#include "board.h"

bool Board::is_valid_coordinates(size_t x, size_t y){
    return (x < grid[0].size() and y < grid.size()) ? true : false;
}

bool Board::is_free_coordinates(size_t x, size_t y) {
    return is_valid_coordinates(x, y) and (grid[y][x] == PlayerType::None);
}

bool Board::do_turn(size_t x, size_t y, PlayerType type) {
    // Exclude not correct input
    if (!is_free_coordinates(x, y) or (type == PlayerType::None)) { return false; }

    grid[y][x] = type; // Mark a cell
    turns++; // Increment counter

    return true;
}

bool Board::is_full() {
    // Size turns bigger then total size
    return turns >= (grid[0].size() * grid.size());
}

bool Board::is_win_coordinate(size_t x, size_t y, PlayerType type) {
    // Not free coordinate, ignore
    if (!is_free_coordinates(x, y)) { return false; }

    // Temporaly set case to mark
    grid[y][x] = type;
    PlayerType winner = get_winner();
    grid[y][x] = PlayerType::None;

    return winner == type;
}

Board::PlayerType Board::get_winner() {
    // All 8 win patterns (x,y) pairs
    std::array<std::array<std::array<size_t,2>,3>,8> patterns{{
        // Diagonals
        {{{0,0},{1,1},{2,2}}},
        {{{0,2},{1,1},{2,0}}},
        // Horizontals
        {{{0,0},{0,1},{0,2}}},
        {{{1,0},{1,1},{1,2}}},
        {{{2,0},{2,1},{2,2}}},
        // Verticals
        {{{0,0},{1,0},{2,0}}},
        {{{0,1},{1,1},{2,1}}},
        {{{0,2},{1,2},{2,2}}}
    }};

    for (auto pattern : patterns) {
        // Take the first cell of the pattern
        PlayerType cell = grid[pattern[0][1]][pattern[0][0]];
        if (cell == PlayerType::None) continue; // Empty line can't be a win

        bool same = true;
        for (size_t i = 1; i < pattern.size(); ++i) {
            if (grid[pattern[i][1]][pattern[i][0]] != cell) {
                same = false;
                break;
            }
        }
        if (same) return cell;
    }

    return PlayerType::None;
}

/**
 * @brief Get free coordinates on board.
 * @return Vector of free coordinates.
 */
std::vector<std::array<size_t, 2>> Board::get_free_coordinates() {
    std::vector<std::array<size_t, 2>> coordinates = {}; 
    for (size_t y = 0; y < grid.size(); y++ ) {
        for (size_t x = 0; x < grid[0].size(); x++) {
            // Coordinate add to array
            if (is_free_coordinates(x, y)) {
                coordinates.push_back({{x, y}});
            }
        }
    }
    return coordinates;
}