// Right now, compile program with: make
// g++ chess_game.cpp ./glad/src/glad.c -I./glad/include -o chess_game -lSDL2 

#include <iostream>
#include <vector>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

// #pragma once

#include "../include/textured_rect.hpp"
#include "../include/pawn.hpp"
#include "../include/knight.hpp"
#include "../include/bishop.hpp"
#include "../include/rook.hpp"
#include "../include/queen.hpp"
#include "../include/king.hpp"
#include "../include/piece.hpp"

using namespace std;

#define CHESS_SIDE 8
#define SQUARE_SIDE 90
#define PIECE_SIDE 90
#define EXTRA 0
#define WHITE_PAWN_ROW 540
#define WHITE_PIECE_ROW 630
#define BLACK_PAWN_ROW 90
#define BLACK_PIECE_ROW 0

#define EMPTY 0
#define PAWN 1
#define KNIGHT 2  
#define BISHOP 3
#define ROOK 4
#define QUEEN 5 
#define KING 6

#define BLACK -1
#define WHITE 1

/*
 empty = 0
 pawn = 1, knight = 2, bishop = 3, rook = 4, queen = 5, king = 6
 black pieces are negative
 int state[8][8] = {
 {-4, -2, -3, -5, -6, -3, -2, -4}
 {-1, -1, -1, -1, -1, -1, -1, -1}
 {0, 0, 0, 0, 0, 0, 0, 0}
 {0, 0, 0, 0, 0, 0, 0, 0}
 {0, 0, 0, 0, 0, 0, 0, 0}
 {0, 0, 0, 0, 0, 0, 0, 0}
 {1, 1, 1, 1, 1, 1, 1, 1}
 {4, 2, 3, 5, 6, 3, 2, 4}
 } 
 */

bool makeMove(int mouseX, int mouseY, int state[CHESS_SIDE][CHESS_SIDE], shared_ptr<Piece> movePiece, int *capturedX, int *capturedY, int *capturedPiece);
void capturePiece(int capturedX, int capturedY, vector<shared_ptr<Piece>> arr);

