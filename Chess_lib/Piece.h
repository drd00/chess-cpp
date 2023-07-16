#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <cstdio>
#include <unordered_map>

class Piece {
public:
    struct coordinate {
        int x;
        int y;
    };

    enum class PieceType {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING,
    };

    enum class PieceColour {
        WHITE,
        BLACK,
    };

    coordinate coord;

    Piece(PieceColour colour, PieceType type) {
        this->colour = colour;
        this->type = type;
    }

    virtual ~Piece() = default;

    PieceColour get_colour() {
        return colour;
    }

    PieceType get_type() {
        return type;
    }

    char get_id() {
        return id;
    }

    virtual Piece* clone() = 0;

    /**
     * poss_move: a pure virtual function which takes x and y
     * coordinates and outputs whether that move is technically possible
     * under any circumstances for this piece type
     * Does not account for board boundaries, other pieces, etc. - hence quite basic
     * @param end: the desired coordinate to move to
     * @return bool whether that change in coordinates is technically possible for
     * this piece type
     */
     virtual bool poss_move(coordinate end) = 0;

     /**
      * poss_capture: a pure virtual function which takes x and y
      * coordinates and outputs whether a capture is technically possible
      * under any circumstances
      * Does not account for board boundaries, other pieces, etc.
      * Should be the same as can_move_geo for all piece types except Pawn
      * @param end: the desired coordinate to capture
      * @return bool whether than change in coordinates (capturing) is technically
      * possible for this piece type
      */
      virtual bool poss_capture(coordinate end) = 0;


private:
    PieceColour colour;
    PieceType type;

protected:
    char id;    // displayed when the board contents are printed
};

#endif