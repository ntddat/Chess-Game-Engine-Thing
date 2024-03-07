#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>

#include "../include/king.hpp"

using namespace std;

#define SQUARE_SIDE 90
#define CHESS_SIDE 8
#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6

#define POS 1
#define NEG -1

#define WHITE 1
#define BLACK -1

King::~King() {

}

void King::setCastleK(bool value) {
  canCastleK = value;
}

void King::setCastleQ(bool value) {
  canCastleQ = value;
}

bool King::getCastleK() {
  return canCastleK;
}

bool King::getCastleQ() {
  return canCastleQ;
}

vector<tuple<int, int>> King::getValidSquares(int state[CHESS_SIDE][CHESS_SIDE]) {
  vector<tuple<int, int>> validSquares;
  int thisPiece = state[squareY][squareX];

  if (squareY + 1 <= CHESS_SIDE - 1 && 
      squareX + 1 <= CHESS_SIDE - 1 &&
      state[squareY + 1][squareX + 1]*thisPiece <= EMPTY &&
      abs(state[squareY + 1][squareX + 1]) != KING &&
      !squareIsDefended(state, squareX + 1, squareY + 1, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX + 1, squareY + 1));
  }
  if (squareY + 1 <= CHESS_SIDE - 1 && 
      state[squareY + 1][squareX]*thisPiece <= EMPTY &&
      abs(state[squareY + 1][squareX]) != KING &&
      !squareIsDefended(state, squareX, squareY + 1, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX, squareY + 1));
  }
  if (squareX + 1 <= CHESS_SIDE - 1 &&
      state[squareY][squareX + 1]*thisPiece <= EMPTY &&
      abs(state[squareY][squareX + 1]) != KING &&
      !squareIsDefended(state, squareX + 1, squareY, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX + 1, squareY));
  }
  if (squareY + 1 <= CHESS_SIDE - 1 && squareX - 1 >= 0 &&
      state[squareY + 1][squareX - 1]*thisPiece <= EMPTY &&
      abs(state[squareY + 1][squareX - 1]) != KING &&
      !squareIsDefended(state, squareX - 1, squareY + 1, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX - 1, squareY + 1));
  }
  if (squareY - 1 >= 0 && squareX + 1 <= CHESS_SIDE - 1 &&
      state[squareY - 1][squareX + 1]*thisPiece <= EMPTY &&
      abs(state[squareY - 1][squareX + 1]) != KING &&
      !squareIsDefended(state, squareX + 1, squareY - 1, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX + 1, squareY - 1));
  }
  if (squareY - 1 >= 0 && squareX - 1 >= 0 &&
      state[squareY - 1][squareX - 1]*thisPiece <= EMPTY &&
      abs(state[squareY - 1][squareX - 1]) != KING &&
      !squareIsDefended(state, squareX - 1, squareY - 1, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX - 1, squareY - 1));
  }
  if (squareY - 1 >= 0 &&
      state[squareY - 1][squareX]*thisPiece <= EMPTY &&
      abs(state[squareY - 1][squareX]) != KING &&
      !squareIsDefended(state, squareX, squareY - 1, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX, squareY - 1));
  }
  if (squareX - 1 >= 0 &&
      state[squareY][squareX - 1]*thisPiece <= EMPTY &&
      abs(state[squareY][squareX - 1]) != KING &&
      !squareIsDefended(state, squareX - 1, squareY, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX - 1, squareY));
  }

  // Castle short
  if (canCastleK && state[squareY][squareX + 1] == EMPTY &&
      state[squareY][squareX + 2] == EMPTY &&
      !squareIsDefended(state, squareX, squareY, squareX, squareY) &&
      !squareIsDefended(state, squareX + 1, squareY, squareX, squareY) &&
      !squareIsDefended(state, squareX + 2, squareY, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX + 2, squareY));
  }
  // Castle long
  if (canCastleQ && state[squareY][squareX - 1] == EMPTY &&
      state[squareY][squareX - 2] == EMPTY &&
      state[squareY][squareX - 3] == EMPTY &&
      !squareIsDefended(state, squareX, squareY, squareX, squareY) &&
      !squareIsDefended(state, squareX - 1, squareY, squareX, squareY) &&
      !squareIsDefended(state, squareX - 2, squareY, squareX, squareY) &&
      !squareIsDefended(state, squareX - 3, squareY, squareX, squareY)) {
    validSquares.push_back(make_tuple(squareX - 2, squareY));
  }

  return validSquares;
}

