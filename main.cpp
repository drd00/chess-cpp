#include <iostream>
#include "Chess_lib/Board.h"

typedef Piece::PieceColour Player;
typedef Piece::coordinate coord;

bool verify_input(std::string start, std::string end) {
    return Board::verify_valid_pos(start) && Board::verify_valid_pos(end);
}

void make_move(Piece* p, Board* brd, coord start, coord end) {
    // standard move
    if (brd->chess_board[end.x][end.y] == nullptr) {
        brd->chess_board[end.x][end.y] = p;
        brd->chess_board[start.x][start.y] = nullptr;
    } else if (brd->chess_board[end.x][end.y] != nullptr) { // capture
        brd->chess_board[end.x][end.y] = p;
        brd->chess_board[start.x][start.y] = nullptr;
    }
}

void start_game(Board* brd) {
    Player player_w = Player::WHITE;
    Player player_b = Player::BLACK;
    Player player_current = player_w;

    while (true) {
        if (player_current == player_w) {
            bool valid = false;
            while (!valid) {
                brd->show();
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

                valid = selected_piece != nullptr &&
                        selected_piece->get_colour() == player_current && brd->is_valid_move(selected_piece, start, end);
                if (valid) {
                    std::cout << "That is a valid move!" << std::endl;
                    make_move(selected_piece, brd, start, end);
                } else {
                    std::cout << "That is not a valid move!" << std::endl;
                }
            }
            player_current = player_b;
        } else if (player_current == player_b) {
            bool valid = false;
            while (!valid) {
                brd->show();
                bool valid_input = false;
                std::string starting_pos;
                std::string end_pos;
                while (!valid_input) {
                    std::cout << "Move for black:" << std::endl << "starting pos: ";
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

                valid = selected_piece != nullptr &&
                        selected_piece->get_colour() == player_current && brd->is_valid_move(selected_piece, start, end);
                if (valid) {
                    std::cout << "That is a valid move!" << std::endl;
                    make_move(selected_piece, brd, start, end);
                } else {
                    std::cout << "That is not a valid move!" << std::endl;
                }
            }

            player_current = player_w;
        }
    }
}

int main() {
    auto* b = new Board();
    start_game(b);

    return 0;
}
