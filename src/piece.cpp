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

Piece::Piece(SDL_Renderer *&renderer, string imagePath, bool color, bool pawn,  int initX) {
  tRect = make_shared<TexturedRect>(renderer, imagePath);
  int initY;
  if (color) {
    if (pawn) initY = WHITE_PAWN_ROW;
    else initY = WHITE_PIECE_ROW;
  }
  else {
    if (pawn) initY = BLACK_PAWN_ROW;
    else initY = BLACK_PIECE_ROW;
  }
  tRect->setProperties(initX, initY, PIECE_SIDE, PIECE_SIDE);
  isWhite = color;
  isPawn = pawn;
}

Piece::~Piece() {

}

shared_ptr<TexturedRect> Piece::getTRect() {
  return tRect;
}
