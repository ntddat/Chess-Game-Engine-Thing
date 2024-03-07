#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/rook.hpp"

using namespace std;

#define SQUARE_SIDE 90
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
      if (abs(state[squareY][squareX + i]) != KING &&
          !kingInCheck(state, squareX + i, squareY, squareX, squareY, false)) {
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
      if (abs(state[squareY + i][squareX]) != KING &&
          !kingInCheck(state, squareX, squareY + i, squareX, squareY, false)) {
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
      if (abs(state[squareY][squareX - i]) != KING &&
          !kingInCheck(state, squareX - i, squareY, squareX, squareY, false)) {
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
      if (abs(state[squareY - i][squareX]) != KING &&
          !kingInCheck(state, squareX, squareY - 1, squareX, squareY, false)) {
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

bool Rook::makeMove(int state[CHESS_SIDE][CHESS_SIDE], int mouseX, int mouseY) {
  vector<tuple<int, int>> validSquares = this->getValidSquares(state);
  for (int i = 0; i < validSquares.size(); i++) {
    int currX = get<0>(validSquares[i]);
    int currY = get<1>(validSquares[i]);
    if (currX*SQUARE_SIDE <= mouseX && mouseX <= currX*SQUARE_SIDE + SQUARE_SIDE &&
        currY*SQUARE_SIDE <= mouseY && mouseY <= currY*SQUARE_SIDE + SQUARE_SIDE) {
      if (!hasMoved) {
        if (isWhite) {
          if (squareX == 0) {
            for (int i = 0; i < wPiecesArr.size(); i++) {
              if (abs(state[wPiecesArr[i]->getSquareY()][wPiecesArr[i]->getSquareX()]) == KING) {
                wPiecesArr[i]->setCastleQ(false);
                break;
              }
            }
          }
          else if (squareX == 7) {
            for (int i = 0; i < wPiecesArr.size(); i++) {
              if (abs(state[wPiecesArr[i]->getSquareY()][wPiecesArr[i]->getSquareX()]) == KING) {
                wPiecesArr[i]->setCastleK(false);
                break;
              }
            }
          }
        }
        else {
          if (squareX == 0) {
            for (int i = 0; i < bPiecesArr.size(); i++) {
              if (abs(state[bPiecesArr[i]->getSquareY()][bPiecesArr[i]->getSquareX()]) == KING) {
                bPiecesArr[i]->setCastleQ(false);
                break;
              }
            }
          }
          else if (squareX == 7) {
            for (int i = 0; i < bPiecesArr.size(); i++) {
              if (abs(state[bPiecesArr[i]->getSquareY()][bPiecesArr[i]->getSquareX()]) == KING) {
                bPiecesArr[i]->setCastleK(false);
                break;
              }
            }
          }

        }
        hasMoved = true;
      }
      changeState(state, squareX, squareY, currX, currY, isWhite);

      squareX = currX;
      squareY = currY;
      return true;
    }
  }
  return false;
}

