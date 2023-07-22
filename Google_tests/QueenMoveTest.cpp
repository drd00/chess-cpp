
#include <gtest/gtest.h>
#include "Piece.h"
#include "Board.h"
#include "Queen.h"
#include "Pawn.h"

TEST(QueenMoveTest, QueenRookMove) {
    auto *b = new Board(0);
    auto *q = new Queen(Piece::PieceColour::WHITE);
    q->coord = { 3, 3 };

    b->chess_board[3][5] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[3][5]->coord = { 5, 5 };

    ASSERT_TRUE(b->is_valid_move(q, { 3, 5 }));
}

TEST(QueenMoveTest, QueenBishopMove) {
    auto *b = new Board(0);
    auto *q = new Queen(Piece::PieceColour::WHITE);
    q->coord = { 3, 3 };

    b->chess_board[5][5] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[5][5]->coord = { 5, 5};

    ASSERT_TRUE(b->is_valid_move(q, {5, 5}));
}

