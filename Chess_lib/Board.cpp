#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include <iostream>

void board_std_setup(std::vector<std::vector<Piece*>> &brd);
void board_test_setup(std::vector<std::vector<Piece*>> &brd);

// TODO: reduce redundancy here

Board::Board() {
    board_std_setup(chess_board);
    white_king_pos = {4, 0};
    black_king_pos = {4, 7};
}

Board::Board(Board* templ) {
    /*
     * Init all to nullptr
     */
    int rows = 8;
    int cols = 8;

    for (auto i = 0; i < cols; i++) {
        std::vector<Piece*> col;
        for (auto j = 0; j < rows; j++) {
            col.push_back(nullptr);
        }
        chess_board.push_back(col);
    }

    for (auto i = 0; i < templ->chess_board.size(); i++) {
        for (auto j = 0; j < templ->chess_board[i].size(); j++) {
            if (templ->chess_board[i][j] != nullptr) {
                chess_board[i][j] = templ->chess_board[i][j]->clone();
            } else {
                chess_board[i][j] = nullptr;
            }
        }
    }

    white_king_pos = templ->white_king_pos;
    black_king_pos = templ->black_king_pos;
}

Board::Board(int setting) {
    /*
    * Init all to nullptr
    */
    int rows = 8;
    int cols = 8;

    for (auto i = 0; i < cols; i++) {
        std::vector<Piece*> col;
        for (auto j = 0; j < rows; j++) {
            col.push_back(nullptr);
        }
        chess_board.push_back(col);
    }

    if (setting == 1) {
        /*
         * Castling test setup
         */
        chess_board[0][0] = new Rook(Piece::PieceColour::WHITE);
        chess_board[7][0] = new Rook(Piece::PieceColour::WHITE);
        chess_board[4][0] = new King(Piece::PieceColour::WHITE);
        white_king_pos = {4, 0};

        chess_board[0][7] = new Rook(Piece::PieceColour::BLACK);
        chess_board[7][7] = new Rook(Piece::PieceColour::BLACK);
        chess_board[4][7] = new King(Piece::PieceColour::BLACK);
        black_king_pos = {4, 7};
    }
}



Board::~Board() {
    /*
     * Delete each of the associated Piece objects
     */
    for (auto i = 0; i < chess_board.size(); i++) {
        for (auto j = 0; j < chess_board[i].size(); j++) {
            delete chess_board[i][j];
        }
    }

    chess_board.clear();
}

