//
// ChessBoard.h Declaration of ChessBoard class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#ifndef ChessBoard_h
#define ChessBoard_h

#include <string>

// The colours for the two players
enum Colour {WHITE, BLACK};

// Forward declaration of the Piece class
class Piece;

// Class representing a chessboard
// This class manages the match simulation
// and takes care of all the validation of the moves
class ChessBoard {

 public:

  // Constructor for the class
  // Initialises the chessboard
  ChessBoard();

  // Function to reset the chessboard
  // Does cleanup if necessary
  // Creates and places pieces in initial position
  void resetBoard();

  // Function to make a move
  // Calls helper function for validation of the move
  // @param source the square of the piece being moved
  // @param destination the square where the piece is being moved to
  // Prints result of the move to standard output stream if move is lawful
  // Once the game is over, asks user whether to reset the board or continue
  void submitMove(std::string const source, std::string const destination);

  // Getter function to access a piece at a position
  // @param rank the rank (row) where the piece is
  // @param file the file (column) where the piece is
  Piece* getPiece(int rank, int file) const;

  // Destructor for the class
  // Does the cleanup
  virtual ~ChessBoard();

 private:

  // Helper function to initialise the chessboard
  // Sets all pointers to nullptr
  void initialiseBoard();

  // Helper function to clean the board
  // Deletes all pointers except nullptrs
  void cleanBoard();

  // Helper function to validate a move
  // @param source the square of the piece which is attempting to move
  // @param destination the desired destination
  // returns true if move is valid
  // false otherwise, printing to standard error stream an informative message
  bool isLawfulMove(std::string const source, std::string const destination);

  // Helper function to set data for easy use in other functions
  // @param source the square of the piece being moved
  // @param destination the square where the piece is being moved to
  // Sets s_file, s_rank, d_file, d_rank,
  // sourceName, sourceColour, destinationName, destinationColour
  void setData(std::string const source, std::string const destination);

  // Helper function to validate positions being passed to submitMove
  // such as source and destination (as above)
  // @param square the position being evaluated
  // returns true if the position is on the board
  // false otherwise
  bool isValidPosition(std::string const square);

  // Helper function to determine whether a move puts the King in check
  // returns true if King ends up being unsafe
  // false otherwise
  bool unsafeKing();

  // Function to determine whether the current player is in check
  // returns true if the player's King is in danger
  // false otherwise
  bool isCheck();

  // Helper function to locate the current player's King
  // returns a string containing the location of the King
  // (format FR where F is file and R is rank of the king)
  std::string findKingSquare();

  // Function to determine whether the current player is in checkmate
  // returns true if the current player is in check and has no moves
  // to save his King
  // false otherwise
  bool isCheckmate();

  // Helper function to determine whether any current player's piece
  // can save his King in danger
  // @param source the square of the piece attempting to save the King
  // returns true if there is a move that saves the King
  // false otherwise
  bool canSaveKing(std::string source);

  // Function to determine whether the current player is in stalemate
  // returns true if the current player has only moves left that
  // would put him in check
  // false otherwise
  bool isStalemate();

  // Function to determine whether the attempted move is a castling move
  // @param source the square where the piece is moving from
  // @param destination the square where the piece is being moved to
  // returns true if castling is being attempted
  // false otherwise
  bool isCastling(std::string const source, std::string const destination);

  // Function to submit a castling move
  // Moves the king towards the rook and the rook over the king
  void makeCastling(std::string const source, std::string const destination);

  // Constant representing the number of ranks on a board
  static int const RANKS = 8;

  // Constant representing the number of files on a board
  static int const FILES = 8;

  // Array of Piece pointers representing the board
  Piece* board[RANKS][FILES];

  // The state of the game
  enum {START, NEUTRAL, CHECKMATE, STALEMATE} state;

  // Variable to determine whose turn it is
  Colour turn = WHITE;

  // Coordinates corresponding to source and destination (as above)
  // translated from strings to ints
  int s_file = 0, s_rank = 0, d_file = 0, d_rank = 0;

  // Names and colours of pieces at source and destination (as above)
  std::string sourceName, sourceColour, destinationName, destinationColour;

};

#endif /* ChessBoard_h */
