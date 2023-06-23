#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include "Piece.h"
#include <string>
#include <unordered_map>

class Board {
public:
    Board();
    ~Board() = default;
    std::vector<std::vector<Piece*>> chess_board;

    /**
     * is_valid_move: making use of the Piece movement possibility functions (poss_move and poss_capture)
     * Consider the board and whether this piece may actually make such a move --- whether there are obstructions, other
     * pieces and their colours, etc., whether the end position is within board bounds, etc.
     * @param p
     * @param start
     * @param end
     * @return bool whether a move for Piece p is from
     */
    bool is_valid_move(Piece* p, Piece::coordinate start, Piece::coordinate end);
    static std::string coord_pos_translation(Piece::coordinate coord);
    static Piece::coordinate pos_coord_translation(std::string pos);
    static bool verify_valid_pos(std::string pos);
    static bool verify_valid_coord(Piece::coordinate coord);

    std::string print_board();

    void show();
};


#endif //CHESS_BOARD_H
