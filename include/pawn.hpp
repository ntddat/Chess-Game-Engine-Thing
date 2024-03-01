#ifndef PAWN_H
#define PAWN_H

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "piece.hpp"

using namespace std;

class Pawn: public Piece {
  private:
    bool hasMoved = false;

  public:
    using Piece::Piece;
    
    ~Pawn();
  
    void setHasMoved(bool value);

    bool getHasMoved();

    vector<tuple<int, int>> getValidSquares(int state[8][8]);

    // bool makeMove(int mouseX, int mouseY, int state[8][8]);
};

#endif