void Board::show_colour() {
    std::cout << "     a  b  c  d  e  f  g  h" << std::endl;
    int row_num = 0;
    for (auto i = 0; i < chess_board.size(); i++) {
        row_num++;
        std::cout << row_num << " | ";
        for (auto j = 0; j < chess_board[i].size(); j++) {
            std::cout << " ";
            if (chess_board[j][i] == nullptr) {
                std::cout << "-";
            } else {
                std::cout << (chess_board[j][i]->get_colour() == Piece::PieceColour::WHITE ? 'W' : 'B') << chess_board[j][i]->get_id();
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Board::show() {
    std::cout << "     a  b  c  d  e  f  g  h" << std::endl;
    int row_num = 0;
    for (auto i = 0; i < chess_board.size(); i++) {
        row_num++;
        std::cout << row_num << " | ";
        for (auto j = 0; j < chess_board[i].size(); j++) {
            std::cout << " ";
            if (chess_board[j][i] == nullptr) {
                std::cout << "-";
            } else {
                std::cout << chess_board[j][i]->get_id();
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void board_std_setup(std::vector<std::vector<Piece*>> &brd) {
    int cols = 8;
    int rows = 8;

    for (auto i = 0; i < cols; i++) {
        std::vector<Piece*> col;
        for (auto j = 0; j < rows; j++) {
            col.push_back(nullptr);
        }
        brd.push_back(col);
    }

    /*
     * Pawn pieces
     */
    for (auto i = 0; i < cols; i++) {
        brd[i][1] = new Pawn(Piece::PieceColour::WHITE);
        brd[i][6] = new Pawn(Piece::PieceColour::BLACK);
    }

    /*
     * Bishop pieces
     */
    brd[2][0] = new Bishop(Piece::PieceColour::WHITE);
    brd[2][7] = new Bishop(Piece::PieceColour::BLACK);
    brd[5][0] = new Bishop(Piece::PieceColour::WHITE);
    brd[5][7] = new Bishop(Piece::PieceColour::BLACK);

    /*
     * Knight pieces
     */
    brd[1][0] = new Knight(Piece::PieceColour::WHITE);
    brd[1][7] = new Knight(Piece::PieceColour::BLACK);
    brd[6][0] = new Knight(Piece::PieceColour::WHITE);
    brd[6][7] = new Knight(Piece::PieceColour::BLACK);

    /*
     * Rook pieces
     */
    brd[0][0] = new Rook(Piece::PieceColour::WHITE);
    brd[0][7] = new Rook(Piece::PieceColour::BLACK);
    brd[7][0] = new Rook(Piece::PieceColour::WHITE);
    brd[7][7] = new Rook(Piece::PieceColour::BLACK);

    /*
     * King pieces
     */
    brd[4][0] = new King(Piece::PieceColour::WHITE);
    brd[4][7] = new King(Piece::PieceColour::BLACK);

    /*
     * Queen pieces
     */
    brd[3][0] = new Queen(Piece::PieceColour::WHITE);
    brd[3][7] = new Queen(Queen::PieceColour::BLACK);
}

std::string Board::coord_pos_translation(Piece::coordinate coord) {
    std::unordered_map<int, char> col_conversion = {
            {0, 'a'},
            {1, 'b'},
            {2, 'c'},
            {3, 'd'},
            {4, 'e'},
            {5, 'f'},
            {6, 'g'},
            {7, 'h'},
    };
    std::string conv = col_conversion[coord.x] + std::to_string(coord.y + 1);

    return conv;
}

bool Board::verify_valid_pos(std::string pos) {
    return (pos.size() == 2 && pos[0] >= 'a' && pos[0] <= 'h' && pos[1] >= '1' && pos[1] <= '8');
}

bool Board::verify_valid_coord(Piece::coordinate coord) {
    return coord.x >= 0 && coord.x <= 7 && coord.y >= 0 && coord.y <= 7;
}

bool Board::is_valid_move_bishop(Piece*p, Piece::coordinate start, Piece::coordinate end) {
    if (p->poss_move(start, end)) {
        // trace the diagonal
        Piece::coordinate coord = start;
        if (end.x > start.x && end.y > start.y) {
            while (coord.x != end.x && coord.y != end.y) {
                coord.x++;
                coord.y++;

                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
                    return false;
                }
            }

            return true;
        } else if (end.x < start.x && end.y < start.y) {
            while (coord.x != end.x && coord.y != end.y) {
                coord.x--;
                coord.y--;

                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
                    return false;
                }
            }

            return true;
        } else if (end.x > start.x && end.y < start.y) {
            while (coord.x != end.x && coord.y != end.y) {
                coord.x++;
                coord.y--;

                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
                    return false;
                }
            }

            return true;
        } else if (end.x < start.x && end.y > start.y) {
            while (coord.x != end.x && coord.y != end.y) {
                coord.x--;
                coord.y++;

                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

bool operator==(const Piece::coordinate& a, const Piece::coordinate& b) {
    return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const Piece::coordinate& a, const Piece::coordinate& b) {
    return (a.x != b.x) || (a.y != b.y);
}

bool Board::is_valid_move_rook(Piece *p, Piece::coordinate start, Piece::coordinate end) {
    if (p->poss_move(start, end) && (start.x == end.x)) {
        // trace row
        Piece::coordinate coord = start;

        if (end.y > start.y) {
            while (coord.y != end.y) {
                if (coord != start && (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr)) {
                    return false;
                }

                coord.y++;
            }

            return true;
        } else if (end.y < start.y) {
            while (coord.y != end.y) {
                if (coord != start && (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr)) {
                    return false;
                }

                coord.y--;
            }

            return true;
        }
    } else if (p->poss_move(start, end) && (start.y == end.y)) {
        // trace col
        Piece::coordinate coord = start;
        if (end.x > start.x) {
            while (coord.x != end.x) {
                if (coord != start && (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr)) {
                    return false;
                }

                coord.x++;
            }

            return true;
        } else if (end.x < start.x) {
            while (coord.x != end.x) {
                if (coord != start && (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr)) {
                    return false;
                }

                coord.x--;
            }

            return true;
        }
    }

    return false;
}

bool Board::is_valid_move(Piece* p, Piece::coordinate start, Piece::coordinate end) {
    /*
     * Make sure end position is on the board
     */
    if (end.x < 0 || end.y < 0 || end.x > 7 || end.y > 7) {
        return false;
    }

    if (!verify_valid_coord(end) || (chess_board[end.x][end.y] != nullptr
                                     && chess_board[end.x][end.y]->get_colour() == p->get_colour())) {
        return false;
    }
    Piece::PieceType type = p->get_type();

    if (type == Piece::PieceType::PAWN) {
        /*
         * To check:
         * - Is the end coordinate on the board
         * - Is the end coordinate a nullptr (empty square)?
         * -- If not, is it the same colour as the current piece? If so, return false --- can only be true if empty square or enemy piece
         */
        if (p->poss_move(start, end) && chess_board[end.x][end.y] == nullptr) {
            // white
            if (p->get_colour() == Piece::PieceColour::WHITE && end.y == start.y + 2) {
                return chess_board[start.x][start.y + 1] == nullptr;
            }

            // black
            if (p->get_colour() == Piece::PieceColour::BLACK && end.y == start.y - 2) {
                return chess_board[start.x][start.y - 1] == nullptr;
            }

            return true;
        } else if (p->poss_capture(start, end)) {
            // know from previous check that it is not the same colour
            return chess_board[end.x][end.y] != nullptr;
        }
    } else if (type == Piece::PieceType::BISHOP) {
        return is_valid_move_bishop(p, start, end);
    } else if (type == Piece::PieceType::KNIGHT) {
        return (p->poss_move(start, end));
    } else if (type == Piece::PieceType::KING) {
        King* k = (King*) p;
        bool std_move = k->poss_move(start, end);
        if (std_move) {
            return true;
        }

        /*
         * Consider whether a King can castle to the left or the right
         * N.B. neither the King piece nor the Rook piece on that castling side can have moved
         */
        if (k->poss_castle_r(start, end)) {
            bool clear_path_r;
            bool is_rook_r;
            Rook* r;

            if (k->get_colour() == Piece::PieceColour::WHITE) {
                clear_path_r = chess_board[5][0] == nullptr && chess_board[6][0] == nullptr;
                is_rook_r = chess_board[7][0] != nullptr && chess_board[7][0]->get_type() == Piece::PieceType::ROOK;
                if (is_rook_r) {
                    r = (Rook*) chess_board[7][0];
                }

                return clear_path_r && is_rook_r && !r->has_moved;
            } else if (k->get_colour() == Piece::PieceColour::BLACK) {
                clear_path_r = chess_board[5][7] == nullptr && chess_board[6][7] == nullptr;
                is_rook_r = chess_board[7][7] != nullptr && chess_board[7][7]->get_type() == Piece::PieceType::ROOK;
                if (is_rook_r) {
                    r = (Rook*) chess_board[7][7];
                }

                return clear_path_r && is_rook_r && !r->has_moved;
            }
        } else if (k->poss_castle_l(start, end)) {
            bool clear_path_l;
            bool is_rook_l;
            Rook* r;

            if (k->get_colour() == Piece::PieceColour::WHITE) {
                clear_path_l = chess_board[3][0] == nullptr && chess_board[2][0] == nullptr
                        && chess_board[1][0] == nullptr;
                is_rook_l = chess_board[0][0] != nullptr && chess_board[0][0]->get_type() == Piece::PieceType::ROOK;
                if (is_rook_l) {
                    r = (Rook*) chess_board[0][0];
                }

                return clear_path_l && is_rook_l && !r->has_moved;
            } else if (k->get_colour() == Piece::PieceColour::BLACK) {
                clear_path_l = chess_board[3][7] == nullptr && chess_board[2][7] == nullptr
                        && chess_board[1][7] == nullptr;
                is_rook_l = chess_board[0][7] != nullptr && chess_board[0][7]->get_type() == Piece::PieceType::ROOK;
                if (is_rook_l) {
                    r = (Rook*) chess_board[0][7];
                }

                return clear_path_l && is_rook_l && !r->has_moved;
            }
        }

        return false;
    } else if (type == Piece::PieceType::QUEEN) {
        return is_valid_move_rook(p, start, end) || is_valid_move_bishop(p, start, end);
    } else if (type == Piece::PieceType::ROOK) {
        return is_valid_move_rook(p, start, end);
    }

    return false;
}

Piece::coordinate Board::pos_coord_translation(std::string pos) {
    bool valid_pos = verify_valid_pos(pos);
    if (valid_pos) {
        std::unordered_map<int, char> col_conversion = {
                {'a', 0},
                {'b', 1},
                {'c', 2},
                {'d', 3},
                {'e', 4},
                {'f', 5},
                {'g', 6},
                {'h', 7},
        };

        return {col_conversion[pos[0]], (int(pos[1]-'0') - 1)};
    }

    return {-1, -1};    // invalid input pos
}
