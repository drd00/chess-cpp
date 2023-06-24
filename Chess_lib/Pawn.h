#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(PieceColour colour) : Piece(colour, PieceType::PAWN) {
        this->id = 'P';
    }

    bool poss_move(coordinate start, coordinate end) override {
        // in starting position?
        int starting_row_white = 1;
        int starting_row_black = 6;

        if (this->get_colour() == PieceColour::WHITE) {
            bool is_starting = start.y == starting_row_white;
            bool valid_pawn_move = (start.x == end.x)
                    && (end.y == start.y + 1 || (end.y == start.y + 2 && is_starting));

            return valid_pawn_move;
        } else if (this->get_colour() == PieceColour::BLACK) {
            bool is_starting = start.y == starting_row_black;
            bool valid_pawn_move = (start.x == end.x)
                    && (end.y == start.y - 1 || (end.y == start.y - 2 && is_starting));

            return valid_pawn_move;
        }

        return false;
    }

    bool poss_capture(coordinate start, coordinate end) override {
        // TODO: account for en passant capture
        if (this->get_colour() == PieceColour::WHITE) {
            return (end.y == start.y + 1) && (end.x == start.x + 1 || end.x == start.x - 1);
        } else if (this->get_colour() == PieceColour::BLACK) {
            return (end.y == start.y - 1) && (end.x == start.x + 1 || end.x == start.x - 1);
        }

        return false;
    }
};

#endif //CHESS_PAWN_H
