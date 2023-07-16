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

    bool poss_move(coordinate end) override {
        coordinate start = coord;

        bool moved = (start.x != end.x) || (start.y != end.y);

        return moved && (start.x == end.x || start.y == end.y);
    }

    bool poss_capture(coordinate end) override {
        return poss_move(end);
    }

    Piece* clone() override {
        auto* r = new Rook(*this);

        return r;
    }
};

#endif //CHESS_ROOK_H
