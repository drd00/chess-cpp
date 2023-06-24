cmake_minimum_required(VERSION 3.25)
project(chess)

set(CMAKE_CXX_STANDARD 17)
set(
        HEADER_FILES
            Piece.h
            Bishop.h
            King.h
            Knight.h
            Pawn.h
            Queen.h
            Rook.h
)

set(
        SOURCE_FILES
            Board.cpp
)

add_library(Chess_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
