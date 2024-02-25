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
#define PIECE_SIDE 80
#define EXTRA 5
#define WHITE_PAWN_ROW 545
#define WHITE_PIECE_ROW 635
#define BLACK_PAWN_ROW 95
#define BLACK_PIECE_ROW 5

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

  // The board
  TexturedRect board(renderer, "../images/Chessboard2048.bmp");
  board.setProperties(0, 0, 720, 720);

  // White pieces
  vector<shared_ptr<TexturedRect>> wPiecesArr;
  shared_ptr<TexturedRect> wK = make_shared<TexturedRect>(renderer, "../images/wk.bmp");
  wK->setProperties(4*SQUARE_SIDE + EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wK);
  shared_ptr<TexturedRect> wQ = make_shared<TexturedRect>(renderer, "../images/wq.bmp");
  wQ->setProperties(3*SQUARE_SIDE + EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wQ);
  shared_ptr<TexturedRect> wB1 = make_shared<TexturedRect>(renderer, "../images/wb.bmp");
  wB1->setProperties(2*SQUARE_SIDE + EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wB1);
  shared_ptr<TexturedRect> wB2 = make_shared<TexturedRect>(renderer, "../images/wb.bmp");
  wB2->setProperties(5*SQUARE_SIDE + EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wB2);
  shared_ptr<TexturedRect> wN1 = make_shared<TexturedRect>(renderer, "../images/wn.bmp");
  wN1->setProperties(SQUARE_SIDE + EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wN1);
  shared_ptr<TexturedRect> wN2 = make_shared<TexturedRect>(renderer, "../images/wn.bmp");
  wN2->setProperties(6*SQUARE_SIDE + EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wN2);
  shared_ptr<TexturedRect> wR1 = make_shared<TexturedRect>(renderer, "../images/wr.bmp");
  wR1->setProperties(EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wR1);
  shared_ptr<TexturedRect> wR2 = make_shared<TexturedRect>(renderer, "../images/wr.bmp");
  wR2->setProperties(7*SQUARE_SIDE + EXTRA, WHITE_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  wPiecesArr.push_back(wR2);
  // TexturedRect *wPArr = (TexturedRect *)malloc(sizeof(TexturedRect) * CHESS_SIDE);
  vector<shared_ptr<TexturedRect>> wPArr;
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<TexturedRect> wP = make_shared<TexturedRect>(renderer, "../images/wp.bmp");
    wP->setProperties(i*SQUARE_SIDE + EXTRA, WHITE_PAWN_ROW, PIECE_SIDE, PIECE_SIDE);
    wPArr.push_back(wP);
  }
  // for (int i = 0; i < CHESS_SIDE; i++) {
    // wPArr[i]->setProperties(i*SQUARE_SIDE + EXTRA, WHITE_PAWN_ROW, PIECE_SIDE, PIECE_SIDE);
  // }


  // Black pieces
  vector<shared_ptr<TexturedRect>> bPiecesArr;
  shared_ptr<TexturedRect> bK = make_shared<TexturedRect>(renderer, "../images/bk.bmp");
  bK->setProperties(4*SQUARE_SIDE + EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bK);
  shared_ptr<TexturedRect> bQ = make_shared<TexturedRect>(renderer, "../images/bq.bmp");
  bQ->setProperties(3*SQUARE_SIDE + EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bQ);
  shared_ptr<TexturedRect> bB1 = make_shared<TexturedRect>(renderer, "../images/bb.bmp");
  bB1->setProperties(2*SQUARE_SIDE + EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bB1);
  shared_ptr<TexturedRect> bB2 = make_shared<TexturedRect>(renderer, "../images/bb.bmp");
  bB2->setProperties(5*SQUARE_SIDE + EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bB2);
  shared_ptr<TexturedRect> bN1 = make_shared<TexturedRect>(renderer, "../images/bn.bmp");
  bN1->setProperties(SQUARE_SIDE + EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bN1);
  shared_ptr<TexturedRect> bN2 = make_shared<TexturedRect>(renderer, "../images/bn.bmp");
  bN2->setProperties(6*SQUARE_SIDE + EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bN2);
  shared_ptr<TexturedRect> bR1 = make_shared<TexturedRect>(renderer, "../images/br.bmp");
  bR1->setProperties(EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bR1);
  shared_ptr<TexturedRect> bR2 = make_shared<TexturedRect>(renderer, "../images/br.bmp");
  bR2->setProperties(7*SQUARE_SIDE + EXTRA, BLACK_PIECE_ROW, PIECE_SIDE, PIECE_SIDE);
  bPiecesArr.push_back(bR2);
  vector<shared_ptr<TexturedRect>> bPArr;
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<TexturedRect> bP = make_shared<TexturedRect>(renderer, "../images/bp.bmp");
    bP->setProperties(i*SQUARE_SIDE + EXTRA, BLACK_PAWN_ROW, PIECE_SIDE, PIECE_SIDE);
    bPArr.push_back(bP);
  }
  // for (int i = 0; i < CHESS_SIDE; i++) {
    // bPArr[i]->setProperties(i*SQUARE_SIDE + EXTRA, BLACK_PAWN_ROW, PIECE_SIDE, PIECE_SIDE);
  // }

  // Game loop
  bool gameRunning = true;
  while (gameRunning) {

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
    }

    /* RENDERING */
    // Rendering the board
    board.render(renderer);

    // Rendering white pieces
    // wK.render(renderer);
    // wQ.render(renderer);
    // wB1.render(renderer);
    // wB2.render(renderer);
    // wN1.render(renderer);
    // wN2.render(renderer);
    // wR1.render(renderer);
    // wR2.render(renderer);
    for (int i = 0; i < CHESS_SIDE; i++) {
      wPiecesArr[i]->render(renderer);
    }
    for (int i = 0; i < CHESS_SIDE; i++) {
      wPArr[i]->render(renderer);
    }

    // Rendering black pieces
    // bK.render(renderer);
    // bQ.render(renderer);
    // bB1.render(renderer);
    // bB2.render(renderer);
    // bN1.render(renderer);
    // bN2.render(renderer);
    // bR1.render(renderer);
    // bR2.render(renderer);
    for (int i = 0; i < CHESS_SIDE; i++) {
      bPiecesArr[i]->render(renderer);
    }
    for (int i = 0; i < CHESS_SIDE; i++) {
      bPArr[i]->render(renderer);
    }

    SDL_RenderPresent(renderer);

  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}
