#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"
#include "../include/piece.hpp"

using namespace std;

#define EMPTY 0;
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

/*
void Piece::initPieces(SDL_Renderer *&renderer) {

  // Array to store the pieces
  shared_ptr<Piece> wR1 = make_shared<Rook>(renderer, "../images/wr.bmp", true, false, 0, 7);
  wPiecesArr.push_back(wR1);
  shared_ptr<Piece> wN1 = make_shared<Knight>(renderer, "../images/wn.bmp", true, false, 1, 7);
  wPiecesArr.push_back(wN1);
  shared_ptr<Piece> wB1 = make_shared<Bishop>(renderer, "../images/wb.bmp", true, false, 2, 7);
  wPiecesArr.push_back(wB1);
  shared_ptr<Piece> wQ = make_shared<Queen>(renderer, "../images/wq.bmp", true, false, 3, 7);
  wPiecesArr.push_back(wQ);
  shared_ptr<Piece> wK = make_shared<King>(renderer, "../images/wk.bmp", true, false, 4, 7);
  wPiecesArr.push_back(wK);
  shared_ptr<Piece> wB2 = make_shared<Bishop>(renderer, "../images/wb.bmp", true, false, 5, 7);
  wPiecesArr.push_back(wB2);
  shared_ptr<Piece> wN2 = make_shared<Knight>(renderer, "../images/wn.bmp", true, false, 6, 7);
  wPiecesArr.push_back(wN2);
  shared_ptr<Piece> wR2 = make_shared<Rook>(renderer, "../images/wr.bmp", true, false, 7, 7);
  wPiecesArr.push_back(wR2);
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<Piece> wP = make_shared<Pawn>(renderer, "../images/wp.bmp", true, true, i, 6);
    wPArr.push_back(wP);
  }

  // Array to store the pieces
  shared_ptr<Piece> bR1 = make_shared<Rook>(renderer, "../images/br.bmp", false, false, 0, 0);
  bPiecesArr.push_back(bR1);
  shared_ptr<Piece> bN1 = make_shared<Knight>(renderer, "../images/bn.bmp", false, false, 1, 0);
  bPiecesArr.push_back(bN1);
  shared_ptr<Piece> bB1 = make_shared<Bishop>(renderer, "../images/bb.bmp", false, false, 2, 0);
  bPiecesArr.push_back(bB1);
  shared_ptr<Piece> bQ = make_shared<Queen>(renderer, "../images/bq.bmp", false, false, 3, 0);
  bPiecesArr.push_back(bQ);
  shared_ptr<Piece> bK = make_shared<King>(renderer, "../images/bk.bmp", false, false, 4, 0);
  bPiecesArr.push_back(bK);
  shared_ptr<Piece> bB2 = make_shared<Bishop>(renderer, "../images/bb.bmp", false, false, 5, 0);
  bPiecesArr.push_back(bB2);
  shared_ptr<Piece> bN2 = make_shared<Knight>(renderer, "../images/bn.bmp", false, false, 6, 0);
  bPiecesArr.push_back(bN2);
  shared_ptr<Piece> bR2 = make_shared<Rook>(renderer, "../images/br.bmp", false, false, 7, 0);
  bPiecesArr.push_back(bR2);
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<Piece> bP = make_shared<Pawn>(renderer, "../images/bp.bmp", false, true, i, 1);
    bPArr.push_back(bP);
  }
}
*/


void Piece::renderPieces(SDL_Renderer *&renderer, shared_ptr<Piece> movePiece) {
    // Rendering white pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (wPiecesArr[i]->getIsAlive() &&
          wPiecesArr[i] != movePiece) {
        wPiecesArr[i]->getTRect()->render(renderer);
      }
      if (wPArr[i]->getIsAlive() &&
          wPArr[i] != movePiece) {
        wPArr[i]->getTRect()->render(renderer);
      }
    }

    // Rendering black pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (bPiecesArr[i]->getIsAlive() &&
          bPiecesArr[i] != movePiece) {
        bPiecesArr[i]->getTRect()->render(renderer);
      }
      if (bPArr[i]->getIsAlive() &&
          bPArr[i] != movePiece) {
        bPArr[i]->getTRect()->render(renderer);
      }
    }

    if (movePiece != NULL) {
      movePiece->getTRect()->render(renderer);
    }

}


bool Piece::makeMove(int state[CHESS_SIDE][CHESS_SIDE], int mouseX, int mouseY) {

}

void Piece::squareSwap(int state[CHESS_SIDE][CHESS_SIDE], int srcX, int srcY, int dstX, int dstY) {
  int temp = state[srcY][srcX];
  state[srcY][srcX] = state[dstY][dstX];
  state[dstY][dstX] = temp; 
}

void Piece::capturePiece(vector<shared_ptr<Piece>> arr, int captureX, int captureY) {
  for (int i = 0; i < CHESS_SIDE; i++) {
    if (arr[i]->getIsAlive() && captureX == arr[i]->getSquareX() &&
        captureY == arr[i]->getSquareY()) {
      arr[i]->setIsAlive(false);
    }
  }
}

void Piece::changeState(int state[CHESS_SIDE][CHESS_SIDE], int squareX, int squareY, int currX, int currY, bool isWhite) {

    // Moved to an empty square
    if (state[currY][currX] == 0) {
      squareSwap(state, squareX, squareY, currX, currY);
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
    }
}
// bool Piece::makeMove(int mouseX, int mouseY, int state[8][8]) {
//
// }
