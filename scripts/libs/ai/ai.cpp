#include "ai.h"
#include <random>

std::vector<std::array<size_t, 2>> AI::find_win_coordinates(Board::PlayerType player_type) {
    // Store win coordinates inside of vector
    std::vector<std::array<size_t, 2>> win_coordinates = {};
    std::vector<std::array<size_t, 2>> free_coordinates = board.get_free_coordinates();

    for (auto coordinate: free_coordinates) {
        if (board.is_win_coordinate(coordinate[0], coordinate[1], player_type)) {
            win_coordinates.push_back(coordinate); // 
        }
    }

    return win_coordinates;
}

std::array<size_t, 2> pick_coordinate(std::vector<std::array<size_t, 2>> coordinates) {
    static std::default_random_engine generator(std::random_device{}()); // Set generator object once
    std::uniform_int_distribution<int> distribution(0, coordinates.size() - 1);

    return coordinates[distribution(generator)];
}

bool AI::do_random_turn(std::vector<std::array<size_t, 2>> coordinates) {
    // Ignore empty coordinates
    if (coordinates.size() == 0) { return false; }

    // Pick random coordinate
    auto rand_coordinate = pick_coordinate(coordinates);

    // Do turn on board
    return board.do_turn(rand_coordinate[0], rand_coordinate[1], type);
}

bool AI::do_turn() {
    // Ignore turn when full
    if (board.is_full()) {
        return false;
    }

    // Try to win
    auto win_coordinates = find_win_coordinates(type);

    if (do_random_turn(win_coordinates)) {return true; };
    
    Board::PlayerType opponent_type = Board::PlayerType::O;
    if (type == Board::PlayerType::O) {
        opponent_type = Board::PlayerType::X;
    }

    // Try to block
    auto block_coordinates = find_win_coordinates(opponent_type);

    if (do_random_turn(block_coordinates)) {return true; };

    // Otherwise choose random free cell
    auto rand_coordinate = pick_coordinate(board.get_free_coordinates());
    return board.do_turn(rand_coordinate[0], rand_coordinate[1], type);
}
