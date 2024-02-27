// Right now, compile program with: make
// g++ chess_game.cpp ./glad/src/glad.c -I./glad/include -o chess_game -lSDL2 

#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>

#include "../include/textured_rect.hpp"

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
  // Array that stores the pieces
  vector<shared_ptr<TexturedRect>> wPiecesArr;
  // King
  shared_ptr<TexturedRect> wK = make_shared<TexturedRect>(renderer, "../images/wk.bmp");
  wK->setProperties(4*SQUARE_SIDE, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wK);
  // Queen
  shared_ptr<TexturedRect> wQ = make_shared<TexturedRect>(renderer, "../images/wq.bmp");
  wQ->setProperties(3*SQUARE_SIDE, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wQ);
  // Bishops
  shared_ptr<TexturedRect> wB1 = make_shared<TexturedRect>(renderer, "../images/wb.bmp");
  wB1->setProperties(2*SQUARE_SIDE, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wB1);
  shared_ptr<TexturedRect> wB2 = make_shared<TexturedRect>(renderer, "../images/wb.bmp");
  wB2->setProperties(5*SQUARE_SIDE, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wB2);
  // Knights
  shared_ptr<TexturedRect> wN1 = make_shared<TexturedRect>(renderer, "../images/wn.bmp");
  wN1->setProperties(SQUARE_SIDE, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wN1);
  shared_ptr<TexturedRect> wN2 = make_shared<TexturedRect>(renderer, "../images/wn.bmp");
  wN2->setProperties(6*SQUARE_SIDE, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wN2);
  // Rooks
  shared_ptr<TexturedRect> wR1 = make_shared<TexturedRect>(renderer, "../images/wr.bmp");
  wR1->setProperties(0, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wR1);
  shared_ptr<TexturedRect> wR2 = make_shared<TexturedRect>(renderer, "../images/wr.bmp");
  wR2->setProperties(7*SQUARE_SIDE, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wR2);

  // Array to store the pawns
  vector<shared_ptr<TexturedRect>> wPArr;
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<TexturedRect> wP = make_shared<TexturedRect>(renderer, "../images/wp.bmp");
    wP->setProperties(i*SQUARE_SIDE, WHITE_PAWN_ROW, PIECE_SIDE, PIECE_SIDE);
    wPArr.push_back(wP);
  }

  /* BLACK PIECES */
  // Array to store the pieces
  vector<shared_ptr<TexturedRect>> bPiecesArr;
  // King
  shared_ptr<TexturedRect> bK = make_shared<TexturedRect>(renderer, "../images/bk.bmp");
  bK->setProperties(4*SQUARE_SIDE, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bK);
  // Queen
  shared_ptr<TexturedRect> bQ = make_shared<TexturedRect>(renderer, "../images/bq.bmp");
  bQ->setProperties(3*SQUARE_SIDE, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bQ);
  // Bishops
  shared_ptr<TexturedRect> bB1 = make_shared<TexturedRect>(renderer, "../images/bb.bmp");
  bB1->setProperties(2*SQUARE_SIDE, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bB1);
  shared_ptr<TexturedRect> bB2 = make_shared<TexturedRect>(renderer, "../images/bb.bmp");
  bB2->setProperties(5*SQUARE_SIDE, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bB2);
  // Knights
  shared_ptr<TexturedRect> bN1 = make_shared<TexturedRect>(renderer, "../images/bn.bmp");
  bN1->setProperties(SQUARE_SIDE, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bN1);
  shared_ptr<TexturedRect> bN2 = make_shared<TexturedRect>(renderer, "../images/bn.bmp");
  bN2->setProperties(6*SQUARE_SIDE, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bN2);
  // Rooks
  shared_ptr<TexturedRect> bR1 = make_shared<TexturedRect>(renderer, "../images/br.bmp");
  bR1->setProperties(0, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bR1);
  shared_ptr<TexturedRect> bR2 = make_shared<TexturedRect>(renderer, "../images/br.bmp");
  bR2->setProperties(7*SQUARE_SIDE, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bR2);

  // Array to store the pawns
  vector<shared_ptr<TexturedRect>> bPArr;
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<TexturedRect> bP = make_shared<TexturedRect>(renderer, "../images/bp.bmp");
    bP->setProperties(i*SQUARE_SIDE, BLACK_PAWN_ROW, PIECE_SIDE, PIECE_SIDE);
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
  shared_ptr<TexturedRect> currPiece;
  shared_ptr<TexturedRect> movePiece;
  int originalX, originalY;
  while (gameRunning) {
    SDL_GetMouseState(&mouseX, &mouseY);
    // if (mouseX > 720) {
      // leftMBPressed = false;
    // }

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

    // SDL_RenderFillRect(renderer, &hoverRect);
    // Rendering the board
    board.render(renderer);

    // SDL_RenderDrawRect(renderer, &hoverRect);
    if (drawHoverRect) {
      hoverRect.x = mouseX - (mouseX % SQUARE_SIDE);
      hoverRect.y = mouseY - (mouseY % SQUARE_SIDE);
      SDL_RenderFillRect(renderer, &hoverRect);
    }

    // Rendering white pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (wPiecesArr[i] != movePiece) {
        wPiecesArr[i]->render(renderer);
      }
      if (wPArr[i] != movePiece) {
        wPArr[i]->render(renderer);
      }
    }

    // Rendering black pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (bPiecesArr[i] != movePiece) {
        bPiecesArr[i]->render(renderer);
      }
      if (bPArr[i] != movePiece) {
        bPArr[i]->render(renderer);
      }
    }

    if (movePiece != NULL) {
      movePiece->render(renderer);
    }

    /* LOGIC */ 
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (wPiecesArr[i]->getXValue() <= mouseX && 
          mouseX <= (wPiecesArr[i]->getXValue() + PIECE_SIDE) &&
          wPiecesArr[i]->getYValue() <= mouseY && 
          mouseY <= (wPiecesArr[i]->getYValue() + PIECE_SIDE)) {
        currPiece = wPiecesArr[i];
        originalX = currPiece->getXValue();
        originalY = currPiece->getYValue();
      }
    }
    
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (wPArr[i]->getXValue() <= mouseX && 
          mouseX <= (wPArr[i]->getXValue() + PIECE_SIDE) &&
          wPArr[i]->getYValue() <= mouseY && 
          mouseY <= (wPArr[i]->getYValue() + PIECE_SIDE)) {
        currPiece = wPArr[i];
        originalX = currPiece->getXValue();
        originalY = currPiece->getYValue();
      }
    }
    
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (bPiecesArr[i]->getXValue() <= mouseX && 
          mouseX <= (bPiecesArr[i]->getXValue() + PIECE_SIDE) &&
          bPiecesArr[i]->getYValue() <= mouseY && 
          mouseY <= (bPiecesArr[i]->getYValue() + PIECE_SIDE)) {
        currPiece = bPiecesArr[i];
        originalX = currPiece->getXValue();
        originalY = currPiece->getYValue();
      }
    }
    
    for (int i = 0; i < CHESS_SIDE && currPiece == NULL; i++) {
      if (bPArr[i]->getXValue() <= mouseX && 
          mouseX <= (bPArr[i]->getXValue() + PIECE_SIDE) &&
          bPArr[i]->getYValue() <= mouseY && 
          mouseY <= (bPArr[i]->getYValue() + PIECE_SIDE)) {
        currPiece = bPArr[i];
        originalX = currPiece->getXValue();
        originalY = currPiece->getYValue();
      }
    }

    if (leftMBPressed && currPiece != NULL) {
      movePiece = currPiece;
      movePiece->setCoordinates(mouseX - PIECE_SIDE/2, mouseY - PIECE_SIDE/2);
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
        movePiece->setCoordinates(squareX, squareY);
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
