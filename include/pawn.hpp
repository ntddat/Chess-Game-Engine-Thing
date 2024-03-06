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
    bool enPassantAble = false;
    int enPassantNum = 0;

  public:
    using Piece::Piece;
    
    ~Pawn();
  
    void setHasMoved(bool value);

    void setEnPassant(bool value, int num);

    bool getHasMoved();

    bool getEnPassant();

    vector<tuple<int, int>> getValidSquares(int state[8][8]);

    bool makeMove(int state[8][8], int mouseX, int mouseY);

    static void activateEnPassant(vector<shared_ptr<Piece>> arr, int currX, int currY, int value);
};

#endif
