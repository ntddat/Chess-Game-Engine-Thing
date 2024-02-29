#ifndef PAWN_H
#define PAWN_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Pawn: public Piece {
  private:
    bool hasMoved = false;

  public:
    using Piece::Piece;
    
    ~Pawn();

    void setSquareXY(int newSquareX, int newSquareY);
};

#endif
