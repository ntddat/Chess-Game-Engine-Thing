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
    static vector<shared_ptr<Piece>> wPiecesArr;
    static vector<shared_ptr<Piece>> wPArr;
    static vector<shared_ptr<Piece>> bPiecesArr;
    static vector<shared_ptr<Piece>> bPArr;
    
    Piece(SDL_Renderer *&renderer, string imagePath, bool color, bool pawn, int initX, int initY);

    ~Piece();

    void setSquareXY(int newSquareX, int newSquareY);

    virtual void setHasMoved(bool value);

    void setIsAlive(bool value);

    virtual void setCastleK(bool value);

    virtual void setCastleQ(bool value);

    virtual void setEnPassant(bool value, int num);

    virtual bool getHasMoved();

    bool getIsWhite();

    bool getIsAlive();

    virtual bool getCastleK();

    virtual bool getCastleQ();

    virtual bool getEnPassant();

    shared_ptr<TexturedRect> getTRect();

    int getSquareX();

    int getSquareY();

    virtual vector<tuple<int, int>> getValidSquares(int state[8][8]);

    // static void initPieces(SDL_Renderer *&renderer);

    static void renderPieces(SDL_Renderer *&renderer, shared_ptr<Piece> movePiece);

    virtual bool makeMove(int state[8][8], int mouseX, int mouseY, int *fiftyMoveCheck);

    static void squareSwap(int state[8][8], int srcX, int srcY, int dstX, int dstY);

    static void capturePiece(vector<shared_ptr<Piece>> arr, int capturedX, int captureY);

    static void changeState(int state[8][8], int squareX, int squareY, int currX, int currY, bool isWhite, int *fiftyMoveCheck);
   
    static bool squareIsDefended(int state[8][8], int currX, int currY, int squareX, int squareY);

    static bool kingInCheck(int state[8][8], int currX, int currY, int squareX, int squareY, bool enPassant);
};

#endif