int main() {
  SDL_Window *window;
  SDL_Surface *screen;
  SDL_Renderer *renderer;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Could not init video: " << SDL_GetError();
  }
  else {
    cout << "Successful init video\n";
  }

  window = SDL_CreateWindow(
    "Yet Another Chess Game",
    0, 0, 1280, 720,
    SDL_WINDOW_SHOWN
  );

  screen = SDL_GetWindowSurface(window);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  int state[CHESS_SIDE][CHESS_SIDE] = {
    {BLACK*ROOK, BLACK*KNIGHT, BLACK*BISHOP, BLACK*QUEEN, BLACK*KING, BLACK*BISHOP, BLACK*KNIGHT, BLACK*ROOK},
    {BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN},
    {WHITE*ROOK, WHITE*KNIGHT, WHITE*BISHOP, WHITE*QUEEN, WHITE*KING, WHITE*BISHOP, WHITE*KNIGHT, WHITE*ROOK}
  };

  /* CHESSBOARD */
  TexturedRect board(renderer, "../images/Chessboard2048.bmp");
  board.setProperties(0, 0, 720, 720);

  /* WHITE PIECES */
  // Array to store the pieces
  vector<shared_ptr<Piece>> wPiecesArr;
  // King
  shared_ptr<Piece> wK = make_shared<King>(renderer, "../images/wk.bmp", true, false, 4, 7);
  wPiecesArr.push_back(wK);
  // Queen
  shared_ptr<Piece> wQ = make_shared<Queen>(renderer, "../images/wq.bmp", true, false, 3, 7);
  wPiecesArr.push_back(wQ);
  // Bishops
  shared_ptr<Piece> wB1 = make_shared<Bishop>(renderer, "../images/wb.bmp", true, false, 2, 7);
  wPiecesArr.push_back(wB1);
  shared_ptr<Piece> wB2 = make_shared<Bishop>(renderer, "../images/wb.bmp", true, false, 5, 7);
  wPiecesArr.push_back(wB2);
  // Knights
  shared_ptr<Piece> wN1 = make_shared<Knight>(renderer, "../images/wn.bmp", true, false, 1, 7);
  wPiecesArr.push_back(wN1);
  shared_ptr<Piece> wN2 = make_shared<Knight>(renderer, "../images/wn.bmp", true, false, 6, 7);
  wPiecesArr.push_back(wN2);
  // Rooks
  shared_ptr<Piece> wR1 = make_shared<Rook>(renderer, "../images/wr.bmp", true, false, 0, 7);
  wPiecesArr.push_back(wR1);
  shared_ptr<Piece> wR2 = make_shared<Rook>(renderer, "../images/wr.bmp", true, false, 7, 7);
  wPiecesArr.push_back(wR2);
  /* WHITE PIECES */
  // Array to store the pawns
  vector<shared_ptr<Piece>> wPArr;
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<Piece> wP = make_shared<Pawn>(renderer, "../images/wp.bmp", true, true, i, 6);
    wPArr.push_back(wP);
  }

  /* BLACK PIECES */
  // Array to store the pieces
  vector<shared_ptr<Piece>> bPiecesArr;
  // King
  shared_ptr<Piece> bK = make_shared<King>(renderer, "../images/bk.bmp", false, false, 4, 0);
  bPiecesArr.push_back(bK);
  // Queen
  shared_ptr<Piece> bQ = make_shared<Queen>(renderer, "../images/bq.bmp", false, false, 3, 0);
  bPiecesArr.push_back(bQ);
  // Bishops
  shared_ptr<Piece> bB1 = make_shared<Bishop>(renderer, "../images/bb.bmp", false, false, 2, 0);
  bPiecesArr.push_back(bB1);
  shared_ptr<Piece> bB2 = make_shared<Bishop>(renderer, "../images/bb.bmp", false, false, 5, 0);
  bPiecesArr.push_back(bB2);
  // Knights
  shared_ptr<Piece> bN1 = make_shared<Knight>(renderer, "../images/bn.bmp", false, false, 1, 0);
  bPiecesArr.push_back(bN1);
  shared_ptr<Piece> bN2 = make_shared<Knight>(renderer, "../images/bn.bmp", false, false, 6, 0);
  bPiecesArr.push_back(bN2);
  // Rooks
  shared_ptr<Piece> bR1 = make_shared<Rook>(renderer, "../images/br.bmp", false, false, 0, 0);
  bPiecesArr.push_back(bR1);
  shared_ptr<Piece> bR2 = make_shared<Rook>(renderer, "../images/br.bmp", false, false, 7, 0);
  bPiecesArr.push_back(bR2);
  // Array to store the pawns
  vector<shared_ptr<Piece>> bPArr;
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<Piece> bP = make_shared<Pawn>(renderer, "../images/bp.bmp", false, true, i, 1);
    bPArr.push_back(bP);
  }

  SDL_Rect hoverRect;
  hoverRect.x = 0;
  hoverRect.y = 0;
  hoverRect.w = PIECE_SIDE;
  hoverRect.h = PIECE_SIDE;

  // Game loop
  bool gameRunning = true;
  bool leftMBPressed = false;
  bool drawHoverRect = false;
  int mouseX;
  int mouseY;
  shared_ptr<Piece> currPiece;
  shared_ptr<Piece> movePiece;
  int originalX, originalY;
  while (gameRunning) {
    SDL_GetMouseState(&mouseX, &mouseY);

    /* EVENT HANDLING */
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gameRunning = false;
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          gameRunning = false;
        }
      }
      if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        leftMBPressed = true;
      }
      if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        leftMBPressed = false;
      }
    }

    /* RENDERING */
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);

    // Rendering the board
    board.render(renderer);

    if (drawHoverRect) {
      hoverRect.x = mouseX - (mouseX % SQUARE_SIDE);
      hoverRect.y = mouseY - (mouseY % SQUARE_SIDE);
      SDL_RenderFillRect(renderer, &hoverRect);
    }

    // Rendering white pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (wPiecesArr[i]->getIsAlive() &&
          wPiecesArr[i] != movePiece) {
        wPiecesArr[i]->getTRect()->render(renderer);
      }
      if (wPArr[i]->getIsAlive() &&
          wPArr[i] != movePiece) {
        wPArr[i]->getTRect()->render(renderer);
      }
    }

    // Rendering black pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (bPiecesArr[i]->getIsAlive() &&
          bPiecesArr[i] != movePiece) {
        bPiecesArr[i]->getTRect()->render(renderer);
      }
      if (bPArr[i]->getIsAlive() &&
          bPArr[i] != movePiece) {
        bPArr[i]->getTRect()->render(renderer);
      }
    }

    if (movePiece != NULL) {
      movePiece->getTRect()->render(renderer);
    }

    /* LOGIC */ 
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (wPiecesArr[i]->getIsAlive() &&
          wPiecesArr[i]->getTRect()->getXValue() <= mouseX && 
          mouseX <= (wPiecesArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
          wPiecesArr[i]->getTRect()->getYValue() <= mouseY && 
          mouseY <= (wPiecesArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
        currPiece = wPiecesArr[i];
        originalX = currPiece->getTRect()->getXValue();
        originalY = currPiece->getTRect()->getYValue();
      }
    }

    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (wPArr[i]->getIsAlive() &&
          wPArr[i]->getTRect()->getXValue() <= mouseX && 
          mouseX <= (wPArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
          wPArr[i]->getTRect()->getYValue() <= mouseY && 
          mouseY <= (wPArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
        currPiece = wPArr[i];
        originalX = currPiece->getTRect()->getXValue();
        originalY = currPiece->getTRect()->getYValue();
      }
    }
    
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (bPiecesArr[i]->getIsAlive() &&
          bPiecesArr[i]->getTRect()->getXValue() <= mouseX && 
          mouseX <= (bPiecesArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
          bPiecesArr[i]->getTRect()->getYValue() <= mouseY && 
          mouseY <= (bPiecesArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
        currPiece = bPiecesArr[i];
        originalX = currPiece->getTRect()->getXValue();
        originalY = currPiece->getTRect()->getYValue();
      }
    }
    
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (bPArr[i]->getIsAlive() &&
          bPArr[i]->getTRect()->getXValue() <= mouseX && 
          mouseX <= (bPArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
          bPArr[i]->getTRect()->getYValue() <= mouseY && 
          mouseY <= (bPArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
        currPiece = bPArr[i];
        originalX = currPiece->getTRect()->getXValue();
        originalY = currPiece->getTRect()->getYValue();
      }
    }

    if (leftMBPressed && currPiece != NULL) {
      movePiece = currPiece;
      movePiece->getTRect()->setCoordinates(mouseX - PIECE_SIDE/2, mouseY - PIECE_SIDE/2);
      if (mouseX < 720) {
        drawHoverRect = true;
      }
    }

    if (!leftMBPressed) {
        int capturedX = -1;
        int capturedY = -1;
        int capturedPiece = EMPTY;
      if (movePiece != NULL) {
        int newX, newY;
        // bool check = movePiece->makeMove(mouseX, mouseY, state);
        // cout << check << endl;
        if (mouseX < 720 && makeMove(mouseX, mouseY, state, movePiece, &capturedX, &capturedY, &capturedPiece)) {
          newX = mouseX - (mouseX % SQUARE_SIDE);
          newY = mouseY - (mouseY % SQUARE_SIDE);
          if (capturedX != -1 && capturedY != -1 & capturedPiece != EMPTY) {
            if (capturedPiece < EMPTY) {
              if (abs(capturedPiece) == PAWN) {
                capturePiece(capturedX, capturedY, bPArr);
              }
              else {
                capturePiece(capturedX, capturedY, bPiecesArr);
              }
            }
            else {
              if (abs(capturedPiece) == PAWN) {
                capturePiece(capturedX, capturedY, wPArr);
              }
              else {
                capturePiece(capturedX, capturedY, wPiecesArr);
              }
            }
          }
        }
        else {
          newX = originalX;
          newY = originalY;
        }
        movePiece->getTRect()->setCoordinates(newX, newY);
      }
      currPiece = NULL;
      movePiece = NULL;
      originalX = 0;
      originalY = 0;
      capturedX = -1;
      capturedY = -1;
      capturedPiece = EMPTY;
      drawHoverRect = false;
    }

    SDL_RenderPresent(renderer);

  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool makeMove(int mouseX, int mouseY, int state[CHESS_SIDE][CHESS_SIDE], shared_ptr<Piece> movePiece, int *capturedX, int *capturedY, int *capturedPiece) {
  vector<tuple<int, int>> validSquares = movePiece->getValidSquares(state);
  for (int i = 0; i < validSquares.size(); i++) {
    int currX = get<0>(validSquares[i])*SQUARE_SIDE;
    int currY = get<1>(validSquares[i])*SQUARE_SIDE;
    if (currX <= mouseX && mouseX <= currX + SQUARE_SIDE &&
        currY <= mouseY && mouseY <= currY + SQUARE_SIDE) {
      if (abs(state[movePiece->getSquareY()][movePiece->getSquareX()]) == PAWN ||
          abs(state[movePiece->getSquareY()][movePiece->getSquareX()]) == KING ||
          abs(state[movePiece->getSquareY()][movePiece->getSquareX()]) == ROOK) {
        if (!movePiece->getHasMoved()) {movePiece->setHasMoved(true);}
      }

      // If the piece just moved
      if (state[get<1>(validSquares[i])][get<0>(validSquares[i])] == EMPTY) {
        int temp = state[get<1>(validSquares[i])][get<0>(validSquares[i])];
        state[get<1>(validSquares[i])][get<0>(validSquares[i])] = state[movePiece->getSquareY()][movePiece->getSquareX()];
        state[movePiece->getSquareY()][movePiece->getSquareX()] = temp;
      }

      // If the piece just captured
      else {
        *capturedPiece = state[get<1>(validSquares[i])][get<0>(validSquares[i])];
        state[get<1>(validSquares[i])][get<0>(validSquares[i])] = state[movePiece->getSquareY()][movePiece->getSquareX()];
        state[movePiece->getSquareY()][movePiece->getSquareX()] = EMPTY;
        *capturedX = get<0>(validSquares[i]);
        *capturedY = get<1>(validSquares[i]);
      }

      movePiece->setSquareXY(get<0>(validSquares[i]), get<1>(validSquares[i]));
      return true;
    }
  }
  return false;
}

void capturePiece(int capturedX, int capturedY, vector<shared_ptr<Piece>> arr) {
  for (int i = 0; i < CHESS_SIDE; i++) {
    if (arr[i]->getIsAlive() && capturedX == arr[i]->getSquareX()
        && capturedY == arr[i]->getSquareY()) {
      arr[i]->setIsAlive(false);
    } 
  }
}
