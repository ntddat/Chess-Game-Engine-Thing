#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/bishop.hpp"

using namespace std;

#define CHESS_SIDE 8
#define EMPTY 0
#define KING 6

Bishop::~Bishop() {

}

vector<tuple<int, int>> Bishop::getValidSquares(int state[CHESS_SIDE][CHESS_SIDE]) {
  vector<tuple<int, int>> validSquares;
  int thisPiece = state[squareY][squareX];

  for (int i = 1; squareX + i <= CHESS_SIDE - 1 && squareY + i <= CHESS_SIDE - 1; i++) {
    if (state[squareY + i][squareX + i]*thisPiece <= EMPTY) {
      if (abs(state[squareY + i][squareX + i]) != KING) {
        validSquares.push_back(make_tuple(squareX + i, squareY + i));
      }
      if (state[squareY + i][squareX + i]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  for (int i = 1; squareX - i >= 0 && squareY + i <= CHESS_SIDE - 1; i++) {
    if (state[squareY + i][squareX - i]*thisPiece <= EMPTY) {
      if (abs(state[squareY + i][squareX - i]) != KING) {
        validSquares.push_back(make_tuple(squareX - i, squareY + i));
      }
      if (state[squareY + i][squareX - i]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  for (int i = 1; squareX + i <= CHESS_SIDE - 1 && squareY - i >= 0; i++) {
    if (state[squareY - i][squareX + i]*thisPiece <= EMPTY) {
      if (abs(state[squareY - i][squareX + i]) != KING) {
        validSquares.push_back(make_tuple(squareX + i, squareY - i));
      }
      if (state[squareY - i][squareX + i]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  for (int i = 1; squareX - i >= 0 && squareY - i >= 0; i++) {
    if (state[squareY - i][squareX - i]*thisPiece <= EMPTY) {
      if (abs(state[squareY - i][squareX - i]) != KING) {
        validSquares.push_back(make_tuple(squareX - i, squareY - i));
      }
      if (state[squareY - i][squareX - i]*thisPiece < EMPTY) {
        break;
      }
    } 
    else {
      break;
    }
  }

  return validSquares;
}
