//
// Knight.cpp Implementation of Knight class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#include"ChessBoard.h"
#include"Knight.hpp"

Knight::Knight(ChessBoard* theChessboard, Colour theColour):
  Piece(theChessboard, theColour, "Knight") {}

bool Knight::isValidMove(std::string const source,
			 std::string const destination)
{
  setData(source, destination);

  if (d_rank == s_rank + 2 || d_rank == s_rank - 2) {
    if (d_file == s_file + 1 || d_file == s_file - 1) {
      if (isUnobstructed()) {
	return true;
      }
    }
  }

  if (d_file == s_file + 2 || d_file == s_file - 2) {
    if (d_rank == s_rank + 1 || d_rank == s_rank - 1) {
      if (isUnobstructed()) {
	return true;
      }
    }
  }

  return false;
}

bool Knight::isUnobstructed()
{
  return true;
}
