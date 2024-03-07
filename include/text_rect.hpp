#ifndef TEXT_RECT_H
#define TEXT_RECT_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class TextRect {
  private:
    SDL_Rect rect;
    SDL_Texture *texture;

  public:
    TextRect(SDL_Renderer *&renderer, TTF_Font *font, string text, int x, int y);

    ~TextRect();

    void render(SDL_Renderer *&renderer);
};

#endif