// bool King::squareIsDefended(int state[CHESS_SIDE][CHESS_SIDE], int currX, int currY, int squareX, int squareY) {
//   int thisPiece = state[squareY][squareX];
//
//   // Checking pawns
//   int dir;
//   if (isWhite) {dir = NEG;}
//   else {dir = POS;}
//   if (currY + dir <= CHESS_SIDE - 1 && 0 <= currX - 1 &&
//       state[currY + dir][currX - 1]*thisPiece < EMPTY &&
//       abs(state[currY + dir][currX - 1]) == PAWN) {
//     return true;
//   }
//   if (currY + dir <= CHESS_SIDE - 1 && 
//       currX + 1 <= CHESS_SIDE - 1 &&
//       state[currY + dir][currX + 1]*thisPiece < EMPTY &&
//       abs(state[currY + dir][currX + 1]) == PAWN) {
//     return true;
//   }
//
//   // Checking knights
//   if (currY + 1 <= CHESS_SIDE - 1 &&
//       currX + 2 <= CHESS_SIDE - 1 &&
//       state[currY + 1][currX + 2]*thisPiece < EMPTY &&
//       abs(state[currY + 1][currX + 2]) == KNIGHT) {
//     return true;
//   }
//   if (currY + 1 <= CHESS_SIDE - 1 && currX - 2 >= 0 &&
//       state[currY + 1][currX - 2]*thisPiece < EMPTY &&
//       abs(state[currY + 1][currX - 2]) == KNIGHT) {
//     return true;
//   }
//   if (currY - 1 >= 0 && currX + 2 <= CHESS_SIDE - 1 &&
//       state[currY - 1][currX + 2]*thisPiece < EMPTY &&
//       abs(state[currY - 1][currX + 2]) == KNIGHT) {
//     return true;
//   }
//   if (currY - 1 >= 0 && currX - 2 <= 0 &&
//       state[currY - 1][currX + 2]*thisPiece < EMPTY &&
//       abs(state[currY - 1][currX + 2]) == KNIGHT) {
//     return true;
//   }
//   if (currY + 2 <= CHESS_SIDE - 1 &&
//       currX + 1 <= CHESS_SIDE - 1 &&
//       state[currY + 2][currX + 1]*thisPiece < EMPTY &&
//       abs(state[currY + 2][currX + 1]) == KNIGHT) {
//     return true;
//   }
//   if (currY + 2 <= CHESS_SIDE - 1 && currX - 1 >= 0 &&
//       state[currY + 2][currX - 1]*thisPiece < EMPTY &&
//       abs(state[currY + 2][currX - 1]) == KNIGHT) {
//     return true;
//   }
//   if (currY - 2 >= 0 && currX + 1 <= CHESS_SIDE - 1 &&
//       state[currY - 2][currX + 1]*thisPiece < EMPTY &&
//       abs(state[currY - 2][currX + 1]) == KNIGHT) {
//     return true;
//   }
//   if (currY - 2 >= 0 && currX - 1 >= 0 &&
//       state[currY - 2][currX - 1]*thisPiece < EMPTY &&
//       abs(state[currY - 2][currX - 1]) == KNIGHT) {
//     return true;
//   }
//
//   // ChecKing (hilarious)
//   if (currY + 1 <= CHESS_SIDE - 1 &&
//       currX + 1 <= CHESS_SIDE - 1 &&
//       state[currY + 1][currX + 1]*thisPiece < EMPTY &&
//       abs(state[currY + 1][currX + 1]) == KING) {
//     return true;
//   }
//   if (currY + 1 <= CHESS_SIDE - 1 &&
//       state[currY + 1][currX]*thisPiece < EMPTY &&
//       abs(state[currY + 1][currX]) == KING) {
//     return true;
//   }
//   if (currX + 1 <= CHESS_SIDE - 1 &&
//       state[currY][currX + 1]*thisPiece < EMPTY &&
//       abs(state[currY][currX + 1]) == KING) {
//     return true;
//   }
//   if (currY - 1 >= 0 && currX + 1 <= CHESS_SIDE - 1 &&
//       state[currY - 1][currX + 1]*thisPiece < EMPTY &&
//       abs(state[currY - 1][currX + 1]) == KING) {
//     return true;
//   }
//   if (currY + 1 <= CHESS_SIDE - 1 && currX - 1 >= 0 &&
//       state[currY + 1][currX - 1]*thisPiece < EMPTY &&
//       abs(state[currY + 1][currX - 1]) == KING) {
//     return true;
//   }
//   if (currY - 1 >= 0 && currX - 1 >= 0 &&
//       state[currY - 1][currX - 1]*thisPiece < EMPTY &&
//       abs(state[currY - 1][currX - 1]) == KING) {
//     return true;
//   }
//   if (currY - 1 >= 0 &&
//       state[currY - 1][currX]*thisPiece < EMPTY &&
//       abs(state[currY - 1][currX]) == KING) {
//     return true;
//   }
//   if (currX - 1 >= 0 &&
//       state[currY][currX - 1]*thisPiece < EMPTY &&
//       abs(state[currY][currX - 1]) == KING) {
//     return true;
//   }
//
//   // Checking the straight lines
//   for (int i = 1; currX + i <= CHESS_SIDE - 1; i++) {
//     if (state[currY][currX + i]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY][currX + i]*thisPiece < EMPTY) {
//       if (abs(state[currY][currX + i]) == ROOK ||
//           abs(state[currY][currX + i]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//
//   for (int i = 1; currX - i >= 0; i++) {
//     if (state[currY][currX - i]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY][currX - i]*thisPiece < EMPTY) {
//       if (abs(state[currY][currX - i]) == ROOK ||
//           abs(state[currY][currX - i]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//
//   for (int i = 1; currY + i <= CHESS_SIDE - 1; i++) {
//     if (state[currY + i][currX]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY + i][currX]*thisPiece < EMPTY) {
//       if (abs(state[currY + i][currX]) == ROOK ||
//           abs(state[currY + i][currX]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//   
//   for (int i = 1; currY - i >= 0; i++) {
//     if (state[currY - i][currX]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY - i][currX]*thisPiece < EMPTY) {
//       if (abs(state[currY - i][currX]) == ROOK ||
//           abs(state[currY - i][currX]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//
//   // Checking the diagonals
//   for (int i = 1; currX + i <= CHESS_SIDE - 1 && currY + i <= CHESS_SIDE - 1; i++) {
//     if (state[currY + i][currX + i]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY + i][currX + i]*thisPiece < EMPTY) {
//       if (abs(state[currY + i][currX + i]) == BISHOP ||
//           abs(state[currY + i][currX + i]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//
//   for (int i = 1; currX - i >= 0 && currY + i <= CHESS_SIDE - 1; i++) {
//     if (state[currY + i][currX - i]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY + i][currX - i]*thisPiece < EMPTY) {
//       if (abs(state[currY + i][currX - i]) == BISHOP ||
//           abs(state[currY + i][currX - i]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//
//   for (int i = 1; currX + i <= CHESS_SIDE - 1 && currY - i >= 0; i++) {
//     if (state[currY - i][currX + i]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY - i][currX + i]*thisPiece < EMPTY) {
//       if (abs(state[currY - i][currX + i]) == BISHOP ||
//           abs(state[currY - i][currX + i]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//
//   for (int i = 1; currX - i >= 0 && currY - i >= 0; i++) {
//     if (state[currY - i][currX - i]*thisPiece > EMPTY) {
//       break;
//     }
//     else if (state[currY - i][currX - i]*thisPiece < EMPTY) {
//       if (abs(state[currY - i][currX - i]) == BISHOP ||
//           abs(state[currY - i][currX - i]) == QUEEN) {
//         return true;
//       }
//       else {
//         break;
//       }
//     }
//   }
//
//   return false;
//
// }

