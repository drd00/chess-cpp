#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include "Piece.h"
#include <string>
#include <unordered_map>

class Board {
public:
    Board();
    Board(int setting);    // for unit testing; does not set up pieces in default manner
    Board(Board* templ); // create a board with another board as a template
    ~Board();
    std::vector<std::vector<Piece*>> chess_board;

    /**
     * is_valid_move: making use of the Piece movement possibility functions (poss_move and poss_capture)
     * Consider the board and whether this piece may actually make such a move --- whether there are obstructions, other
     * pieces and their colours, etc., whether the end position is within board bounds, etc.
     * @param p: a pointer to the piece attempting to move
     * @param start: the current coordinates on the board of p
     * @param end: the goal coordinates on the board of p
     * @return bool whether a move for Piece p is valid, taking into account the board state
     */
    bool is_valid_move(Piece* p, Piece::coordinate end);
    bool is_valid_move_bishop(Piece* p, Piece::coordinate end);    // used in is_valid_move
    bool is_valid_move_rook(Piece* p, Piece::coordinate end);  // used in is_valid_move

    Piece::coordinate white_king_pos;
    Piece::coordinate black_king_pos;

    static std::string coord_pos_translation(Piece::coordinate coord);
    static Piece::coordinate pos_coord_translation(std::string pos);
    static bool verify_valid_pos(std::string pos);
    static bool verify_valid_coord(Piece::coordinate coord);

    void show();
    void show_colour();
};


#endif //CHESS_BOARD_H
