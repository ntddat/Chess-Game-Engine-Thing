#include <string>
#include <memory>
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

shared_ptr<TexturedRect> Piece::getTRect() {
  return tRect;
}
