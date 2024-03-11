#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <map>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"
#include "../include/piece.hpp"

using namespace std;

#define EMPTY 0
#define PAWN 1
#define KNIGHT 2  
#define BISHOP 3
#define ROOK 4
#define QUEEN 5 
#define KING 6
#define PIECE_SIDE 90
#define CHESS_SIDE 8
#define WHITE_PAWN_ROW 540
#define WHITE_PIECE_ROW 630
#define BLACK_PAWN_ROW 90
#define BLACK_PIECE_ROW 0

#define POS 1 
#define NEG -1

#define WHITE 1
#define BLACK -1

vector<shared_ptr<Piece>> Piece::wPiecesArr;
vector<shared_ptr<Piece>> Piece::wPArr;
vector<shared_ptr<Piece>> Piece::bPiecesArr;
vector<shared_ptr<Piece>> Piece::bPArr;

Piece::Piece(SDL_Renderer *&renderer, string imagePath, bool color, bool pawn, int initX, int initY) {
  tRect = make_shared<TexturedRect>(renderer, imagePath);
  tRect->setProperties(initX * PIECE_SIDE, initY * PIECE_SIDE, PIECE_SIDE, PIECE_SIDE);
  isWhite = color;
  isPawn = pawn;
  squareX = initX;
  squareY = initY;
}

Piece::~Piece() {

}

void Piece::setSquareXY(int newSquareX, int newSquareY) {
  squareX = newSquareX;
  squareY = newSquareY;
}

void Piece::setHasMoved(bool value) {

}

void Piece::setIsAlive(bool value) {
  isAlive = value;
}

void Piece::setCastleK(bool value) {

}

void Piece::setCastleQ(bool value) {

}

void Piece::setEnPassant(bool value, int num) {

}

bool Piece::getHasMoved() {

}

bool Piece::getIsAlive() {
  return isAlive;
}

bool Piece::getIsWhite() {
  return isWhite;
}

bool Piece::getCastleK() {

}

bool Piece::getCastleQ() {

}

bool Piece::getEnPassant() {

}

shared_ptr<TexturedRect> Piece::getTRect() {
  return tRect;
}

int Piece::getSquareX() {
  return squareX;
}

int Piece::getSquareY() {
  return squareY;
}

vector<tuple<int, int>> Piece::getValidSquares(int state[8][8]) {

}

void Piece::renderPieces(SDL_Renderer *&renderer, shared_ptr<Piece> movePiece) {
  // Rendering white pieces
  for (int i = 0; i < wPiecesArr.size(); i++) {
    if (wPiecesArr[i]->getIsAlive() &&
        wPiecesArr[i] != movePiece) {
      wPiecesArr[i]->getTRect()->render(renderer);
    }
  }
  
  for (int i = 0; i < wPArr.size(); i++) {
    if (wPArr[i]->getIsAlive() &&
        wPArr[i] != movePiece) {
      wPArr[i]->getTRect()->render(renderer);
    }
  }

  // Rendering black pieces
  for (int i = 0; i < bPiecesArr.size(); i++) {
    if (bPiecesArr[i]->getIsAlive() &&
        bPiecesArr[i] != movePiece) {
      bPiecesArr[i]->getTRect()->render(renderer);
    }
  }

  for (int i = 0; i < bPArr.size(); i++) {
    if (bPArr[i]->getIsAlive() &&
        bPArr[i] != movePiece) {
      bPArr[i]->getTRect()->render(renderer);
    }
  }

  if (movePiece != NULL) {
    movePiece->getTRect()->render(renderer);
  }

}


bool Piece::makeMove(int state[CHESS_SIDE][CHESS_SIDE], int mouseX, int mouseY, int *fiftyMoveCheck, map<string, int> pastStates) {

}

void Piece::squareSwap(int state[CHESS_SIDE][CHESS_SIDE], int srcX, int srcY, int dstX, int dstY) {
  int temp = state[srcY][srcX];
  state[srcY][srcX] = state[dstY][dstX];
  state[dstY][dstX] = temp; 
}

