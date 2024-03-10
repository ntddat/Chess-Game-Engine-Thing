#ifndef ROOK_H
#define ROOK_H

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Rook: public Piece {
  private:
    bool hasMoved = false;

  public:
    using Piece::Piece;

    ~Rook();

    vector<tuple<int, int>> getValidSquares(int state[8][8]);

    bool makeMove(int state[8][8], int mouseX, int mouseY, int *fiftyMoveCheck);
};

#endif
