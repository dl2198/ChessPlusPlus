//
// King.hpp Declaration of King class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//
#ifndef King_hpp
#define King_hpp

#include"Piece.hpp"

// Class representing a King, derived from Piece
// This class contains validation functions for moves intended for kings
class King : public Piece {

 public:

  // Constructor for the class
  // @param theChessboard pointer to the chessboard the piece is on
  // @param theColour the colour of the piece
  // calls the base class initializer
  King(ChessBoard* theChessboard, Colour theColour);

  // Function to validate a move
  // @param source the square where the piece is
  // @param destination the square where the piece is trying to be moved to
  // returns true if the move is valid
  // false otherwise
  virtual bool isValidMove(std::string const source,
			   std::string const destination) override;

  // Function to check whether the piece is unobstructed in
  // making the move
  // returns true always as the King is always unobstructed
  virtual bool isUnobstructed() override;

};

#endif /*King_hpp*/
