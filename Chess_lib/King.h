#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"
#include <cmath>

class King : public Piece {
public:
    King(PieceColour colour) : Piece(colour, PieceType::KING) {
        this->id = 'K';
        has_moved = false;
    }

    bool has_moved;

    bool poss_move(coordinate end) override {
        coordinate start = coord;

        bool moved = (start.x != end.x) || (start.y != end.y);

        return moved &&
            std::abs(start.x - end.x) <= 1 && std::abs(start.y - end.y) <= 1;
    }

    bool poss_capture(coordinate end) override {
        return poss_move(end);
    }

    bool poss_castle_l(coordinate end) {
        coordinate start = coord;

        if (this->get_colour() == Piece::PieceColour::WHITE) {
            bool valid_start = start.x == 4 && start.y == 0;
            bool valid_end = (end.x == 2 && end.y == 0);

            return !has_moved && valid_start && valid_end;
        } else if (this->get_colour() == Piece::PieceColour::BLACK) {
            bool valid_start = start.x == 4 && start.y == 7;
            bool valid_end = (end.x == 2 && end.y == 7);

            return !has_moved && valid_start && valid_end;
        }

        return false;
    }

    bool poss_castle_r(coordinate end) {
        coordinate start = coord;

        if (this->get_colour() == Piece::PieceColour::WHITE) {
            bool valid_start = start.x == 4 && start.y == 0;
            bool valid_end = (end.x == 6 && end.y == 0);

            return !has_moved && valid_start && valid_end;
        } else if (this->get_colour() == Piece::PieceColour::BLACK) {
            bool valid_start = start.x == 4 && start.y == 7;
            bool valid_end = (end.x == 6 && end.y == 7);

            return !has_moved && valid_start && valid_end;
        }

        return false;
    }

    Piece* clone() override {
        auto* k = new King(*this);

        return k;
    }
};

#endif //CHESS_KING_H
