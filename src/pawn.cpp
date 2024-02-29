#include <string>
#include <memory>
#include <SDL2/SDL.h>

#include "../include/pawn.hpp"

using namespace std;

Pawn::~Pawn() {

}

void Pawn::setSquareXY(int newSquareX, int newSquareY) {
  squareX = newSquareX;
  squareY = newSquareY;
  hasMoved = true;
}
