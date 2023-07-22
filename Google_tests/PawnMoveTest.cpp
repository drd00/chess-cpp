
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
    pw->coord = { 0, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {0, 3}));
    pw->coord = { 1, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {1, 3}));
    pw->coord = { 2, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {2, 3}));
    pw->coord = { 3, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {3, 3}));
    pw->coord = { 4, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {4, 3}));
    pw->coord = { 5, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {5, 3}));
    pw->coord = { 6, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {6, 3}));
    pw->coord = { 7, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {7, 3}));

    /*
     * Black pawns can move forward two from starting position
     */
    pb->coord = { 0, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {0, 4}));
    pb->coord = { 1, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {1, 4}));
    pb->coord = { 2, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {2, 4}));
    pb->coord = { 3, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {3, 4}));
    pb->coord = { 4, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {4, 4}));
    pb->coord = { 5, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {5, 4}));
    pb->coord = { 6, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {6, 4}));
    pb->coord = { 7, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {7, 4}));

    /*
     * White pawns cannot move forward two from a non-starting position
     */
    pw->coord = { 0, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {0, 4}));
    pw->coord = { 1, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {1, 4}));
    pw->coord = { 2, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {2, 4}));
    pw->coord = { 3, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {3, 4}));
    pw->coord = { 4, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {4, 4}));
    pw->coord = { 5, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {5, 4}));
    pw->coord = { 6, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {6, 4}));
    pw->coord = { 7, 2 };
    ASSERT_FALSE(b->is_valid_move(pw, {7, 4}));

    /*
     * Black pawns cannot move forward two from a non-starting position
     */
    pb->coord = { 0, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {0, 3}));
    pb->coord = { 1, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {1, 3}));
    pb->coord = { 2, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {2, 3}));
    pb->coord = { 3, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {3, 3}));
    pb->coord = { 4, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {4, 3}));
    pb->coord = { 5, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {5, 3}));
    pb->coord = { 6, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {6, 3}));
    pb->coord = { 7, 5 };
    ASSERT_FALSE(b->is_valid_move(pb, {7, 3}));

    delete b;
    delete pw;
    delete pb;
}

TEST(PawnMoveTest, PawnMoveBack) {
    auto *b = new Board(0);
    auto *pw = new Pawn(Piece::PieceColour::WHITE);
    auto *pb = new Pawn(Piece::PieceColour::BLACK);

    pw->coord = { 3, 3 };
    ASSERT_FALSE(b->is_valid_move(pw, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 1}));

    pb->coord = { 3, 3 };
    ASSERT_FALSE(b->is_valid_move(pb, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 5}));

    delete b;
    delete pw;
    delete pb;
}

TEST(PawnMoveTest, PawnBoundsTest) {
    auto *b = new Board(0);
    auto *pw = new Pawn(Piece::PieceColour::WHITE);
    auto *pb = new Pawn(Piece::PieceColour::BLACK);

    pw->coord = { 0, 0 };
    ASSERT_FALSE(b->is_valid_move(pw, {-1, 1}));
    pw->coord = { 7, 0 };
    ASSERT_FALSE(b->is_valid_move(pw, {8, 1}));

    pb->coord = { 0, 7 };
    ASSERT_FALSE(b->is_valid_move(pb, {-1, 6}));
    pb->coord = { 7, 7 };
    ASSERT_FALSE(b->is_valid_move(pb, {8, 6}));

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
    pw->coord = { 1, 1 };
    ASSERT_TRUE(b->is_valid_move(pw, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(pw, {1, 3}));
    b->chess_board[1][2] = new Pawn(Piece::PieceColour::WHITE);

    ASSERT_FALSE(b->is_valid_move(pw, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {1, 3}));
    b->chess_board[1][3] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(pw, {1, 3}));
    b->chess_board[1][2] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pw, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {1, 3}));
    b->chess_board[1][3] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pw, {1, 3}));

    // black
    pb->coord = { 0, 6 };
    ASSERT_TRUE(b->is_valid_move(pb, {0, 5}));
    ASSERT_TRUE(b->is_valid_move(pb, {0, 4}));
    b->chess_board[0][5] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 5}));
    ASSERT_FALSE(b->is_valid_move(pb, {0, 4}));
    b->chess_board[0][4] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 4}));
    b->chess_board[0][5] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 5}));
    ASSERT_FALSE(b->is_valid_move(pb, {0, 4}));
    b->chess_board[0][4] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(pb, {0, 4}));

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

    pw->coord = { 3, 3 };
    pb->coord = { 3, 3 };
    ASSERT_FALSE(b->is_valid_move(pw, {4, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {2, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {2, 2}));
    ASSERT_FALSE(b->is_valid_move(pb, {4, 2}));

    b->chess_board[4][4] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[2][4] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[2][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][2] = new Pawn(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(pw, {4, 4}));
    ASSERT_TRUE(b->is_valid_move(pw, {2, 4}));
    ASSERT_TRUE(b->is_valid_move(pb, {2, 2}));
    ASSERT_TRUE(b->is_valid_move(pb, {4, 2}));

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
    pw->coord = { 3, 3 };
    pb->coord = { 3, 3 };
    ASSERT_FALSE(b->is_valid_move(pw, {2, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {2, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {4, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {4, 2}));
    // black
    ASSERT_FALSE(b->is_valid_move(pb, {2, 2}));
    ASSERT_FALSE(b->is_valid_move(pb, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {2, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {4, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {4, 2}));

    // rook moves
    // white
    ASSERT_TRUE(b->is_valid_move(pw, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 5}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 6}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 7}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 1}));
    ASSERT_FALSE(b->is_valid_move(pw, {3, 0}));
    // black
    ASSERT_FALSE(b->is_valid_move(pb, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 5}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 6}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 7}));
    ASSERT_TRUE(b->is_valid_move(pb, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 1}));
    ASSERT_FALSE(b->is_valid_move(pb, {3, 0}));

    // bishop moves
    // white
    ASSERT_FALSE(b->is_valid_move(pw, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {1, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {0, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {5, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {6, 3}));
    ASSERT_FALSE(b->is_valid_move(pw, {7, 3}));
    // black
    ASSERT_FALSE(b->is_valid_move(pb, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {1, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {0, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {5, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {6, 3}));
    ASSERT_FALSE(b->is_valid_move(pb, {7, 3}));

    delete b;
    delete pw;
    delete pb;
}