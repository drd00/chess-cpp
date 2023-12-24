#!/bin/bash
GTEST_LIB_DIR="./Google_tests/lib"
GTEST_GIT="https://github.com/google/googletest.git"

if [ -d "$GTEST_LIB_DIR" ]; then
  echo "GTEST_LIB_DIR exists."
else
  echo "GTEST_LIB_DIR does not exist. Cloning."
  git clone $GTEST_GIT $GTEST_LIB_DIR
fi

cmake CMakeLists.txt
make

