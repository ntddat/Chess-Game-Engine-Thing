// Right now, compile program with: make
// g++ chess_game.cpp ./glad/src/glad.c -I./glad/include -o chess_game -lSDL2 

#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"
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

  /* CHESSBOARD */
  TexturedRect board(renderer, "../images/Chessboard2048.bmp");
  board.setProperties(0, 0, 720, 720);

  /* WHITE PIECES */
  // Array to store the pieces
  vector<shared_ptr<Piece>> wPiecesArr;
  // King
  shared_ptr<Piece> wK = make_shared<Piece>(renderer, "../images/wk.bmp", true, false, 4*SQUARE_SIDE);
  wPiecesArr.push_back(wK);
  // Queen
  shared_ptr<Piece> wQ = make_shared<Piece>(renderer, "../images/wq.bmp", true, false, 3*SQUARE_SIDE);
  wPiecesArr.push_back(wQ);
  // Bishops
  shared_ptr<Piece> wB1 = make_shared<Piece>(renderer, "../images/wb.bmp", true, false, 2*SQUARE_SIDE);
  wPiecesArr.push_back(wB1);
  shared_ptr<Piece> wB2 = make_shared<Piece>(renderer, "../images/wb.bmp", true, false, 5*SQUARE_SIDE);
  wPiecesArr.push_back(wB2);
  // Knights
  shared_ptr<Piece> wN1 = make_shared<Piece>(renderer, "../images/wn.bmp", true, false, SQUARE_SIDE);
  wPiecesArr.push_back(wN1);
  shared_ptr<Piece> wN2 = make_shared<Piece>(renderer, "../images/wn.bmp", true, false, 6*SQUARE_SIDE);
  wPiecesArr.push_back(wN2);
  // Rooks
  shared_ptr<Piece> wR1 = make_shared<Piece>(renderer, "../images/wr.bmp", true, false, 0);
  wPiecesArr.push_back(wR1);
  shared_ptr<Piece> wR2 = make_shared<Piece>(renderer, "../images/wr.bmp", true, false, 7*SQUARE_SIDE);
  wPiecesArr.push_back(wR2);
  /* WHITE PIECES */
  // Array to store the pawns
  vector<shared_ptr<Piece>> wPArr;
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
      shared_ptr<Piece> wP = make_shared<Piece>(renderer, "../images/wp.bmp", true, true, i*SQUARE_SIDE);
    wPArr.push_back(wP);
  }

  /* BLACK PIECES */
  // Array to store the pieces
  vector<shared_ptr<Piece>> bPiecesArr;
  // King
  shared_ptr<Piece> bK = make_shared<Piece>(renderer, "../images/bk.bmp", false, false, 4*SQUARE_SIDE);
  bPiecesArr.push_back(bK);
  // Queen
  shared_ptr<Piece> bQ = make_shared<Piece>(renderer, "../images/bq.bmp", false, false, 3*SQUARE_SIDE);
  bPiecesArr.push_back(bQ);
  // Bishops
  shared_ptr<Piece> bB1 = make_shared<Piece>(renderer, "../images/bb.bmp", false, false, 2*SQUARE_SIDE);
  bPiecesArr.push_back(bB1);
  shared_ptr<Piece> bB2 = make_shared<Piece>(renderer, "../images/bb.bmp", false, false, 5*SQUARE_SIDE);
  bPiecesArr.push_back(bB2);
  // Knights
  shared_ptr<Piece> bN1 = make_shared<Piece>(renderer, "../images/bn.bmp", false, false, SQUARE_SIDE);
  bPiecesArr.push_back(bN1);
  shared_ptr<Piece> bN2 = make_shared<Piece>(renderer, "../images/bn.bmp", false, false, 6*SQUARE_SIDE);
  bPiecesArr.push_back(bN2);
  // Rooks
  shared_ptr<Piece> bR1 = make_shared<Piece>(renderer, "../images/br.bmp", false, false, 0);
  bPiecesArr.push_back(bR1);
  shared_ptr<Piece> bR2 = make_shared<Piece>(renderer, "../images/br.bmp", false, false, 7*SQUARE_SIDE);
  bPiecesArr.push_back(bR2);
  // Array to store the pawns
  vector<shared_ptr<Piece>> bPArr;
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<Piece> bP = make_shared<Piece>(renderer, "../images/bp.bmp", false, true, i*SQUARE_SIDE);
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
      if (wPiecesArr[i] != movePiece) {
        wPiecesArr[i]->getTRect()->render(renderer);
      }
      if (wPArr[i] != movePiece) {
        wPArr[i]->getTRect()->render(renderer);
      }
    }

    // Rendering black pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (bPiecesArr[i] != movePiece) {
        bPiecesArr[i]->getTRect()->render(renderer);
      }
      if (bPArr[i] != movePiece) {
        bPArr[i]->getTRect()->render(renderer);
      }
    }

    if (movePiece != NULL) {
      movePiece->getTRect()->render(renderer);
    }

    /* LOGIC */ 
    for (int i = 0; i < CHESS_SIDE - 1 && currPiece == NULL; i++) {
      if (wPiecesArr[i]->getTRect()->getXValue() <= mouseX && 
          mouseX <= (wPiecesArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
          wPiecesArr[i]->getTRect()->getYValue() <= mouseY && 
          mouseY <= (wPiecesArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
        currPiece = wPiecesArr[i];
        originalX = currPiece->getTRect()->getXValue();
        originalY = currPiece->getTRect()->getYValue();
      }
    }

    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (wPArr[i]->getTRect()->getXValue() <= mouseX && 
          mouseX <= (wPArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
          wPArr[i]->getTRect()->getYValue() <= mouseY && 
          mouseY <= (wPArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
        currPiece = wPArr[i];
        originalX = currPiece->getTRect()->getXValue();
        originalY = currPiece->getTRect()->getYValue();
      }
    }
    
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (bPiecesArr[i]->getTRect()->getXValue() <= mouseX && 
          mouseX <= (bPiecesArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
          bPiecesArr[i]->getTRect()->getYValue() <= mouseY && 
          mouseY <= (bPiecesArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
        currPiece = bPiecesArr[i];
        originalX = currPiece->getTRect()->getXValue();
        originalY = currPiece->getTRect()->getYValue();
      }
    }
    
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (bPArr[i]->getTRect()->getXValue() <= mouseX && 
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
      if (movePiece != NULL) {
        int squareX, squareY;
        if (mouseX < 720) {
          squareX = mouseX - (mouseX % SQUARE_SIDE);
          squareY = mouseY - (mouseY % SQUARE_SIDE);
        }
        else {
          squareX = originalX;
          squareY = originalY;
        }
        movePiece->getTRect()->setCoordinates(squareX, squareY);
      }
      currPiece = NULL;
      movePiece = NULL;
      originalX = 0;
      originalY = 0;
      drawHoverRect = false;
    }


    SDL_RenderPresent(renderer);

  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
