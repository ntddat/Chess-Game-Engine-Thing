#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <iostream>
#include <SDL2/SDL.h>

#include "../include/pawn.hpp"

using namespace std;

#define POS 1
#define NEG -1

#define KING 6
#define EMPTY 0
#define SQUARE_SIDE 90
#define CHESS_SIDE 8

Pawn::~Pawn() {

}

void Pawn::setHasMoved(bool value) {
  hasMoved = value;
}

bool Pawn::getHasMoved() {
  return hasMoved;
}

vector<tuple<int, int>> Pawn::getValidSquares(int state[CHESS_SIDE][CHESS_SIDE]) {
  vector<tuple<int, int>> validSquares;
  int dir;
  if (isWhite) {dir = NEG;}
  else {dir = POS;}
  // Moving up 1 square
  if (0 <= squareY + dir && squareY + dir <= CHESS_SIDE - 1 &&
      0 <= squareX && squareX <= CHESS_SIDE - 1 &&
      state[squareY + dir][squareX] == EMPTY) {
    validSquares.push_back(make_tuple(squareX, squareY + dir));
  }
  // Moving up 2 squares (if the pawn hasn't moved yet)
  if (0 <= squareY + 2*dir && squareY + 2*dir <= CHESS_SIDE - 1 && 
      0 <= squareX && squareX <= CHESS_SIDE - 1 && !hasMoved && 
      state[squareY + 2*dir][squareX] == EMPTY) {
    validSquares.push_back(make_tuple(squareX, squareY + 2*dir));
  }
  // Capturing diagionally (if there are pieces to be captured)
  if (0 <= squareY + dir && squareY + dir <= CHESS_SIDE - 1 &&
      0 <= squareX - 1 && squareX - 1 <= CHESS_SIDE - 1 &&
      state[squareY + dir][squareX - 1]*dir > EMPTY &&
      abs(state[squareY + dir][squareX - 1]) != KING) {
    validSquares.push_back(make_tuple(squareX - 1, squareY + dir));
  }
  if (0 <= squareY + dir && squareY + dir <= CHESS_SIDE - 1 &&
      0 <= squareX + 1 && squareX + 1 <= CHESS_SIDE - 1 &&
      state[squareY + dir][squareX + 1]*dir > EMPTY &&
      abs(state[squareY + dir][squareX + 1]) != KING) {
    validSquares.push_back(make_tuple(squareX + 1, squareY + dir));
  }
  // En passant: *TO BE IMPLEMENTED*
  
  return validSquares;
}

/*
bool Pawn::makeMove(int mouseX, int mouseY, int state[8][8]) {
  vector<tuple<int, int>> validSquares = this->getValidSquares(state);
  for (int i = 0; i < validSquares.size(); i++) {
    int currX = get<0>(validSquares[i])*SQUARE_SIDE;
    int currY = get<1>(validSquares[i])*SQUARE_SIDE;
    if (currX <= mouseX && mouseX <= currX + SQUARE_SIDE &&
        currY <= mouseY && mouseY <= currY + SQUARE_SIDE) {
      if (!hasMoved) {hasMoved = true;}
      if (state[get<1>(validSquares[i])][get<0>(validSquares[i])] == EMPTY) {
        int temp = state[get<1>(validSquares[i])][get<0>(validSquares[i])];
        state[get<1>(validSquares[i])][get<0>(validSquares[i])] = state[squareY][squareX];
        state[squareY][squareX] = temp;
      }
      else {
        state[get<1>(validSquares[i])][get<0>(validSquares[i])] = state[squareY][squareX];
        state[squareY][squareX] = EMPTY;
      }
      squareX = get<0>(validSquares[i]);
      squareY = get<1>(validSquares[i]);
      return true;
    }
  }
  return false;
}
*/
