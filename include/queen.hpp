#ifndef QUEEN_H
#define QUEEN_H

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Queen: public Piece {
  public:
    using Piece::Piece;

    ~Queen();

    vector<tuple<int, int>> getValidSquares(int state[8][8]);

    bool makeMove(int state[8][8], int mouseX, int mouseY, int *fiftyMoveCheck, map<string, int> pastStates);
};

#endif
