#ifndef KING_H
#define KING_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class King: public Piece {
  private:
    bool hasMoved = false;

  public:
    using Piece::Piece;

    ~King();
};

#endif
