#ifndef QUEEN_H
#define QUEEN_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Queen: public Piece {
  public:
    using Piece::Piece;

    ~Queen();
};

#endif
