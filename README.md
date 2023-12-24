# Chess-CPP
This C++ project implements a chess game in the command-line.

## Build
The program can be compiled using CMake.
1. `git clone https://github.com/drd00/chess-cpp.git && cd chess-cpp`
2. `git clone https://github.com/google/googletest.git Google_tests/lib`
3. `cmake CMakeLists.txt`
4. `make`

This is automated in the `build.sh` script; simply `./build.sh`.

## Run
Once compiled, run using `./Chess_run`.

## Outstanding issues (which I'm aware of)
1. For some reason, after a move is made, a string of `0` characters appears in the first line of the output, and I can't find what exactly is causing this.
2. En-passant capture is still not possible.

