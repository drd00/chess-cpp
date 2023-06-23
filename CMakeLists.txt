cmake_minimum_required(VERSION 3.25)
project(chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess main.cpp Piece.h Bishop.h King.h Knight.h Pawn.h Queen.h Rook.h Board.cpp Board.h)
