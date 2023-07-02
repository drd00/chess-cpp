#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"
#include <cmath>

class Queen : public Piece {
public:
    Queen(PieceColour colour) : Piece(colour, PieceType::QUEEN) {
        this->id = 'Q';
    }

    /*
     * Check first whether the movement pattern of a rook
     * If not, return whether the movement pattern of a bishop
     */
    bool poss_move(coordinate start, coordinate end) override {
        bool moved = (start.x != end.x) || (start.y != end.y);
        bool poss_rook_moves = start.x == end.x || start.y == end.y;
        if (moved && poss_rook_moves) {
            return true;
        }

        // bishop movement pattern?
        int change_x = std::abs(start.x - end.x);
        int change_y = std::abs(start.y - end.y);

        return moved && (change_x == change_y);
    }

    bool poss_capture(coordinate start, coordinate end) override {
        return poss_move(start, end);
    }

    Piece* clone() override {
        auto* q = new Queen(*this);

        return q;
    }
};

#endif //CHESS_QUEEN_H
