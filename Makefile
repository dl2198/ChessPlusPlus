OBJ = ChessMain.o ChessBoard.o Piece.o Pawn.o Rook.o Knight.o Bishop.o King.o Queen.o

EXE = chess

CXX = g++

CXXFLAGS = -Wall -g -Wextra -MMD

$(EXE):$(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)

.PHONY: clean
