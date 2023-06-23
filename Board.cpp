#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include <iostream>

void board_std_setup(std::vector<std::vector<Piece*>> &brd);

Board::Board() {
    board_std_setup(chess_board);
    show();
}
std::string Board::print_board() {

}

void Board::show() {
    for (auto i = 0; i < chess_board.size(); i++) {
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
    return (pos.size() == 2 && pos[0] >= 'a' && pos[1] >= 1 && pos[1] <= 8);
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
}

bool Board::is_valid_move_rook(Piece *p, Piece::coordinate start, Piece::coordinate end) {
    if (p->poss_move(start, end) && (start.x == end.x)) {
        // trace row
        Piece::coordinate coord = start;

        if (end.y > start.y) {
            while (coord.y != end.y) {
                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
                    return false;
                }

                coord.y++;
            }

            return true;
        } else if (end.y < start.y) {
            while (coord.y != end.y) {
                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
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
                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
                    return false;
                }

                coord.x++;
            }

            return true;
        } else if (end.x < start.x) {
            while (coord.x != end.x) {
                if (!verify_valid_coord(coord) || chess_board[coord.x][coord.y] != nullptr) {
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
        return (p->poss_move(start, end));
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

        return {col_conversion[pos[0]], (int(pos[1]) - 1)};
    }
}
