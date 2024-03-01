#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/king.hpp"

using namespace std;

#define CHESS_SIDE 8
#define EMPTY 0
#define KING 6

King::~King() {

}

vector<tuple<int, int>> King::getValidSquares(int state[CHESS_SIDE][CHESS_SIDE]) {
  vector<tuple<int, int>> validSquares;
  int thisPiece = state[squareY][squareX];

  // Implement movement but must not allow capture of protected piece 
  // Also implementing castling (fuck)
  return validSquares;
}
