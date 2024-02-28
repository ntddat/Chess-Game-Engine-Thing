CC = g++
LIB = -lSDL2

SRC = chess_game.cpp piece.cpp textured_rect.cpp
OBJ = $(SRC:.cpp=.o)

EXE = chess_game

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ) $(EXE)
