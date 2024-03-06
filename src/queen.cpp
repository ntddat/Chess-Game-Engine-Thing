#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/queen.hpp"

using namespace std;

#define EMPTY 0
#define KING 6
#define CHESS_SIDE 8
#define SQUARE_SIDE 90

Queen::~Queen() {

}

vector<tuple<int, int>> Queen::getValidSquares(int state[CHESS_SIDE][CHESS_SIDE]) {
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

bool Queen::makeMove(int state[CHESS_SIDE][CHESS_SIDE], int mouseX, int mouseY) {
  vector<tuple<int, int>> validSquares = this->getValidSquares(state);
  for (int i = 0; i < validSquares.size(); i++) {
    int currX = get<0>(validSquares[i]);
    int currY = get<1>(validSquares[i]);
    if (currX*SQUARE_SIDE <= mouseX && mouseX <= currX*SQUARE_SIDE + SQUARE_SIDE &&
        currY*SQUARE_SIDE <= mouseY && mouseY <= currY*SQUARE_SIDE + SQUARE_SIDE) {
      changeState(state, squareX, squareY, currX, currY, isWhite);

      squareX = currX;
      squareY = currY;
      return true;
    }
  }
  return false;
}
