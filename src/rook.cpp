#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/rook.hpp"

using namespace std;

#define CHESS_SIDE 8
#define KING 6
#define EMPTY 0

Rook::~Rook() {

}

vector<tuple<int, int>> Rook::getValidSquares(int state[CHESS_SIDE][CHESS_SIDE]) {
  vector<tuple<int, int>> validSquares;
  int thisPiece = state[squareY][squareX];

  for (int i = 1; squareX + i <= CHESS_SIDE - 1; i++) {
    if (state[squareY][squareX + i]*thisPiece <= EMPTY) {
      if (abs(state[squareY][squareX + i]) != KING) {
        validSquares.push_back(make_tuple(squareX + i, squareY));
      }
      if (state[squareY][squareX + i]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  for (int i = 1; squareY + i <= CHESS_SIDE - 1; i++) {
    if (state[squareY + i][squareX]*thisPiece <= EMPTY) {
      if (abs(state[squareY + i][squareX]) != KING) {
        validSquares.push_back(make_tuple(squareX, squareY + i));
      }
      if (state[squareY + i][squareX]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  for (int i = 1; squareX - i >= 0; i++) {
    if (state[squareY][squareX - i]*thisPiece <= EMPTY) {
      if (abs(state[squareY][squareX - i]) != KING) {
        validSquares.push_back(make_tuple(squareX - i, squareY));
      }
      if (state[squareY][squareX - i]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  for (int i = 1; squareY - i >= 0; i++) {
    if (state[squareY - i][squareX]*thisPiece <= EMPTY) {
      if (abs(state[squareY - i][squareX]) != KING) {
        validSquares.push_back(make_tuple(squareX, squareY - i));
      }
      if (state[squareY - i][squareX]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  return validSquares;
}
