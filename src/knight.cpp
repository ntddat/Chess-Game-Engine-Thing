#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <iostream>
#include <SDL2/SDL.h>

#include "../include/knight.hpp"

using namespace std;

#define CHESS_SIDE 8
#define SQUARE_SIDE 90
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
        abs(state[squareY + 1][squareX + 2]) != KING &&
        !kingInCheck(state, squareX + 2, squareY + 1, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX + 2, squareY + 1));
    }
    if (0 <= squareY - 1 && squareY - 1 <= CHESS_SIDE - 1 &&
        state[squareY - 1][squareX + 2]*thisPiece <= EMPTY &&
        abs(state[squareY - 1][squareX + 2]) != KING &&
        !kingInCheck(state, squareX + 2, squareY - 1, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX + 2, squareY - 1));
    }
  }
  
  if (0 <= squareX - 2 && squareX - 2 <= CHESS_SIDE - 1) {
    if (0 <= squareY + 1 && squareY + 1 <= CHESS_SIDE - 1 &&
        state[squareY + 1][squareX - 2]*thisPiece <= EMPTY &&
        abs(state[squareY + 1][squareX - 2]) != KING &&
        !kingInCheck(state, squareX - 2, squareY + 1, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX - 2, squareY + 1));
    }
    if (0 <= squareY - 1 && squareY - 1 <= CHESS_SIDE - 1 &&
        state[squareY - 1][squareX - 2]*thisPiece <= EMPTY &&
        abs(state[squareY - 1][squareX - 2]) != KING &&
        !kingInCheck(state, squareX - 2, squareY - 1, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX - 2, squareY - 1));
    }
  }

  if (0 <= squareY + 2 && squareY + 2 <= CHESS_SIDE - 1) {
    if (0 <= squareX + 1 && squareX + 1 <= CHESS_SIDE - 1 &&
        state[squareY + 2][squareX + 1]*thisPiece <= EMPTY &&
        abs(state[squareY + 2][squareX + 1]) != KING &&
        !kingInCheck(state, squareX + 1, squareY + 2, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX + 1, squareY + 2));
    }
    if (0 <= squareX - 1 && squareX - 1 <= CHESS_SIDE - 1 &&
        state[squareY + 2][squareX - 1]*thisPiece <= EMPTY &&
        abs(state[squareY + 2][squareX - 1]) != KING &&
        !kingInCheck(state, squareX - 1, squareY + 2, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX - 1, squareY + 2));
    }
  }

  if (0 <= squareY - 2 && squareY - 2 <= CHESS_SIDE) {
    if (0 <= squareX + 1 && squareX + 1 <= CHESS_SIDE - 1 &&
        state[squareY - 2][squareX + 1]*thisPiece <= EMPTY &&
        abs(state[squareY - 2][squareX + 1]) != KING &&
        !kingInCheck(state, squareX + 1, squareY - 2, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX + 1, squareY - 2));
    }
    if (0 <= squareX - 1 && squareX - 1 <= CHESS_SIDE - 1 &&
        state[squareY - 2][squareX - 1]*thisPiece <= EMPTY &&
        abs(state[squareY - 2][squareX - 1]) != KING &&
        !kingInCheck(state, squareX - 1, squareY - 2, squareX, squareY, false)) {
      validSquares.push_back(make_tuple(squareX - 1, squareY - 2));
    }
  }

  return validSquares;
}

bool Knight::makeMove(int state[CHESS_SIDE][CHESS_SIDE], int mouseX, int mouseY, int *fiftyMoveCheck, map<string, int> pastStates) {
  vector<tuple<int, int>> validSquares = this->getValidSquares(state);
  for (int i = 0; i < validSquares.size(); i++) {
    int currX = get<0>(validSquares[i]);
    int currY = get<1>(validSquares[i]);
    if (currX*SQUARE_SIDE <= mouseX && mouseX <= currX*SQUARE_SIDE + SQUARE_SIDE &&
        currY*SQUARE_SIDE <= mouseY && mouseY <= currY*SQUARE_SIDE + SQUARE_SIDE) {
      changeState(state, squareX, squareY, currX, currY, isWhite, fiftyMoveCheck, pastStates);

      squareX = currX;
      squareY = currY;
      return true;
    }
  }
  return false;
}