void Piece::capturePiece(vector<shared_ptr<Piece>> arr, int captureX, int captureY) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i]->getIsAlive() && captureX == arr[i]->getSquareX() &&
        captureY == arr[i]->getSquareY()) {
      arr[i]->setIsAlive(false);
    }
  }
}

void Piece::changeState(int state[CHESS_SIDE][CHESS_SIDE], int squareX, int squareY, int currX, int currY, bool isWhite, int *fiftyMoveCheck, map<string, int> pastStates) {

  // Turning off en passant for enemy pawns if needed
  if (isWhite) {
    for (int i = 0; i < wPArr.size(); i++) {
      if (wPArr[i]->getEnPassant()) {
        wPArr[i]->setEnPassant(false, 0);
      }
    }
  }
  else {
    for (int i = 0; i < bPArr.size(); i++) {
      if (bPArr[i]->getEnPassant()) {
        bPArr[i]->setEnPassant(false, 0);
      }
    }
  }

  // Moved to an empty square
  if (state[currY][currX] == 0) {
    squareSwap(state, squareX, squareY, currX, currY);
    *fiftyMoveCheck += 1;
  }
  // Captured an enemy piece (doesn't include en passant)
  else {
    if (isWhite) {
      if (abs(state[currY][currX]) == PAWN) {
        capturePiece(bPArr, currX, currY);
      }
      else {
        capturePiece(bPiecesArr, currX, currY);
      }
    }
    else {
      if (abs(state[currY][currX]) == PAWN) {
        capturePiece(wPArr, currX, currY);
      }
      else {
        capturePiece(wPiecesArr, currX, currY);
      }
    }
    state[currY][currX] = state[squareY][squareX];
    state[squareY][squareX] = EMPTY;
    *fiftyMoveCheck = 0;
    pastStates.clear();
  }
}

