#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(PieceColour colour) : Piece(colour, PieceType::ROOK) {
        this->id = 'R';
        has_moved = false;
    }

    bool has_moved;

    bool poss_move(coordinate start, coordinate end) override {
        bool moved = (start.x != end.x) || (start.y != end.y);

        return moved && (start.x == end.x || start.y == end.y);
    }

    bool poss_capture(coordinate start, coordinate end) override {
        return poss_move(start, end);
    }
};

#endif //CHESS_ROOK_H
