#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"
#include <cmath>

class King : public Piece {
public:
    King(PieceColour colour) : Piece(colour, PieceType::KING) {
        this->id = 'K';
    }

    bool poss_move(coordinate start, coordinate end) override {
        bool moved = (start.x != end.x) || (start.y != end.y);

        return moved &&
            std::abs(start.x - end.x) <= 1 && std::abs(start.y - end.y) <= 1;
    }

    bool poss_capture(coordinate start, coordinate end) override {
        return poss_move(start, end);
    }
};

#endif //CHESS_KING_H
