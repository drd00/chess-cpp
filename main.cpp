#include <iostream>
#include "Board.h"

typedef Piece::PieceColour Player;
typedef Piece::coordinate coord;

bool verify_input(std::string start, std::string end) {
    return Board::verify_valid_pos(start) && Board::verify_valid_pos(end);
}

void start_game(Board* brd) {
    Player player_w = Player::WHITE;
    Player player_b = Player::BLACK;
    Player player_current = player_w;

    while (true) {
        if (player_current == player_w) {
            bool valid_input = false;
            std::string starting_pos;
            std::string end_pos;
            while (!valid_input) {
                std::cout << "Move for white:" << std::endl << "starting pos: ";
                std::cin >> starting_pos;
                std::cout << "end pos: ";
                std::cin >> end_pos;

                valid_input = verify_input(starting_pos, end_pos);

                if (!valid_input) {
                    std::cout << "Invalid input! Try again." << std::endl;
                }
            }
            coord start = Board::pos_coord_translation(starting_pos);
            coord end = Board::pos_coord_translation(end_pos);
            Piece* selected_piece = brd->chess_board[start.x][start.y];

            if (selected_piece->poss_move(start, end) || selected_piece->poss_capture(start, end)) {

            }

            player_current = player_b;
        } else if (player_current == player_b) {

            player_current = player_w;
        }
    }
}

int main() {
    Board* b = new Board();
    start_game(b);

    return 0;
}
