#ifndef KNIGHT_H
#define KNIGHT_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Knight: public Piece {
  public:
    using Piece::Piece;

    ~Knight();
};

#endif
