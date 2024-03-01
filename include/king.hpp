#ifndef KING_H
#define KING_H

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class King: public Piece {
  private:
    bool hasMoved = false;

  public:
    using Piece::Piece;

    ~King();

    vector<tuple<int, int>> getValidSquares(int state[8][8]);
};

#endif
