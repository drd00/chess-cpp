
#include <gtest/gtest.h>
#include "Piece.h"
#include "Board.h"
#include "Knight.h"
#include "Pawn.h"

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
    k->coord = { 3, 3 };

    b->chess_board[2][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][2] = new Pawn(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(k, {2, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {4, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {2, 1}));
    ASSERT_TRUE(b->is_valid_move(k, {4, 1}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern1EmptySquare) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 3, 3 };

    ASSERT_TRUE(b->is_valid_move(k, {2, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {4, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {2, 1}));
    ASSERT_TRUE(b->is_valid_move(k, {4, 1}));

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
    k->coord = { 3, 3 };

    b->chess_board[2][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[2][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[3][2] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][4] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][3] = new Pawn(Piece::PieceColour::WHITE);
    b->chess_board[4][2] = new Pawn(Piece::PieceColour::WHITE);

    ASSERT_TRUE(b->is_valid_move(k, {1, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {5, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(k, {5, 2}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern2EmptySquare) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 3, 3 };

    ASSERT_TRUE(b->is_valid_move(k, {1, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {5, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(k, {5, 2}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern1FriendlyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 3, 3 };

    b->chess_board[2][5] = new Knight(Piece::PieceColour::WHITE);
    b->chess_board[4][5] = new Knight(Piece::PieceColour::WHITE);
    b->chess_board[2][1] = new Knight(Piece::PieceColour::WHITE);
    b->chess_board[4][1] = new Knight(Piece::PieceColour::WHITE);

    ASSERT_FALSE(b->is_valid_move(k, {2, 5}));
    ASSERT_FALSE(b->is_valid_move(k, {4, 5}));
    ASSERT_FALSE(b->is_valid_move(k, {2, 1}));
    ASSERT_FALSE(b->is_valid_move(k, {4, 1}));

    delete b;
}

TEST(KnightMoveTest, KnightPattern2FriendlyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 3, 3 };

    b->chess_board[1][4] = new Knight(Piece::PieceColour::WHITE);
    b->chess_board[5][4] = new Knight(Piece::PieceColour::WHITE);
    b->chess_board[1][2] = new Knight(Piece::PieceColour::WHITE);
    b->chess_board[5][2] = new Knight(Piece::PieceColour::WHITE);

    ASSERT_FALSE(b->is_valid_move(k, {1, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {5, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {5, 2}));

    delete b;
}

TEST(KnightMoveTest, KnightPattern1EnemyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 3, 3 };

    b->chess_board[2][5] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[4][5] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[2][1] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[4][1] = new Pawn(Piece::PieceColour::BLACK);

    ASSERT_TRUE(b->is_valid_move(k, {2, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {4, 5}));
    ASSERT_TRUE(b->is_valid_move(k, {2, 1}));
    ASSERT_TRUE(b->is_valid_move(k, {4, 1}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightPattern2EnemyPiece) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 3, 3 };

    b->chess_board[1][4] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[5][4] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[1][2] = new Pawn(Piece::PieceColour::BLACK);
    b->chess_board[5][2] = new Pawn(Piece::PieceColour::BLACK);

    ASSERT_TRUE(b->is_valid_move(k, {1, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {5, 4}));
    ASSERT_TRUE(b->is_valid_move(k, {1, 2}));
    ASSERT_TRUE(b->is_valid_move(k, {5, 2}));

    delete b;
    delete k;
}

TEST(KnightMoveTest, KnightEdge) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 0, 0 };

    // pattern 1
    ASSERT_TRUE(b->is_valid_move(k, {1, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {-1, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {-1, -2}));
    ASSERT_FALSE(b->is_valid_move(k, {1, -2}));

    // pattern 2
    ASSERT_TRUE(b->is_valid_move(k, {2, 1}));
    ASSERT_FALSE(b->is_valid_move(k, {-2, 1}));
    ASSERT_FALSE(b->is_valid_move(k, {2, -1}));
    ASSERT_FALSE(b->is_valid_move(k, {-2, -1}));
}

TEST(KnightMoveTest, KnightInvalidPatterns) {
    auto* b = new Board(0);
    auto* k = new Knight(Piece::PieceColour::WHITE);
    k->coord = { 3, 3 };
    /*
     * A Knight cannot move in the same pattern as any other Piece type
     */

    // pawn moves
    ASSERT_FALSE(b->is_valid_move(k, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 5}));

    // king moves
    ASSERT_FALSE(b->is_valid_move(k, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {2, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {2, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {4, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {4, 2}));

    // rook moves
    ASSERT_FALSE(b->is_valid_move(k, {3, 4}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 5}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 6}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 7}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 2}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 1}));
    ASSERT_FALSE(b->is_valid_move(k, {3, 0}));

    // bishop moves
    ASSERT_FALSE(b->is_valid_move(k, {2, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {1, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {0, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {4, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {5, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {6, 3}));
    ASSERT_FALSE(b->is_valid_move(k, {7, 3}));

    delete b;
    delete k;
}