bool Piece::squareIsDefended(int state[CHESS_SIDE][CHESS_SIDE], int currX, int currY, int squareX, int squareY) {
  int thisPiece = state[squareY][squareX];

  // Checking pawns
  int dir;
  if (thisPiece > EMPTY) {dir = NEG;}
  else {dir = POS;}
  if (currY + dir <= CHESS_SIDE - 1 && 0 <= currX - 1 &&
      state[currY + dir][currX - 1]*thisPiece < EMPTY &&
      abs(state[currY + dir][currX - 1]) == PAWN) {
    return true;
  }
  if (currY + dir <= CHESS_SIDE - 1 && 
      currX + 1 <= CHESS_SIDE - 1 &&
      state[currY + dir][currX + 1]*thisPiece < EMPTY &&
      abs(state[currY + dir][currX + 1]) == PAWN) {
    return true;
  }

  // Checking knights
  if (currY + 1 <= CHESS_SIDE - 1 &&
      currX + 2 <= CHESS_SIDE - 1 &&
      state[currY + 1][currX + 2]*thisPiece < EMPTY &&
      abs(state[currY + 1][currX + 2]) == KNIGHT) {
    return true;
  }
  if (currY + 1 <= CHESS_SIDE - 1 && currX - 2 >= 0 &&
      state[currY + 1][currX - 2]*thisPiece < EMPTY &&
      abs(state[currY + 1][currX - 2]) == KNIGHT) {
    return true;
  }
  if (currY - 1 >= 0 && currX + 2 <= CHESS_SIDE - 1 &&
      state[currY - 1][currX + 2]*thisPiece < EMPTY &&
      abs(state[currY - 1][currX + 2]) == KNIGHT) {
    return true;
  }
  if (currY - 1 >= 0 && currX - 2 <= 0 &&
      state[currY - 1][currX + 2]*thisPiece < EMPTY &&
      abs(state[currY - 1][currX + 2]) == KNIGHT) {
    return true;
  }
  if (currY + 2 <= CHESS_SIDE - 1 &&
      currX + 1 <= CHESS_SIDE - 1 &&
      state[currY + 2][currX + 1]*thisPiece < EMPTY &&
      abs(state[currY + 2][currX + 1]) == KNIGHT) {
    return true;
  }
  if (currY + 2 <= CHESS_SIDE - 1 && currX - 1 >= 0 &&
      state[currY + 2][currX - 1]*thisPiece < EMPTY &&
      abs(state[currY + 2][currX - 1]) == KNIGHT) {
    return true;
  }
  if (currY - 2 >= 0 && currX + 1 <= CHESS_SIDE - 1 &&
      state[currY - 2][currX + 1]*thisPiece < EMPTY &&
      abs(state[currY - 2][currX + 1]) == KNIGHT) {
    return true;
  }
  if (currY - 2 >= 0 && currX - 1 >= 0 &&
      state[currY - 2][currX - 1]*thisPiece < EMPTY &&
      abs(state[currY - 2][currX - 1]) == KNIGHT) {
    return true;
  }

  // ChecKing (hilarious)
  if (currY + 1 <= CHESS_SIDE - 1 &&
      currX + 1 <= CHESS_SIDE - 1 &&
      state[currY + 1][currX + 1]*thisPiece < EMPTY &&
      abs(state[currY + 1][currX + 1]) == KING) {
    return true;
  }
  if (currY + 1 <= CHESS_SIDE - 1 &&
      state[currY + 1][currX]*thisPiece < EMPTY &&
      abs(state[currY + 1][currX]) == KING) {
    return true;
  }
  if (currX + 1 <= CHESS_SIDE - 1 &&
      state[currY][currX + 1]*thisPiece < EMPTY &&
      abs(state[currY][currX + 1]) == KING) {
    return true;
  }
  if (currY - 1 >= 0 && currX + 1 <= CHESS_SIDE - 1 &&
      state[currY - 1][currX + 1]*thisPiece < EMPTY &&
      abs(state[currY - 1][currX + 1]) == KING) {
    return true;
  }
  if (currY + 1 <= CHESS_SIDE - 1 && currX - 1 >= 0 &&
      state[currY + 1][currX - 1]*thisPiece < EMPTY &&
      abs(state[currY + 1][currX - 1]) == KING) {
    return true;
  }
  if (currY - 1 >= 0 && currX - 1 >= 0 &&
      state[currY - 1][currX - 1]*thisPiece < EMPTY &&
      abs(state[currY - 1][currX - 1]) == KING) {
    return true;
  }
  if (currY - 1 >= 0 &&
      state[currY - 1][currX]*thisPiece < EMPTY &&
      abs(state[currY - 1][currX]) == KING) {
    return true;
  }
  if (currX - 1 >= 0 &&
      state[currY][currX - 1]*thisPiece < EMPTY &&
      abs(state[currY][currX - 1]) == KING) {
    return true;
  }

  // Checking the straight lines
  for (int i = 1; currX + i <= CHESS_SIDE - 1; i++) {
    if (state[currY][currX + i]*thisPiece > EMPTY &&
        abs(state[currY][currX + i]) != KING) {
      break;
    }
    else if (state[currY][currX + i]*thisPiece < EMPTY) {
      if (abs(state[currY][currX + i]) == ROOK ||
          abs(state[currY][currX + i]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }

  for (int i = 1; currX - i >= 0; i++) {
    if (state[currY][currX - i]*thisPiece > EMPTY &&
        abs(state[currY][currX - i]) != KING) {
      break;
    }
    else if (state[currY][currX - i]*thisPiece < EMPTY) {
      if (abs(state[currY][currX - i]) == ROOK ||
          abs(state[currY][currX - i]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }

  for (int i = 1; currY + i <= CHESS_SIDE - 1; i++) {
    if (state[currY + i][currX]*thisPiece > EMPTY &&
        abs(state[currY + i][currX]) != KING) {
      break;
    }
    else if (state[currY + i][currX]*thisPiece < EMPTY) {
      if (abs(state[currY + i][currX]) == ROOK ||
          abs(state[currY + i][currX]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }
  
  for (int i = 1; currY - i >= 0; i++) {
    if (state[currY - i][currX]*thisPiece > EMPTY &&
        abs(state[currY - i][currX]) != KING) {
      break;
    }
    else if (state[currY - i][currX]*thisPiece < EMPTY) {
      if (abs(state[currY - i][currX]) == ROOK ||
          abs(state[currY - i][currX]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }

  // Checking the diagonals
  for (int i = 1; currX + i <= CHESS_SIDE - 1 && currY + i <= CHESS_SIDE - 1; i++) {
    if (state[currY + i][currX + i]*thisPiece > EMPTY &&
        abs(state[currY + i][currX + i]) != KING) {
      break;
    }
    else if (state[currY + i][currX + i]*thisPiece < EMPTY) {
      if (abs(state[currY + i][currX + i]) == BISHOP ||
          abs(state[currY + i][currX + i]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }

  for (int i = 1; currX - i >= 0 && currY + i <= CHESS_SIDE - 1; i++) {
    if (state[currY + i][currX - i]*thisPiece > EMPTY &&
        abs(state[currY + i][currX - i]) != KING) {
      break;
    }
    else if (state[currY + i][currX - i]*thisPiece < EMPTY) {
      if (abs(state[currY + i][currX - i]) == BISHOP ||
          abs(state[currY + i][currX - i]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }

  for (int i = 1; currX + i <= CHESS_SIDE - 1 && currY - i >= 0; i++) {
    if (state[currY - i][currX + i]*thisPiece > EMPTY &&
        abs(state[currY - i][currX + i]) != KING) {
      break;
    }
    else if (state[currY - i][currX + i]*thisPiece < EMPTY) {
      if (abs(state[currY - i][currX + i]) == BISHOP ||
          abs(state[currY - i][currX + i]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }

  for (int i = 1; currX - i >= 0 && currY - i >= 0; i++) {
    if (state[currY - i][currX - i]*thisPiece > EMPTY &&
        abs(state[currY - i][currX - i]) != KING) {
      break;
    }
    else if (state[currY - i][currX - i]*thisPiece < EMPTY) {
      if (abs(state[currY - i][currX - i]) == BISHOP ||
          abs(state[currY - i][currX - i]) == QUEEN) {
        return true;
      }
      else {
        break;
      }
    }
  }

  return false;

}

bool Piece::kingInCheck(int state[CHESS_SIDE][CHESS_SIDE], int currX, int currY, int squareX, int squareY, bool enPassant) {
  int tempState[CHESS_SIDE][CHESS_SIDE];
  for (int i = 0; i < CHESS_SIDE; i++) {
    for (int j = 0; j < CHESS_SIDE; j++) {
      tempState[i][j] = state[i][j];
    }
  }
  int dir;
  if (tempState[squareY][squareX] > 0) {dir = NEG;}
  else {dir = POS;}
  if (tempState[currY][currX] == EMPTY) {
    squareSwap(tempState, squareX, squareY, currX, currY);
  }
  else {
    tempState[currY][currX] = tempState[squareY][squareX];
    tempState[squareY][squareX] = EMPTY;
  }

  if (enPassant) {
    tempState[currY - dir][currX] = EMPTY;
  }

  int kingX, kingY;
  if (tempState[currY][currX] > EMPTY) {
    for (int i = 0; i < CHESS_SIDE; i++) {
      for (int j = 0; j < CHESS_SIDE; j++) {
        if (tempState[i][j] == WHITE*KING) {
          kingX = j;
          kingY = i;
        }
      }
    }
  }
  else if (tempState[currY][currX] < EMPTY) {
    for (int i = 0; i < CHESS_SIDE; i++) {
      for (int j = 0; j < CHESS_SIDE; j++) {
        if (tempState[i][j] == BLACK*KING) {
          kingX = j;
          kingY = i;
        }
      }
    }
  }

  if (squareIsDefended(tempState, kingX, kingY, kingX, kingY)) {
    return true;
  }
  else {
    return false;
  }
}
// bool Piece::makeMove(int mouseX, int mouseY, int state[8][8]) {
//
// }
