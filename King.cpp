//
// King.cpp Implementation of King class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#include"ChessBoard.h"
#include"King.hpp"

King::King(ChessBoard* theChessboard, Colour theColour):
  Piece(theChessboard, theColour, "King") {}

bool King::isValidMove(std::string const source, std::string const destination)
{
  setData(source, destination);

  int f_diff = d_file - s_file;
  int r_diff = d_rank - s_rank;

  if (r_diff && !f_diff) {
    if (abs(r_diff) == 1) {
      if (isUnobstructed()) {
	return true;
      }
    }
  }

  if (!r_diff && f_diff) {
    if (abs(f_diff) == 1) {
      if (isUnobstructed()) {
	return true;
      }
    }
  }

  if (r_diff && f_diff) {
    if (abs(r_diff) == abs(f_diff)) {
      if (abs(r_diff) == 1) {
	if (isUnobstructed()) {
	  return true;
	}
      }
    }
  }

  return false;
}

bool King::isUnobstructed()
{
  return true;
}
