#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/text_rect.hpp"

using namespace std;

TextRect::TextRect(SDL_Renderer *&renderer, TTF_Font *font, string text, int x, int y) {
  SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;
}

TextRect::~TextRect() {
  SDL_DestroyTexture(texture);
}

void TextRect::render(SDL_Renderer *&renderer) {
  SDL_RenderCopy(renderer, texture, NULL, &rect);
}
