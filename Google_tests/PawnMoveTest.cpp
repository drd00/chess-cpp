
#include <gtest/gtest.h>
#include "Board.h"
#include "Pawn.h"

TEST(PawnMoveTest, PawnPattern1EmptySquare) {
    auto *b = new Board(0);
    auto *pw = new Pawn(Piece::PieceColour::WHITE);
    auto *pb = new Pawn(Piece::PieceColour::BLACK);

    /*
     * White pawns can move forward two from starting position
     */
    ASSERT_TRUE(b->is_valid_move(pw, {0, 1}, {0, 3}));
    ASSERT_TRUE(b->is_valid_move(pw, {1, 1}, {1, 3}));
    ASSERT_TRUE(b->is_valid_move(pw, {2, 1}, {2, 3}));
    ASSERT_TRUE(b->is_valid_move(pw, {3, 1}, {3, 3}));
    ASSERT_TRUE(b->is_valid_move(pw, {4, 1}, {4, 3}));
    ASSERT_TRUE(b->is_valid_move(pw, {5, 1}, {5, 3}));
    ASSERT_TRUE(b->is_valid_move(pw, {6, 1}, {6, 3}));
    ASSERT_TRUE(b->is_valid_move(pw, {7, 1}, {7, 3}));

    /*
     * Black pawns can move forward two from starting position
     */
    ASSERT_TRUE(b->is_valid_move(pb, {0, 6}, {0, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {1, 6}, {1, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {2, 6}, {2, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {3, 6}, {3, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {4, 6}, {4, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {5, 6}, {5, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {6, 6}, {6, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {7, 6}, {7, 4}));

    /*
     * White pawns cannot move forward two from a non-starting position
     */
    ASSERT_FALSE(b->is_valid_move(pw, {0, 2}, {0, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {1, 2}, {1, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {2, 2}, {2, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 2}, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {4, 2}, {4, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {5, 2}, {5, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {6, 2}, {6, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {7, 2}, {7, 4}));

    /*
     * Black pawns cannot move forward two from a non-starting position
     */
    ASSERT_FALSE(b->is_valid_move(pb, {0, 5}, {0, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {1, 5}, {1, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {2, 5}, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 5}, {3, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {4, 5}, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {5, 5}, {5, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {6, 5}, {6, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {7, 5}, {7, 3}));

    delete b;
    delete pw;
    delete pb;
}

TEST(PawnMoveTest, PawnMoveBack) {
    auto *b = new Board(0);
    auto *pw = new Pawn(Piece::PieceColour::WHITE);
    auto *pb = new Pawn(Piece::PieceColour::BLACK);

    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 1}));

    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 5}));

    delete b;
    delete pw;
    delete pb;
}

TEST(PawnMoveTest, PawnBoundsTest) {
    auto *b = new Board(0);
    auto *pw = new Pawn(Piece::PieceColour::WHITE);
    auto *pb = new Pawn(Piece::PieceColour::BLACK);

    ASSERT_FALSE(b->is_valid_move(pw, {0, 0}, {-1, 1}));
    ASSERT_FALSE(b->is_valid_move(pw, {7, 0}, {8, 1}));

    ASSERT_FALSE(b->is_valid_move(pb, {0, 7}, {-1, 6}));
    ASSERT_FALSE(b->is_valid_move(pb, {7, 7}, {8, 6}));

    delete b;
    delete pw;
    delete pb;
}

TEST(PawnMoveTest, PawnClearanceTest) {

    /*
     * Verify can only move forward if way is clear
     */
    auto *b = new Board(0);
    auto *pw = new Pawn(Piece::PieceColour::WHITE);
    auto *pb = new Pawn(Piece::PieceColour::BLACK);

    // white
    ASSERT_TRUE(b->is_valid_move(pw, {1, 1}, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(pw, {1, 1}, {1, 3}));
    b->chess_board[1][2] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(pw, {1, 1}, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {1, 1}, {1, 3}));
    b->chess_board[1][3] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(pw, {1, 1}, {1, 3}));
    b->chess_board[1][2] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pw, {1, 1}, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {1, 1}, {1, 3}));
    b->chess_board[1][3] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pw, {1, 1}, {1, 3}));

    // black
    ASSERT_TRUE(b->is_valid_move(pb, {0, 6}, {0, 5}));
    ASSERT_TRUE(b->is_valid_move(pb, {0, 6}, {0, 4}));
    b->chess_board[0][5] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 6}, {0, 5}));
    ASSERT_FALSE(b->is_valid_move(pb, {0, 6}, {0, 4}));
    b->chess_board[0][4] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 6}, {0, 4}));
    b->chess_board[0][5] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 6}, {0, 5}));
    ASSERT_FALSE(b->is_valid_move(pb, {0, 6}, {0, 4}));
    b->chess_board[0][4] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 6}, {0, 4}));

    delete b;
    delete pw;
    delete pb;
}

TEST(PawnMoveTest, PawnCaptureTest) {
    /*
     *  Verify can only capture if there is an enemy piece in the square being moved to
     */
    auto *b = new Board(0);
    auto *pw = new Pawn(Piece::PieceColour::WHITE);
    auto *pb = new Pawn(Piece::PieceColour::BLACK);

    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {4,4}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {2,4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {2, 2}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {4, 2}));

    b->chess_board[4][4] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[2][4] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[2][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][2] = new Pawn(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(pw, {3, 3}, {4,4}));
    ASSERT_TRUE(b->is_valid_move(pw, {3, 3}, {2,4}));
    ASSERT_TRUE(b->is_valid_move(pb, {3, 3}, {2, 2}));
    ASSERT_TRUE(b->is_valid_move(pb, {3, 3}, {4, 2}));

    delete b;
    delete pw;
    delete pb;
}

TEST(PawnMoveTest, PawnInvalidPatterns) {
    auto* b = new Board(0);
    auto* pw = new Pawn(Piece::PieceColour::WHITE);
    auto* pb = new Pawn(Piece::PieceColour::BLACK);

    // king moves
    // white
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {2, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {2, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {4, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {4, 2}));
    // black
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {2, 2}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {2, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {4, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {4, 2}));

    // rook moves
    // white
    ASSERT_TRUE(b->is_valid_move(pw, {3, 3}, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 5}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 6}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 7}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 1}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {3, 0}));
    // black
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 5}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 6}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 7}));
    ASSERT_TRUE(b->is_valid_move(pb, {3, 3}, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 1}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {3, 0}));

    // bishop moves
    // white
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {1, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {0, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {5, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {6, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 3}, {7, 3}));
    // black
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {1, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {0, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {5, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {6, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}, {7, 3}));

    delete b;
    delete pw;
    delete pb;
}