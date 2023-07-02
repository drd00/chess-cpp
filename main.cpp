#include <iostream>
#include "Chess_lib/Board.h"
#include "King.h"
#include "Rook.h"

typedef Piece::PieceColour Player;
typedef Piece::coordinate coord;

int check_check(Board* brd) {
    /*
     * Return 0 if the white king is in check
     * Return 1 if the black king is in check
     * Return -1 if neither king is in check
     */
    for (auto i = 0; i < brd->chess_board.size(); i++) {
        for (auto j = 0; j < brd->chess_board[i].size(); j++) {
            if (brd->chess_board[i][j] != nullptr) {
                if (brd->is_valid_move(brd->chess_board[i][j], {i, j}, brd->white_king_pos)) {
                    return 0;
                } else if (brd->is_valid_move(brd->chess_board[i][j], {i, j}, brd->black_king_pos)) {
                    return 1;
                }
            }
        }
    }

    return -1;
}

void make_move(Board* brd, Piece* p, coord start, coord end) {
    // standard move
    if (brd->chess_board[end.x][end.y] == nullptr) {
        brd->chess_board[end.x][end.y] = p;
        brd->chess_board[start.x][start.y] = nullptr;
    } else if (brd->chess_board[end.x][end.y] != nullptr) { // capture
        brd->chess_board[end.x][end.y] = p;
        brd->chess_board[start.x][start.y] = nullptr;
    }

    // must track whether a King has already moved for castling
    if (p->get_type() == Piece::PieceType::KING) {
        King* k = (King*) p;
        if (!k->has_moved) {
            k->has_moved = true;
        }

        if (p->get_colour() == Piece::PieceColour::BLACK) {
            brd->black_king_pos = end;
        } else if (p->get_colour() == Piece::PieceColour::WHITE) {
            brd->white_king_pos = end;
        }
    } else if (p->get_type() == Piece::PieceType::ROOK) {
        Rook* r = (Rook*) p;
        if (!r->has_moved) {
            r->has_moved = true;
        }
    }
}

void move_rook_castle(Board* brd, Piece* selected_piece, coord start, coord end) {
    // move the rook in the case of castling
    if (selected_piece->get_type() == Piece::PieceType::KING) {
        King* k = (King*) selected_piece;
        if (k->get_colour() == Piece::PieceColour::WHITE && k->poss_castle_l(start, end)) {
            make_move(brd, brd->chess_board[0][0], {0, 0}, {3, 0});
        } else if (k->get_colour() == Piece::PieceColour::WHITE && k->poss_castle_r(start, end)) {
            make_move(brd, brd->chess_board[7][0], {7, 0}, {5, 0});
        } else if (k->get_colour() == Piece::PieceColour::BLACK && k->poss_castle_l(start, end)) {
            make_move(brd, brd->chess_board[0][7], {0, 7}, {3, 7});
        } else if (k->get_colour() == Piece::PieceColour::BLACK && k->poss_castle_r(start, end)) {
            make_move(brd, brd->chess_board[7][7], {7, 7}, {5, 7});
        }
    }
}

bool handle_move(Board* brd, Piece* selected_piece, coord start, coord end) {
    /*
     * Return true and make a move if this move does not result in another check position
     *
     * Return false otherwise: the attempted move results in check
     */
    Piece::PieceColour colour = selected_piece->get_colour();
    auto* simulate = new Board(brd);
    auto* sel_piece = selected_piece->clone();

    move_rook_castle(simulate, sel_piece, start, end);
    make_move(simulate, sel_piece, start, end);

    bool white_check = (check_check(simulate) == 0);
    bool black_check = (check_check(simulate) == 1);

    if ((white_check && colour == Piece::PieceColour::WHITE) || (black_check && colour == Piece::PieceColour::BLACK)) {
        delete simulate;

        return false;
    } else {
        delete simulate;
    }

    move_rook_castle(brd, selected_piece, start, end);
    make_move(brd, selected_piece, start, end);

    int is_check = check_check(brd);
    if (is_check == 0) {
        std::cout << "White is now in check" << std::endl;
    } else if (is_check == 1) {
        std::cout << "Black is now in check" << std::endl;
    }

    return true;
}

void game_turn(Player ply, Board* brd) {
    bool valid = false;
    while (!valid) {
        brd->show();
        bool valid_input = false;
        std::string starting_pos;
        std::string end_pos;

        while (!valid_input) {
            std::cout << (ply == Player::WHITE ? "WHITE turn" : "BLACK turn") << std::endl;
            std::cout << "Enter starting position: ";
            std::cin >> starting_pos;
            std::cout << "Enter ending position: ";
            std::cin >> end_pos;

            valid_input = Board::verify_valid_pos(starting_pos) && Board::verify_valid_pos(end_pos);

            if (!valid_input) {
                std::cout << "Invalid input! Try again." << std::endl;
            }
        }

        coord start = Board::pos_coord_translation(starting_pos);
        coord end = Board::pos_coord_translation(end_pos);
        Piece* selected_piece = brd->chess_board[start.x][start.y];

        valid = selected_piece != nullptr &&
                selected_piece->get_colour() == ply && brd->is_valid_move(selected_piece, start, end);

        if (valid) {
            // make the move if it does not put ply into a check position
            bool move = handle_move(brd, selected_piece, start, end);

            if (!move) {
                std::cout << "Invalid move! Attempt to move into check position" << std::endl;
                valid = false;
            }
        } else {
            std::cout << "Invalid move!" << std::endl;
        }
    }
}

void game_play(Board* brd) {
    Player player_w = Player::WHITE;
    Player player_b = Player::BLACK;
    Player player_current = player_w;

    bool playing = true;
    while (playing) {
        if (player_current == player_w) {
            game_turn(player_w, brd);
            player_current = player_b;
        } else if (player_current == player_b) {
            game_turn(player_b, brd);
            player_current = player_w;
        }
    }
}

int main() {
    auto* b = new Board();
    //auto* b = new Board(1);
    game_play(b);

    return 0;
}
