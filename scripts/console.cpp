#include <iostream> // Library for input output features
#include <array> // Library for dynamic arrays

#include "libs/board/board.h"
#include "libs/ai/ai.h"

using namespace std;

class Game {
    public:
        /**
         * @brief Convert enum to character.
         * @param type Player type of choosen cell on grid.
         * @return Character of player type.
         */
        char convert_enum_to(Board::PlayerType type) {
            char character = '.';
            switch (type) {
                case Board::PlayerType::O:
                    character = 'O';
                    break;
                case Board::PlayerType::X:
                    character = 'X';
                    break;
            }
            return character;
        }

        /**
         * @brief Display board on console.
         * @param grid Grid represented by array. 
         */
        void display(array<array<Board::PlayerType, 3>, 3> grid, bool is_coordinates = true) {
            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #else
                system("clear"); // Clear screen from trash
            #endif

            int ascii_code = 'A'; // Get ascii code of A character
            string line = is_coordinates ? "  " : "";

            // Display numeration from 1 to end column
            for (int i_r = 0; i_r < grid[0].size(); i_r++) {

                line += (char)('0' + i_r);
                line += " ";

                if (i_r == grid[0].size() - 1){ // On last item display numerate coordinates
                    cout << line << endl;
                }
            }

            // Iterate each row and column
            for (auto row: grid){
                string line = "";

                for (int i_c = 0; i_c < row.size(); i_c++){
                    // Display alphabet cordinates 
                    if (is_coordinates == true and i_c == 0) {
                        line += ascii_code;
                        line += " "; // Add space

                        ascii_code++; // Next character after A
                    }


                    // Convert num into character and concatanate into line
                    line += convert_enum_to(row[i_c]);

                    line += " ";
                }

                cout << line << endl;
            }
        }

        array<int, 2> parse_coordinates(string input) {
            array<int, 2> coordinates = {-1, -1}; // -1 means that coordinate not correct

            // Create a vector of chars
            vector<char> chars(input.begin(), input.end());

            // There are have to be two chars for correct input
            if (chars.size() != 2) { return coordinates; };

            // Chars can not be converted to int
            if (!isalpha(chars[0]) || !isdigit(chars[1])) {
                return coordinates;
            };

            int y = (toupper(chars[0]) - 'A');
            int x = (chars[1] - '0');

            // Check that coordinates not succeed total size of board
            // Or cell already occupied
            if (!board.is_free_coordinates(x, y)) {
                return coordinates;
            }

            coordinates[0] = x; coordinates[1] = y;
            return coordinates;
        }

        array<int, 2> get_coordinates() {
            array<int, 2> coordinates;
            do {
                cout << "Enter coordinate in format LETTER:NUMBER." << endl;
                cout << ">> ";
                string input;

                cin >> input;

                coordinates = parse_coordinates(input);

                if (coordinates[0] == -1) {
                    cout << "Incorrect input! Try again. ";
                }
            } while (coordinates[0] == -1); // Ignore when coordinates not correct
            
            return coordinates;
        }

        Board::PlayerType get_player_type() {
            while (true) {
                cout << "Choose your player type. Possible values: X, O." << endl;;
                cout << ">> ";

                string input;
                cin >> input;

                if (input.size() == 1) {
                    char c = toupper(static_cast<unsigned char>(input[0]));
                    if (c == 'X') return Board::PlayerType::X;
                    if (c == 'O') return Board::PlayerType::O;
                }

                cout << "Incorrect input! Try again. ";
            }
        }

        bool is_end(Board::PlayerType player_type) {
            bool is_end = false;
            string end_string;

            Board::PlayerType winner = board.get_winner();
            // Tie
            if (board.is_full()) {
                is_end = true;

                end_string = "It is a tie.";
            }

            // Win or lost
            else if (winner != Board::PlayerType::None) {
                is_end = true;

                // Display after Console information
                winner == player_type ? end_string = "Congratulations! You won.": end_string = "You lost.";
            }

            // Display grid
            if (is_end) {
                display(board.get_grid());

                cout << end_string << endl;
            }
            return is_end;
        }

        void run() {
            cout << "Welcome to Tic-Tac-Toe Console!" << endl;
            cout << "Credits: Created by Progme." << endl;

            cout << "" << endl;

            Board::PlayerType player_type = get_player_type();
            Board::PlayerType ai_type = (player_type == Board::PlayerType::X) ? Board::PlayerType::O : Board::PlayerType::X;

            AI ai(board, ai_type);

            // Start Console loop
            while (true) {
                array<int, 2> coordinates;

                // Player first
                if (player_type == Board::PlayerType::X) {
                    display(board.get_grid()); // Display grid

                    // Parse coordinates from console
                    coordinates = get_coordinates();
                    board.do_turn(coordinates[0], coordinates[1], player_type);

                    if (is_end(player_type)) { break; } // Check that Console was ended

                    ai.do_turn();
                }
                // AI first
                else {
                    ai.do_turn();

                    if (is_end(player_type)) { break; } // Check that Console was ended

                    display(board.get_grid()); // Display grid

                    // Parse coordinates from console
                    coordinates = get_coordinates();
                    board.do_turn(coordinates[0], coordinates[1], player_type);
                }

                // Check that Console was ended
                if (is_end(player_type)) { break; }
            }
        }
    private:
        Board board;
};

int main() {
    Game game;
    game.run();

    return 0;
}