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
#define PAWN 1
#define SQUARE_SIDE 90
#define CHESS_SIDE 8

#define TWO_SQUARES 2

Pawn::~Pawn() {

}

void Pawn::setHasMoved(bool value) {
  hasMoved = value;
}

void Pawn::setEnPassant(bool value, int num) {
  enPassantAble = value;
  enPassantNum = num;
}

bool Pawn::getHasMoved() {
  return hasMoved;
}

bool Pawn::getEnPassant() {
  return enPassantAble;
}

vector<tuple<int, int>> Pawn::getValidSquares(int state[CHESS_SIDE][CHESS_SIDE]) {
  vector<tuple<int, int>> validSquares;
  int dir;
  if (isWhite) {dir = NEG;}
  else {dir = POS;}
  // Moving up 1 square
  if (0 <= squareY + dir && squareY + dir <= CHESS_SIDE - 1 &&
      0 <= squareX && squareX <= CHESS_SIDE - 1 &&
      state[squareY + dir][squareX] == EMPTY &&
      !kingInCheck(state, squareX, squareY + dir, squareX, squareY, false)) {
    validSquares.push_back(make_tuple(squareX, squareY + dir));
  }
  // Moving up 2 squares (if the pawn hasn't moved yet)
  if (0 <= squareY + 2*dir && squareY + 2*dir <= CHESS_SIDE - 1 && 
      0 <= squareX && squareX <= CHESS_SIDE - 1 && !hasMoved && 
      state[squareY + dir][squareX] == EMPTY &&
      state[squareY + 2*dir][squareX] == EMPTY &&
      !kingInCheck(state, squareX, squareY + 2*dir, squareX, squareY, false)) {
    validSquares.push_back(make_tuple(squareX, squareY + 2*dir));
  }
  // Capturing diagionally (if there are pieces to be captured)
  if (0 <= squareY + dir && squareY + dir <= CHESS_SIDE - 1 &&
      0 <= squareX - 1 && squareX - 1 <= CHESS_SIDE - 1 &&
      state[squareY + dir][squareX - 1]*dir > EMPTY &&
      abs(state[squareY + dir][squareX - 1]) != KING &&
      !kingInCheck(state, squareX - 1, squareY + dir, squareX, squareY, false)) {
    validSquares.push_back(make_tuple(squareX - 1, squareY + dir));
  }
  if (0 <= squareY + dir && squareY + dir <= CHESS_SIDE - 1 &&
      0 <= squareX + 1 && squareX + 1 <= CHESS_SIDE - 1 &&
      state[squareY + dir][squareX + 1]*dir > EMPTY &&
      abs(state[squareY + dir][squareX + 1]) != KING &&
      !kingInCheck(state, squareX + 1, squareY + dir, squareX, squareY, false)) {
    validSquares.push_back(make_tuple(squareX + 1, squareY + dir));
  }
  // En passant: *TO BE IMPLEMENTED*
  if (enPassantAble &&
      !kingInCheck(state, squareX + enPassantNum, squareY + dir, squareX, squareY, true)) {
    validSquares.push_back(make_tuple(squareX + enPassantNum, squareY + dir));
  }
  
  return validSquares;
}

bool Pawn::makeMove(int state[CHESS_SIDE][CHESS_SIDE], int mouseX, int mouseY, int *fiftyMoveCheck) {
  vector<tuple<int, int>> validSquares = this->getValidSquares(state);
  int dir;
  if (isWhite) {dir = NEG;}
  else {dir = POS;}
  for (int i = 0; i < validSquares.size(); i++) {
    int currX = get<0>(validSquares[i]);
    int currY = get<1>(validSquares[i]);
    if (currX*SQUARE_SIDE <= mouseX && mouseX <= currX*SQUARE_SIDE + SQUARE_SIDE &&
        currY*SQUARE_SIDE <= mouseY && mouseY <= currY*SQUARE_SIDE + SQUARE_SIDE) {
      if (!hasMoved) {hasMoved = true;}
      // If it is currently en passant
      if (enPassantAble) {
        this->setEnPassant(false, 0);
        if (abs(state[currY][currX]) == EMPTY &&
            abs(currX - squareX) == 1 && abs(currY - squareY) == 1) {
          if (isWhite) {
            capturePiece(bPArr, currX, currY - dir);
            state[currY - dir][currX] = EMPTY;
          }
          else {
            capturePiece(wPArr, currX, currY - dir);
            state[currY - dir][currX] = EMPTY;
          }
        }
      }
      // Activate en passant for enemy pawns if possible
      if (abs(squareY - currY) == TWO_SQUARES) {
        if (abs(state[currY][currX - 1]) == PAWN &&
            state[currY][currX - 1]*state[squareY][squareX] < EMPTY) {
          if (isWhite) {
            activateEnPassant(bPArr, currX - 1, currY, POS);
          }
          else {
            activateEnPassant(wPArr, currX - 1, currY, POS);
          }
        }
        if (abs(state[currY][currX + 1]) == PAWN &&
            state[currY][currX + 1]*state[squareY][squareX] < EMPTY) {
          if (isWhite) {
            activateEnPassant(bPArr, currX + 1, currY, NEG);
          }
          else {
            activateEnPassant(wPArr, currX + 1, currY, NEG);
          }
        }
      }
      
      changeState(state, squareX, squareY, currX, currY, isWhite, fiftyMoveCheck);
      *fiftyMoveCheck = 0;

      squareX = currX;
      squareY = currY;
      return true;
    }
  }
  return false;
}

void Pawn::activateEnPassant(vector<shared_ptr<Piece>> arr, int currX, int currY, int value) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i]->getSquareX() == currX &&
        arr[i]->getSquareY() == currY) {
      arr[i]->setEnPassant(true, value);
      break;
    }
  }
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
