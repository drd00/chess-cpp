#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"
#include <cmath>

class Bishop : public Piece {
public:
    Bishop(PieceColour colour) : Piece(colour, PieceType::BISHOP) {
        this->id = 'B';
    }

    bool poss_move(coordinate start, coordinate end) override {
        bool moved = (start.x != end.x) || (start.y != end.y);

        // if change in x == change in y
        int change_x = std::abs(start.x - end.x);
        int change_y = std::abs(start.y - end.y);

        return moved && (change_x == change_y);
    }

    bool poss_capture(coordinate start, coordinate end) override {
        return poss_capture(start, end);
    }

    Piece* clone() override {
        auto* b = new Bishop(*this);

        return b;
    }
};

#endif //CHESS_BISHOP_H
