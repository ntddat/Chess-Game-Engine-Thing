#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"
using namespace std;

class Piece {
  protected:
    shared_ptr<TexturedRect> tRect;
    bool isWhite;
    bool isPawn;
    int squareX, squareY;

  public:
    Piece(SDL_Renderer *&renderer, string imagePath, bool color, bool pawn, int initX, int initY);

    ~Piece();

    void setSquareXY(int newSquareX, int newSquareY);

    shared_ptr<TexturedRect> getTRect();
};

#endif
