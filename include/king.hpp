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
    bool canCastleK = true;
    bool canCastleQ = true;

  public:
    using Piece::Piece;

    ~King();

    void setCastleK(bool value);

    void setCastleQ(bool value);

    bool getCastleK();

    bool getCastleQ();

    vector<tuple<int, int>> getValidSquares(int state[8][8]);

    // bool squareIsDefended(int state[8][8], int currX, int currY, int squareX, int squareY);

    bool makeMove(int state[8][8], int mouseX, int mouseY);
};

#endif
