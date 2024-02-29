#ifndef BISHOP_H
#define BISHOP_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Bishop: public Piece {
  public:
    using Piece::Piece;

    ~Bishop();
};

#endif
