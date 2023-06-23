#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(PieceColour colour) : Piece(colour, PieceType::KNIGHT) {
        this->id = 'N';
    }

    bool poss_move(coordinate start, coordinate end) override {
        bool shape_1 = ((end.y == start.y + 2) || (end.y == start.y - 2))
                && ((end.x == start.x + 1) || (end.x == start.x - 1));

        bool shape_2 = ((end.y == start.y + 1) || (end.y == start.y - 1))
                && ((end.x == start.x + 2) || (end.x == start.x - 2));

        return shape_1 || shape_2;
    }

    bool poss_capture(coordinate start, coordinate end) override {
        return poss_move(start, end);
    }
};

#endif //CHESS_KNIGHT_H
