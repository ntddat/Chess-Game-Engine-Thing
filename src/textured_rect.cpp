#include <string>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"

using namespace std;

// Constructor
TexturedRect::TexturedRect(SDL_Renderer *&renderer, string imagePath) {
  SDL_Surface *surface = SDL_LoadBMP(imagePath.c_str());
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

// Destructor
TexturedRect::~TexturedRect() {
  SDL_DestroyTexture(texture);
}

void TexturedRect::setProperties(int x, int y, int width, int height) {
  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;
}

void TexturedRect::setCoordinates(int x, int y) {
  rect.x = x;
  rect.y = y;
}

int TexturedRect::getXValue() {
  return rect.x;
}

int TexturedRect::getYValue() {
  return rect.y;
}

void TexturedRect::render(SDL_Renderer *&renderer) {
  SDL_RenderCopy(renderer, texture, NULL, &rect);
}