bool King::makeMove(int state[CHESS_SIDE][CHESS_SIDE], int mouseX, int mouseY) {
  vector<tuple<int, int>> validSquares = this->getValidSquares(state);
  for (int i = 0; i < validSquares.size(); i++) {
    int currX = get<0>(validSquares[i]);
    int currY = get<1>(validSquares[i]);
    if (currX*SQUARE_SIDE <= mouseX && mouseX <= currX*SQUARE_SIDE + SQUARE_SIDE &&
        currY*SQUARE_SIDE <= mouseY && mouseY <= currY*SQUARE_SIDE + SQUARE_SIDE) {
      if (canCastleK) {canCastleK = false;}
      if (canCastleQ) {canCastleQ = false;}

      // Moving the rooks if it is a castling move
      shared_ptr<Piece> currRook = NULL;
      int color = EMPTY;
      // Castle long
      if (squareX - currX == 2) {
        if (isWhite) {
          for (int i = 0; i < wPiecesArr.size(); i++) {
            if (wPiecesArr[i]->getSquareX() == 0 &&
                wPiecesArr[i]->getSquareY() == currY) {
              currRook = wPiecesArr[i];
              break;
            }
          }
          color = WHITE;
        }
        else {
          for (int i = 0; i < bPiecesArr.size(); i++) {
            if (bPiecesArr[i]->getSquareX() == 0 &&
                bPiecesArr[i]->getSquareY() == currY) {
              currRook = bPiecesArr[i];
              break;
            }
          }
          color = BLACK;
        }
        state[currRook->getSquareY()][currRook->getSquareX()] = EMPTY;
        state[currRook->getSquareY()][currRook->getSquareX() + 3] = color*ROOK;
        currRook->setSquareXY(currRook->getSquareX() + 3, currRook->getSquareY());
        currRook->getTRect()->setCoordinates(currRook->getSquareX()*SQUARE_SIDE,
                                             currRook->getSquareY()*SQUARE_SIDE);
        canCastleQ = false;
      }
      else if (currX - squareX == 2) {
        if (isWhite) {
          for (int i = 0; i < wPiecesArr.size(); i++) {
            if (wPiecesArr[i]->getSquareX() == 7 &&
                wPiecesArr[i]->getSquareY() == currY) {
              currRook = wPiecesArr[i];
              break;
            }
          }
          color = WHITE;
        }
        else {
          for (int i = 0; i < bPiecesArr.size(); i++) {
            if (bPiecesArr[i]->getSquareX() == 7 &&
                bPiecesArr[i]->getSquareY() == currY) {
              currRook = bPiecesArr[i];
              break;
            }
          }
          color = BLACK;
        }
        state[currRook->getSquareY()][currRook->getSquareX()] = EMPTY;
        state[currRook->getSquareY()][currRook->getSquareX() - 2] = color*ROOK;
        currRook->setSquareXY(currRook->getSquareX() - 2, currRook->getSquareY());
        currRook->getTRect()->setCoordinates(currRook->getSquareX()*SQUARE_SIDE,
                                             currRook->getSquareY()*SQUARE_SIDE);
        canCastleK = false;
      }

      changeState(state, squareX, squareY, currX, currY, isWhite);

      squareX = currX;
      squareY = currY;
      return true;
    }
  }
  return false;
}
