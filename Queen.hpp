//
// Queen.hpp Declaration of Queen class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//
#ifndef Queen_hpp
#define Queen_hpp

#include"Piece.hpp"

// Class representing a Queen, derived from Piece
// This class contains validation functions for moves intended for queens
class Queen : public Piece {

 public:

  // Constructor for the class
  // @param theChessboard pointer to the chessboard the piece is on
  // @param theColour the colour of the piece
  // calls the base class initializer
  Queen(ChessBoard* theChessboard, Colour theColour);

  // Function to validate a move
  // @param source the square where the piece is
  // @param destination the square where the piece is trying to be moved to
  // returns true if the move is valid
  // false otherwise
  virtual bool isValidMove(std::string const source,
			   std::string const destination) override;

  // Function to check whether the piece is unobstructed in
  // making the move
  // returns true if there are no obstacles
  // false otherwise
  virtual bool isUnobstructed() override;

};

#endif /*Queen_hpp*/
