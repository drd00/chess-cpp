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
                if (brd->is_valid_move(brd->chess_board[i][j], brd->white_king_pos)) {
                    return 0;
                } else if (brd->is_valid_move(brd->chess_board[i][j], brd->black_king_pos)) {
                    return 1;
                }
            }
        }
    }

    return -1;
}

void make_move(Board* brd, Piece* p, coord end) {
    coord start = p->coord;

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

    p->coord = end;
}

void move_rook_castle(Board* brd, Piece* selected_piece, coord end) {
    // move the rook in the case of castling
    if (selected_piece->get_type() == Piece::PieceType::KING) {
        King* k = (King*) selected_piece;
        if (k->get_colour() == Piece::PieceColour::WHITE && k->poss_castle_l(end)) {
            make_move(brd, brd->chess_board[0][0], {3, 0});
        } else if (k->get_colour() == Piece::PieceColour::WHITE && k->poss_castle_r(end)) {
            make_move(brd, brd->chess_board[7][0], {5, 0});
        } else if (k->get_colour() == Piece::PieceColour::BLACK && k->poss_castle_l(end)) {
            make_move(brd, brd->chess_board[0][7], {3, 7});
        } else if (k->get_colour() == Piece::PieceColour::BLACK && k->poss_castle_r(end)) {
            make_move(brd, brd->chess_board[7][7], {5, 7});
        }
    }
}

bool run_simulate(Board* brd, Piece* p, coord end) {
    Piece::PieceColour colour = p->get_colour();
    auto* simulate = new Board(brd);
    auto* sel_piece = p->clone();

    move_rook_castle(simulate, sel_piece, end);
    make_move(simulate, sel_piece, end);

    int check = check_check(simulate);

    bool white_check = (check == 0);
    bool black_check = (check == 1);

    if ((white_check && colour == Piece::PieceColour::WHITE) || (black_check && colour == Piece::PieceColour::BLACK)) {
        delete simulate;

        return false;
    } else {
        delete simulate;
    }

    return true;
}


/*
 * TODO: write this function with less repetition
 */
int check_mate(Board* brd, int check_status) {
    /*
     * Mate if the King is currently in check and any movement would result in the King
     * still being in check
     *
     * Return 0 if white king checkmate
     * Return 1 if black king checkmate
     */

    if (check_status == 0) {    // white king is in check
        // check for mate
        coord wk = brd->white_king_pos;
        std::vector<coord> poss_end_coords { {wk.x + 1, wk.y + 1}, {wk.x + 1, wk.y}, {wk.x + 1, wk.y - 1},
                                             {wk.x, wk.y - 1}, {wk.x - 1, wk.y - 1}, {wk.x - 1, wk.y}, {wk.x - 1, wk.y + 1},
                                             {wk.x, wk.y + 1}};

        bool any_poss_move = false;
        Piece* white_king = brd->chess_board[wk.x][wk.y];
        for (auto c : poss_end_coords) {
            if (brd->is_valid_move(white_king, c)) {
                any_poss_move = run_simulate(brd, white_king, c);

                if (any_poss_move) {
                    return -1;
                }
            }
        }

        return 0;
    }
    if (check_status == 1) {    // black king is in check
        // check for mate
        coord bk = brd->black_king_pos;

        std::vector<coord> poss_end_coords { {bk.x + 1, bk.y + 1}, {bk.x + 1, bk.y}, {bk.x + 1, bk.y - 1},
                                             {bk.x, bk.y - 1}, {bk.x - 1, bk.y - 1}, {bk.x - 1, bk.y}, {bk.x - 1, bk.y + 1},
                                             {bk.x, bk.y + 1}};

        bool any_poss_move = false;
        Piece* black_king = brd->chess_board[bk.x][bk.y];
        for (auto c : poss_end_coords) {
            if(brd->is_valid_move(black_king, c)) {
                any_poss_move = run_simulate(brd, black_king, c);

                if (any_poss_move) {
                    return -1;
                }
            }
        }

        return 1;
    }

    return -1;  // no mate
}

bool handle_move(Board* brd, Piece* selected_piece, coord end, bool &checkmate) {
    /*
     * Return true and make a move if this move does not result in another check position
     *
     * Return false otherwise: the attempted move results in check
     */
    bool sim_success = run_simulate(brd, selected_piece, end);
    if (sim_success) {
        move_rook_castle(brd, selected_piece, end);
        make_move(brd, selected_piece, end);

        int is_check = check_check(brd);
        if (is_check == 0) {
            std::cout << "White is now in check" << std::endl;
        } else if (is_check == 1) {
            std::cout << "Black is now in check" << std::endl;
        }

        checkmate = check_mate(brd, is_check) != -1;

        return true;
    } else {
        return false;
    }
}

void game_turn(Player ply, Board* brd, bool &checkmate) {
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
                selected_piece->get_colour() == ply && brd->is_valid_move(selected_piece, end);

        if (valid) {
            // make the move if it does not put ply into a check position
            bool move = handle_move(brd, selected_piece, end, checkmate);

            if (checkmate) {
                Player other_player = (ply == Player::WHITE ? Player::BLACK : Player::WHITE);
                std::cout << "Checkmate! " << (other_player == Player::WHITE ? "Black" : "White") << " has won." << std::endl;
            }

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

    bool mate = false;
    while (!mate) {
        if (player_current == player_w) {
            game_turn(player_w, brd, mate);
            player_current = player_b;
        } else if (player_current == player_b) {
            game_turn(player_b, brd, mate);
            player_current = player_w;
        }
    }
}

int main() {
    //auto* b = new Board();
    auto* b = new Board(2);
    game_play(b);


    return 0;
}
