#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <iostream>
#include <SDL2/SDL.h>

#include "../include/knight.hpp"

using namespace std;

#define CHESS_SIDE 8
#define EMPTY 0
#define KING 6

Knight::~Knight() {

}

vector<tuple<int, int>> Knight::getValidSquares(int state[8][8]) {
  vector<tuple<int, int>> validSquares;
  int thisPiece = state[squareY][squareX];
  if (0 <= squareX + 2 && squareX + 2 <= CHESS_SIDE - 1) {
    if (0 <= squareY + 1 && squareY + 1 <= CHESS_SIDE - 1 &&
        state[squareY + 1][squareX + 2]*thisPiece <= EMPTY &&
        abs(state[squareY + 1][squareX + 2]) != KING) {
      validSquares.push_back(make_tuple(squareX + 2, squareY + 1));
    }
    if (0 <= squareY - 1 && squareY - 1 <= CHESS_SIDE - 1 &&
        state[squareY - 1][squareX + 2]*thisPiece <= EMPTY &&
        abs(state[squareY - 1][squareX + 2]) != KING) {
      validSquares.push_back(make_tuple(squareX + 2, squareY - 1));
    }
  }
  
  if (0 <= squareX - 2 && squareX - 2 <= CHESS_SIDE - 1) {
    if (0 <= squareY + 1 && squareY + 1 <= CHESS_SIDE - 1 &&
        state[squareY + 1][squareX - 2]*thisPiece <= EMPTY &&
        abs(state[squareY + 1][squareX - 2]) != KING) {
      validSquares.push_back(make_tuple(squareX - 2, squareY + 1));
    }
    if (0 <= squareY - 1 && squareY - 1 <= CHESS_SIDE - 1 &&
        state[squareY - 1][squareX - 2]*thisPiece <= EMPTY &&
        abs(state[squareY - 1][squareX - 2]) != KING) {
      validSquares.push_back(make_tuple(squareX - 2, squareY - 1));
    }
  }

  if (0 <= squareY + 2 && squareY + 2 <= CHESS_SIDE - 1) {
    if (0 <= squareX + 1 && squareX + 1 <= CHESS_SIDE - 1 &&
        state[squareY + 2][squareX + 1]*thisPiece <= EMPTY &&
        abs(state[squareY + 2][squareX + 1]) != KING) {
      validSquares.push_back(make_tuple(squareX + 1, squareY + 2));
    }
    if (0 <= squareX - 1 && squareX - 1 <= CHESS_SIDE - 1 &&
        state[squareY + 2][squareX - 1]*thisPiece <= EMPTY &&
        abs(state[squareY + 2][squareX - 1]) != KING) {
      validSquares.push_back(make_tuple(squareX - 1, squareY + 2));
    }
  }

  if (0 <= squareY - 2 && squareY - 2 <= CHESS_SIDE) {
    if (0 <= squareX + 1 && squareX + 1 <= CHESS_SIDE - 1 &&
        state[squareY - 2][squareX + 1]*thisPiece <= EMPTY &&
        abs(state[squareY - 2][squareX + 1]) != KING) {
      validSquares.push_back(make_tuple(squareX + 1, squareY - 2));
    }
    if (0 <= squareX - 1 && squareX - 1 <= CHESS_SIDE - 1 &&
        state[squareY - 2][squareX - 1]*thisPiece <= EMPTY &&
        abs(state[squareY - 2][squareX - 1]) != KING) {
      validSquares.push_back(make_tuple(squareX - 1, squareY - 2));
    }
  }

  return validSquares;
}
