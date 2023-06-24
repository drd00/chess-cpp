
#include <gtest/gtest.h>
#include "Piece.h"
#include "Board.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"

/*
 * Knight movement
 */

/*  **PATTERN 1**
 *      bool shape_1 = ((end.y == start.y + 2) || (end.y == start.y - 2))
                && ((end.x == start.x + 1) || (end.x == start.x - 1));
        std::cout << shape_1;
 */
TEST(KnightMoveTest, KnightPattern1Jump) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);

    b->chess_board[2][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][2] = new Pawn(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {2, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {4, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {2, 1}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {4, 1}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern1EmptySquare) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {2, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {4, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {2, 1}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {4, 1}));

    delete b;
    delete k;
}

/*
 *  **PATTERN 2**
        bool shape_2 = ((end.y == start.y + 1) || (end.y == start.y - 1))
                && ((end.x == start.x + 2) || (end.x == start.x - 2));
        std::cout << shape_2;
*/
TEST(KnightMoveTest, KnightPattern2Jump) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);

    b->chess_board[2][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][2] = new Pawn(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {1, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {5, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {5, 2}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern2EmptySquare) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {1, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {5, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {5, 2}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern1FriendlyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);

    b->chess_board[2][5] = k;
    b->chess_board[4][5] = k;
    b->chess_board[2][1] = k;
    b->chess_board[4][1] = k;

    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {2, 5}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {4, 5}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {2, 1}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {4, 1}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern2FriendlyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);

    b->chess_board[1][4] = k;
    b->chess_board[5][4] = k;
    b->chess_board[1][2] = k;
    b->chess_board[5][2] = k;

    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {1, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {5, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 3}, {5, 2}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern1EnemyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    auto* enemy_piece = new Pawn(Piece::PieceColour::BLACK);

    b->chess_board[2][5] = enemy_piece;
    b->chess_board[4][5] = enemy_piece;
    b->chess_board[2][1] = enemy_piece;
    b->chess_board[4][1] = enemy_piece;

    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {2, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {4, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {2, 1}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {4, 1}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern2EnemyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    auto* enemy_piece = new Pawn(Piece::PieceColour::BLACK);

    b->chess_board[1][4] = enemy_piece;
    b->chess_board[5][4] = enemy_piece;
    b->chess_board[1][2] = enemy_piece;
    b->chess_board[5][2] = enemy_piece;

    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {1, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {5, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(k, {3, 3}, {5, 2}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightEdge) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);

    // pattern 1
    ASSERT_TRUE(b->is_valid_move(k, {0, 0}, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {0, 0}, {-1, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {0, 0}, {-1, -2}));
    ASSERT_FALSE(b->is_valid_move(k, {0, 0}, {1, -2}));

    // pattern 2
    ASSERT_TRUE(b->is_valid_move(k, {0, 0}, {2, 1}));
    ASSERT_FALSE(b->is_valid_move(k, {0, 0}, {-2, 1}));
    ASSERT_FALSE(b->is_valid_move(k, {0, 0}, {2, -1}));
    ASSERT_FALSE(b->is_valid_move(k, {0, 0}, {-2, -1}));
}

TEST(KnightMoveTest, KnightInvalidPatterns) {

}

TEST(KnightMoveTest, KnightBoardBounds) {

}
