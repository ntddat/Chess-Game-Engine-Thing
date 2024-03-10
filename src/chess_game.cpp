// Right now, compile program with: make
// g++ chess_game.cpp ./glad/src/glad.c -I./glad/include -o chess_game -lSDL2 

#include <iostream>
#include <vector>
#include <memory>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// #pragma once

#include "../include/text_rect.hpp"
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

#define NOTYET -3
#define WHITE_RESIGNED -2
#define WHITE_CHECKMATED -1
#define DRAW 0
#define BLACK_CHECKMATED 1
#define BLACK_RESIGNED 2

#define FIFTY_MOVE 100  // lmao

#define CASTLE_LONG -20
#define CASTLE_SHORT -30

#define MENU 0
#define VS_PLAYER 1
#define VS_ENGINE 2

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

// bool makeMove(int mouseX, int mouseY, int state[CHESS_SIDE][CHESS_SIDE], shared_ptr<Piece> movePiece, int *capturedX, int *capturedY, int *capturedPiece, bool *pawnMovedTwo, bool *isEnPassantNow);
// void capturePiece(int capturedX, int capturedY, vector<shared_ptr<Piece>> arr);
void initPieces(SDL_Renderer *&renderer);
void renderPieces(SDL_Renderer *&renderer, shared_ptr<Piece> movePiece);
void reset(SDL_Renderer *&renderer, int state[CHESS_SIDE][CHESS_SIDE], int startingState[CHESS_SIDE][CHESS_SIDE], bool *isWhiteTurn);
bool isCheckmate(int state[CHESS_SIDE][CHESS_SIDE], bool isWhiteTurn);

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

  int startingState[CHESS_SIDE][CHESS_SIDE] = {
    {BLACK*ROOK, BLACK*KNIGHT, BLACK*BISHOP, BLACK*QUEEN, BLACK*KING, BLACK*BISHOP, BLACK*KNIGHT, BLACK*ROOK},
    {BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN, BLACK*PAWN},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN, WHITE*PAWN},
    {WHITE*ROOK, WHITE*KNIGHT, WHITE*BISHOP, WHITE*QUEEN, WHITE*KING, WHITE*BISHOP, WHITE*KNIGHT, WHITE*ROOK}
  };
  int state[CHESS_SIDE][CHESS_SIDE];
  for (int i = 0; i < CHESS_SIDE; i++) {
    for (int j = 0; j < CHESS_SIDE; j++) {
      state[i][j] = startingState[i][j];
    }
  }

  /* CHESSBOARD */
  TexturedRect board(renderer, "../images/Chessboard2048.bmp");
  board.setProperties(0, 0, 720, 720);

  initPieces(renderer);

  SDL_Rect hoverRect;
  hoverRect.x = 0;
  hoverRect.y = 0;
  hoverRect.w = PIECE_SIDE;
  hoverRect.h = PIECE_SIDE;

  TTF_Init();
  TTF_Font *font = TTF_OpenFont("../font/RobotoMonoNerdFontMono-Bold.ttf", 32);
  TextRect instructionsMenu1(renderer, font, "Press 1 for 2-Player Mode", 765, 200);
  TextRect instructionsMenu2(renderer, font, "Press 2 to play an engine", 765, 320);
  TextRect drawOption(renderer, font, "Press D to agree to a draw", 755, 50);
  TextRect whiteResignOption(renderer, font, "Press W to resign as white", 755, 100);
  TextRect blackResignOption(renderer, font, "Press B to resign as black", 755, 150);
  TextRect instructionsExit(renderer, font, "Press 0 to go back to menu", 755, 200);
  TextRect promotionKnight(renderer, font, "Press 1 to promote to Knight", 735, 250);
  TextRect promotionBishop(renderer, font, "Press 2 to promote to Bishop", 735, 300);
  TextRect promotionRook(renderer, font, "Press 3 to promote to Rook", 735, 350);
  TextRect promotionQueen(renderer, font, "Press 4 to promote to Queen", 735, 400);
  TextRect whiteCheckmated(renderer, font, "Checkmate! Black has won!", 765, 450);
  TextRect blackCheckmated(renderer, font, "Checkmate! White has won!", 765, 450);
  TextRect whiteResigned(renderer, font, "White resigns! Black wins!", 760, 450);
  TextRect blackResigned(renderer, font, "Black resigns! White wins!", 760, 450);
  TextRect gameDrawn(renderer, font, "It's a draw! No one wins!", 760, 450);

  // Game loop
  bool gameRunning = true;
  bool leftMBPressed = false;
  bool drawHoverRect = false;
  int mouseX;
  int mouseY;
  shared_ptr<Piece> currPiece;
  shared_ptr<Piece> movePiece;
  int originalX, originalY;
  vector<tuple<int, int>> validMoves;
  vector<SDL_Rect> validMovesRects;
  int currLevel = MENU;
  bool isWhiteTurn = true;
  int gameEnds = NOTYET;
  bool isPromotion = false;
  shared_ptr<Piece> promotionPawn = NULL;
  int promoteTo = EMPTY;
  int fiftyMoveCheck = 0;
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
        if (currLevel == MENU && event.key.keysym.sym == SDLK_1) {
          currLevel = VS_PLAYER;
        }
        if (currLevel != MENU && event.key.keysym.sym == SDLK_0) {
          currLevel = MENU;
          gameEnds = NOTYET;
          reset(renderer, state, startingState, &isWhiteTurn);
        }
        if (currLevel != MENU && gameEnds == NOTYET) {
          switch (event.key.keysym.sym) {
            case SDLK_d:
              gameEnds = DRAW;
              break;
            case SDLK_w:
              gameEnds = WHITE_RESIGNED;
              break;
            case SDLK_b:
              gameEnds = BLACK_RESIGNED;
              break;
          }
        }
        if (currLevel != MENU && isPromotion && promoteTo == EMPTY) {
          switch (event.key.keysym.sym) {
            case SDLK_1:
              promoteTo = KNIGHT;
              break;
            case SDLK_2:
              promoteTo = BISHOP;
              break;
            case SDLK_3:
              promoteTo = ROOK;
              break;
            case SDLK_4:
              promoteTo = QUEEN;
              break;
          }
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
      for (int i = 0; i < validMovesRects.size(); i++) {
        SDL_RenderFillRect(renderer, &validMovesRects[i]);
      }
    }
    
    if (currLevel == MENU) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
      instructionsMenu1.render(renderer);
      instructionsMenu2.render(renderer);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
    else {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
      if (gameEnds == NOTYET) {
        drawOption.render(renderer);
        whiteResignOption.render(renderer);
        blackResignOption.render(renderer);
      }
      instructionsExit.render(renderer);
      if (isPromotion && promoteTo == EMPTY) {
        promotionKnight.render(renderer);
        promotionBishop.render(renderer);
        promotionRook.render(renderer);
        promotionQueen.render(renderer);
      }
      if (gameEnds == WHITE_RESIGNED) {
        whiteResigned.render(renderer);
      }
      else if (gameEnds == WHITE_CHECKMATED) {
        whiteCheckmated.render(renderer);
      }
      else if (gameEnds == DRAW) {
        gameDrawn.render(renderer);
      }
      else if (gameEnds == BLACK_CHECKMATED) {
        blackCheckmated.render(renderer);
      }
      else if (gameEnds == BLACK_RESIGNED) {
        blackResigned.render(renderer);
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }

    Piece::renderPieces(renderer, movePiece);

    /* LOGIC */ 
    if (currLevel != MENU) {
      if (gameEnds == NOTYET) {
        if (isWhiteTurn) {
          for (int i = 0; i < Piece::wPiecesArr.size() && currPiece == NULL; i++) {
            if (Piece::wPiecesArr[i]->getIsAlive() &&
                Piece::wPiecesArr[i]->getTRect()->getXValue() <= mouseX && 
                mouseX <= (Piece::wPiecesArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
                Piece::wPiecesArr[i]->getTRect()->getYValue() <= mouseY && 
                mouseY <= (Piece::wPiecesArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
              currPiece = Piece::wPiecesArr[i];
              originalX = currPiece->getTRect()->getXValue();
              originalY = currPiece->getTRect()->getYValue();
            }
          }

          for (int i = 0; i < Piece::wPArr.size() && currPiece == NULL; i++) {
            if (Piece::wPArr[i]->getIsAlive() &&
                Piece::wPArr[i]->getTRect()->getXValue() <= mouseX && 
                mouseX <= (Piece::wPArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
                Piece::wPArr[i]->getTRect()->getYValue() <= mouseY && 
                mouseY <= (Piece::wPArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
              currPiece = Piece::wPArr[i];
              originalX = currPiece->getTRect()->getXValue();
              originalY = currPiece->getTRect()->getYValue();
            }
          }
        }
        else {
          for (int i = 0; i < Piece::bPiecesArr.size() && currPiece == NULL; i++) {
            if (Piece::bPiecesArr[i]->getIsAlive() &&
                Piece::bPiecesArr[i]->getTRect()->getXValue() <= mouseX && 
                mouseX <= (Piece::bPiecesArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
                Piece::bPiecesArr[i]->getTRect()->getYValue() <= mouseY && 
                mouseY <= (Piece::bPiecesArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
              currPiece = Piece::bPiecesArr[i];
              originalX = currPiece->getTRect()->getXValue();
              originalY = currPiece->getTRect()->getYValue();
            }
          }
          
          for (int i = 0; i < Piece::bPArr.size() && currPiece == NULL; i++) {
            if (Piece::bPArr[i]->getIsAlive() &&
                Piece::bPArr[i]->getTRect()->getXValue() <= mouseX && 
                mouseX <= (Piece::bPArr[i]->getTRect()->getXValue() + PIECE_SIDE) &&
                Piece::bPArr[i]->getTRect()->getYValue() <= mouseY && 
                mouseY <= (Piece::bPArr[i]->getTRect()->getYValue() + PIECE_SIDE)) {
              currPiece = Piece::bPArr[i];
              originalX = currPiece->getTRect()->getXValue();
              originalY = currPiece->getTRect()->getYValue();
            }
          }
        }
      }

      if (isPromotion && promotionPawn != NULL && promoteTo != EMPTY) {
        if (promotionPawn->getIsWhite()) {
          state[promotionPawn->getSquareY()][promotionPawn->getSquareX()] = WHITE*promoteTo;
          for (int i = 0; i < Piece::wPArr.size(); i++) {
            if (promotionPawn == Piece::wPArr[i]) {
              shared_ptr<Piece> newPiece;
              switch (promoteTo) {
                case KNIGHT:
                  newPiece = make_shared<Knight>(renderer, "../images/wn.bmp", true, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
                case BISHOP:
                  newPiece = make_shared<Bishop>(renderer, "../images/wb.bmp", true, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
                case ROOK:
                  newPiece = make_shared<Rook>(renderer, "../images/wr.bmp", true, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
                case QUEEN:
                  newPiece = make_shared<Queen>(renderer, "../images/wq.bmp", true, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
              }
              Piece::wPiecesArr.push_back(newPiece);
              Piece::wPArr.erase(Piece::wPArr.begin() + i);
            }
          }
        }
        else {
          state[promotionPawn->getSquareY()][promotionPawn->getSquareX()] = BLACK*promoteTo;
          for (int i = 0; i < Piece::bPArr.size(); i++) {
            if (promotionPawn == Piece::bPArr[i]) {
              shared_ptr<Piece> newPiece;
              switch (promoteTo) {
                case KNIGHT:
                  newPiece = make_shared<Knight>(renderer, "../images/bn.bmp", false, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
                case BISHOP:
                  newPiece = make_shared<Bishop>(renderer, "../images/bb.bmp", false, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
                case ROOK:
                  newPiece = make_shared<Rook>(renderer, "../images/br.bmp", false, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
                case QUEEN:
                  newPiece = make_shared<Queen>(renderer, "../images/bq.bmp", false, false,
                                                 promotionPawn->getSquareX(), promotionPawn->getSquareY());
                  break;
              }
              Piece::bPiecesArr.push_back(newPiece);
              Piece::bPArr.erase(Piece::bPArr.begin() + i);
            }
          }

        }
        isPromotion = false;
        promotionPawn = NULL;
        promoteTo = EMPTY;
      }

      if (isCheckmate(state, isWhiteTurn)) {
        if (isWhiteTurn) {
          gameEnds = WHITE_CHECKMATED;  
        }
        else {
          gameEnds = BLACK_CHECKMATED;
        }
      }

      if (fiftyMoveCheck == FIFTY_MOVE) {
        gameEnds = DRAW;
      }

      if (leftMBPressed && currPiece != NULL && !isPromotion) {
        movePiece = currPiece;
        movePiece->getTRect()->setCoordinates(mouseX - PIECE_SIDE/2, mouseY - PIECE_SIDE/2);
        if (mouseX < 720) {
          drawHoverRect = true;
        }
        if (validMovesRects.size() == 0) {
          validMoves = movePiece->getValidSquares(state);
          for (int i = 0; i < validMoves.size(); i++) {
            SDL_Rect newRect;
            if (state[get<1>(validMoves[i])][get<0>(validMoves[i])]*state[movePiece->getSquareY()][movePiece->getSquareX()] < EMPTY) {
              newRect.x = get<0>(validMoves[i])*SQUARE_SIDE;
              newRect.y = get<1>(validMoves[i])*SQUARE_SIDE;
              newRect.w = SQUARE_SIDE;
              newRect.h = SQUARE_SIDE;
            }
            else {
              newRect.x = get<0>(validMoves[i])*SQUARE_SIDE + 40;
              newRect.y = get<1>(validMoves[i])*SQUARE_SIDE + 40;
              newRect.w = 10;
              newRect.h = 10;
            }
            validMovesRects.push_back(newRect);
          }
        }
      }

      if (!leftMBPressed) {
        if (movePiece != NULL) {
          int newX, newY;
          if (mouseX < 720 && movePiece->makeMove(state, mouseX, mouseY, &fiftyMoveCheck)) {
            if (abs(state[movePiece->getSquareY()][movePiece->getSquareX()]) == PAWN &&
                (movePiece->getSquareY() == 0 || movePiece->getSquareY() == 7))  {
              isPromotion = true;
              promotionPawn = movePiece;
            }
            if (movePiece != NULL) {
              newX = movePiece->getSquareX()*SQUARE_SIDE;
              newY = movePiece->getSquareY()*SQUARE_SIDE;
            }

            isWhiteTurn = !isWhiteTurn;
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
        drawHoverRect = false;
        validMovesRects.clear();
      }
    }

    SDL_RenderPresent(renderer);

  }

  TTF_CloseFont(font);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
void initPieces(SDL_Renderer *&renderer) {

  // Array to store the pieces
  shared_ptr<Piece> wR1 = make_shared<Rook>(renderer, "../images/wr.bmp", true, false, 0, 7);
  Piece::wPiecesArr.push_back(wR1);
  shared_ptr<Piece> wN1 = make_shared<Knight>(renderer, "../images/wn.bmp", true, false, 1, 7);
  Piece::wPiecesArr.push_back(wN1);
  shared_ptr<Piece> wB1 = make_shared<Bishop>(renderer, "../images/wb.bmp", true, false, 2, 7);
  Piece::wPiecesArr.push_back(wB1);
  shared_ptr<Piece> wQ = make_shared<Queen>(renderer, "../images/wq.bmp", true, false, 3, 7);
  Piece::wPiecesArr.push_back(wQ);
  shared_ptr<Piece> wK = make_shared<King>(renderer, "../images/wk.bmp", true, false, 4, 7);
  Piece::wPiecesArr.push_back(wK);
  shared_ptr<Piece> wB2 = make_shared<Bishop>(renderer, "../images/wb.bmp", true, false, 5, 7);
  Piece::wPiecesArr.push_back(wB2);
  shared_ptr<Piece> wN2 = make_shared<Knight>(renderer, "../images/wn.bmp", true, false, 6, 7);
  Piece::wPiecesArr.push_back(wN2);
  shared_ptr<Piece> wR2 = make_shared<Rook>(renderer, "../images/wr.bmp", true, false, 7, 7);
  Piece::wPiecesArr.push_back(wR2);
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<Piece> wP = make_shared<Pawn>(renderer, "../images/wp.bmp", true, true, i, 6);
    Piece::wPArr.push_back(wP);
  }

  // Array to store the pieces
  shared_ptr<Piece> bR1 = make_shared<Rook>(renderer, "../images/br.bmp", false, false, 0, 0);
  Piece::bPiecesArr.push_back(bR1);
  shared_ptr<Piece> bN1 = make_shared<Knight>(renderer, "../images/bn.bmp", false, false, 1, 0);
  Piece::bPiecesArr.push_back(bN1);
  shared_ptr<Piece> bB1 = make_shared<Bishop>(renderer, "../images/bb.bmp", false, false, 2, 0);
  Piece::bPiecesArr.push_back(bB1);
  shared_ptr<Piece> bQ = make_shared<Queen>(renderer, "../images/bq.bmp", false, false, 3, 0);
  Piece::bPiecesArr.push_back(bQ);
  shared_ptr<Piece> bK = make_shared<King>(renderer, "../images/bk.bmp", false, false, 4, 0);
  Piece::bPiecesArr.push_back(bK);
  shared_ptr<Piece> bB2 = make_shared<Bishop>(renderer, "../images/bb.bmp", false, false, 5, 0);
  Piece::bPiecesArr.push_back(bB2);
  shared_ptr<Piece> bN2 = make_shared<Knight>(renderer, "../images/bn.bmp", false, false, 6, 0);
  Piece::bPiecesArr.push_back(bN2);
  shared_ptr<Piece> bR2 = make_shared<Rook>(renderer, "../images/br.bmp", false, false, 7, 0);
  Piece::bPiecesArr.push_back(bR2);
  // Pawns
  for (int i = 0; i < CHESS_SIDE; i++) {
    shared_ptr<Piece> bP = make_shared<Pawn>(renderer, "../images/bp.bmp", false, true, i, 1);
    Piece::bPArr.push_back(bP);
  }
}

void renderPieces(SDL_Renderer *&renderer, shared_ptr<Piece> movePiece) {
    // Rendering white pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (Piece::wPiecesArr[i]->getIsAlive() &&
          Piece::wPiecesArr[i] != movePiece) {
        Piece::wPiecesArr[i]->getTRect()->render(renderer);
      }
      if (Piece::wPArr[i]->getIsAlive() &&
          Piece::wPArr[i] != movePiece) {
        Piece::wPArr[i]->getTRect()->render(renderer);
      }
    }

    // Rendering black pieces
    for (int i = 0; i < CHESS_SIDE; i++) {
      if (Piece::bPiecesArr[i]->getIsAlive() &&
          Piece::bPiecesArr[i] != movePiece) {
        Piece::bPiecesArr[i]->getTRect()->render(renderer);
      }
      if (Piece::bPArr[i]->getIsAlive() &&
          Piece::bPArr[i] != movePiece) {
        Piece::bPArr[i]->getTRect()->render(renderer);
      }
    }

    if (movePiece != NULL) {
      movePiece->getTRect()->render(renderer);
    }

}
void reset(SDL_Renderer *&renderer, int state[CHESS_SIDE][CHESS_SIDE], int startingState[CHESS_SIDE][CHESS_SIDE], bool *isWhiteTurn) {
  *isWhiteTurn = true;
  Piece::wPiecesArr.clear();
  Piece::wPArr.clear();
  Piece::bPiecesArr.clear();
  Piece::bPArr.clear();
  initPieces(renderer);
  for (int i = 0; i < CHESS_SIDE; i++) {
    for (int j = 0; j < CHESS_SIDE; j++) {
      state[i][j] = startingState[i][j];
    }
  }

}

bool isCheckmate(int state[CHESS_SIDE][CHESS_SIDE], bool isWhiteTurn) {
  if (isWhiteTurn) {
    for (int i = 0; i < Piece::wPArr.size(); i++) {
      if (!Piece::wPArr[i]->getIsAlive()) {
        continue;
      }
      vector<tuple<int, int>> validMoves = Piece::wPArr[i]->getValidSquares(state);
      // cout << validMoves.size() << " ";
      if (!validMoves.empty()) {
        return false;
      }
    }
    for (int i = 0; i < Piece::wPiecesArr.size(); i++) {
      if (!Piece::wPiecesArr[i]->getIsAlive()) {
        continue;
      }
      vector<tuple<int, int>> validMoves = Piece::wPiecesArr[i]->getValidSquares(state);
      // cout << validMoves.size() << " ";
      if (!validMoves.empty()) {
        return false;
      }
    }
    // cout << endl;
  }
  else {
    for (int i = 0; i < Piece::bPArr.size(); i++) {
      if (!Piece::bPArr[i]->getIsAlive()) {
        continue;
      }
      vector<tuple<int, int>> validMoves = Piece::bPArr[i]->getValidSquares(state);
      // cout << validMoves.size() << " ";
      if (!validMoves.empty()) {
        return false;
      }
    }
    for (int i = 0; i < Piece::bPiecesArr.size(); i++) {
      if (!Piece::bPiecesArr[i]->getIsAlive()) {
        continue;
      }
      vector<tuple<int, int>> validMoves = Piece::bPiecesArr[i]->getValidSquares(state);
      // cout << validMoves.size() << " ";
      if (!validMoves.empty()) {
        return false;
      }
    }
    // cout << endl;

  }
  // cout << "here\n";

  return true;
}
