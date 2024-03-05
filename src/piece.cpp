#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"
#include "../include/piece.hpp"

using namespace std;

#define PIECE_SIDE 90
#define WHITE_PAWN_ROW 540
#define WHITE_PIECE_ROW 630
#define BLACK_PAWN_ROW 90
#define BLACK_PIECE_ROW 0

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
// bool Piece::makeMove(int mouseX, int mouseY, int state[8][8]) {
//
// }
