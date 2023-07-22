
#include <gtest/gtest.h>
#include "Piece.h"
#include "Board.h"
#include "Rook.h"
#include "Pawn.h"

TEST(RookMoveTest, RookClearanceTest) {

    /*
     * Verify can only move forward if way is clear
     */
    auto *b = new Board(0);
    auto *rw = new Rook(Piece::PieceColour::WHITE);
    rw->coord = { 3, 3 };

    ASSERT_TRUE(b->is_valid_move(rw, {3, 7}));
    ASSERT_TRUE(b->is_valid_move(rw, {3, 0}));
    ASSERT_TRUE(b->is_valid_move(rw, {0, 3}));
    ASSERT_TRUE(b->is_valid_move(rw, {7, 3}));

    b->chess_board[3][5] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(rw, {3, 7}));
    b->chess_board[3][5] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(rw, {3, 7}));

    b->chess_board[3][1] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(rw, {3, 0}));
    b->chess_board[3][1] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(rw, {3, 0}));

    b->chess_board[1][3] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(rw, {0, 3}));
    b->chess_board[1][3] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(rw, {0, 3}));

    b->chess_board[6][3] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(rw, {7, 3}));
    b->chess_board[6][3] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(rw, {7, 3}));

    delete b;
    delete rw;
}

TEST(RookMoveTest, RookEnemyPiece) {
    auto *b = new Board(0);
    auto *rw = new Rook(Piece::PieceColour::WHITE);
    rw->coord = { 3, 3 };

    b->chess_board[3][5] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_TRUE(b->is_valid_move(rw, {3, 5}));
    delete rw;


    auto *rb = new Rook(Piece::PieceColour::BLACK);
    rb->coord = { 3, 3 };
    b->chess_board[3][5] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_TRUE(b->is_valid_move(rb, {3, 5}));
    delete rb;

    delete b;
}

TEST(RookMoveTest, RookFriendlyPiece) {
    auto *b = new Board(0);
    auto *rw = new Rook(Piece::PieceColour::WHITE);
    rw->coord = { 3, 3 };

    b->chess_board[3][5] = new Pawn(Piece::PieceColour::WHITE);
    ASSERT_FALSE(b->is_valid_move(rw, {3, 5}));
    delete rw;

    auto *rb = new Rook(Piece::PieceColour::BLACK);
    rb->coord = { 3, 3 };
    b->chess_board[3][5] = new Pawn(Piece::PieceColour::BLACK);
    ASSERT_FALSE(b->is_valid_move(rb, {3, 5}));
    delete rb;

    delete b;
}

TEST(RookMoveTest, RookBoundsTest) {
    auto *b = new Board(0);
    auto *rw = new Rook(Piece::PieceColour::WHITE);
    rw->coord = { 3, 3 };

    ASSERT_FALSE(b->is_valid_move(rw, {-1, 3}));
    ASSERT_FALSE(b->is_valid_move(rw, {8, 3}));
    ASSERT_FALSE(b->is_valid_move(rw, {3, -1}));
    ASSERT_FALSE(b->is_valid_move(rw, {3, 8}));

    delete b;
    delete rw;
}