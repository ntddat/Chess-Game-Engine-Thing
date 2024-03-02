#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"
using namespace std;

class Piece {
  protected:
    shared_ptr<TexturedRect> tRect;
    bool isWhite;
    bool isPawn;
    bool isAlive = true;
    int squareX, squareY;

  public:
    Piece(SDL_Renderer *&renderer, string imagePath, bool color, bool pawn, int initX, int initY);

    ~Piece();

    void setSquareXY(int newSquareX, int newSquareY);

    virtual void setHasMoved(bool value);

    void setIsAlive(bool value);

    virtual void setCastleK(bool value);

    virtual void setCastleQ(bool value);

    virtual bool getHasMoved();

    bool getIsWhite();

    bool getIsAlive();

    virtual bool getCastleK();

    virtual bool getCastleQ();

    shared_ptr<TexturedRect> getTRect();

    int getSquareX();

    int getSquareY();

    virtual vector<tuple<int, int>> getValidSquares(int state[8][8]);

    // virtual bool makeMove(int mouseX, int mouseY, int state[8][8]);
};

#endif
