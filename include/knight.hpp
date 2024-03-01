#ifndef KNIGHT_H
#define KNIGHT_H

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Knight: public Piece {
  public:
    using Piece::Piece;

    ~Knight();

    vector<tuple<int, int>> getValidSquares(int state[8][8]);
};

#endif
