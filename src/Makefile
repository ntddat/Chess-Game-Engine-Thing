CC = g++
LIB = -lSDL2 -lSDL2_ttf

SRC = chess_game.cpp pawn.cpp knight.cpp bishop.cpp rook.cpp queen.cpp king.cpp piece.cpp textured_rect.cpp text_rect.cpp
OBJ = $(SRC:.cpp=.o)

EXE = chess_game

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ) $(EXE)
