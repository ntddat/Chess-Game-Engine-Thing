#include <string>
#include <memory>
#include <SDL2/SDL.h>

// #include "../include/textured_rect.hpp"

class Piece {
  protected:
    shared_ptr<TexturedRect> tRect;
    bool isWhite;
    bool isPawn;

  public:
    Piece(SDL_Renderer *&renderer, string imagePath, bool color, bool pawn, int initX);

    virtual ~Piece();

    shared_ptr<TexturedRect> getTRect();
};
