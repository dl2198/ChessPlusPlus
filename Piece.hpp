//
// Piece.hpp Declaration of Piece class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//
#ifndef Piece_hpp
#define Piece_hpp

class ChessBoard;

// Abstract class representing a piece on the chessboard
// This class provides an interface through which the ChessBoard class
// interacts with its Pieces
// Each Piece contains validation for determining which moves are allowed
// according to its kind
class Piece {

 public:

  // Constructor for the class
  // @param theChessboard pointer to the chessboard the piece is on
  // @param theColour the colour of the piece
  // @param theName the name of the piece
  // Sets the pointer to the chessboard the piece is on,
  // the colour of the piece,
  // and its name
  Piece(ChessBoard* theChessboard, Colour theColour, std::string const theName);

  // Getter function to access the colour of the piece
  Colour getColour() const;

  // Getter function to access the name of the piece
  std::string getName() const;

  // Pure virtual function to validate a move
  // @param source the square where the piece is
  // @param destination the square where the piece is trying to be moved to
  // Each different kind of piece will override this function accordingly
  // returns true if the move is valid
  // false otherwise
  virtual bool isValidMove(std::string const source,
			   std::string const destination) = 0;

  // Pure virtual function to check whether the piece is unobstructed in
  // making the move
  // Each different kind of piece will override this funciton accordingly:
  // some pieces aren't bothered by obstacles
  // returns true if there are no obstacles
  // false otherwise
  virtual bool isUnobstructed() = 0;

  // Function to change the state of the piece after its first move
  // sets the member variable firstMove
  void hasMoved();

  // Getter function to access the firstMove variable
  bool isFirstMove();

  // Destructor for the class
  virtual ~Piece(){};

 protected:

  // Helper function to set data for easy use in other functions
  // @param source the square of the piece being moved
  // @param destination the square where the piece is being moved to
  // Sets s_file, s_rank, d_file, d_rank,
  // sourceName, sourceColour, destinationName, destinationColour
  void setData(std::string const source, std::string const destination);

  // Pointer to the chessboard the piece is on
  ChessBoard* const board;

  // The colour of the piece
  Colour const colour;

  // The name of the piece
  std::string const name;

  // Coordinates corresponding to source and destination (as above)
  // translated from strings to ints
  int s_file = 0, s_rank = 0, d_file = 0,  d_rank = 0;

  // Directions in which the piece moves
  // 1 represents up
  // -1 represent down
  int verticaldir = 1, horizontaldir = 1;

  // Variable to keep track of whether the piece has moved already or not
  bool firstMove = true;
};

#endif /* Piece_hpp */
