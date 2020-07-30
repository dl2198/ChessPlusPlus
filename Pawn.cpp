//
// Pawn.cpp Implementation of Pawn class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#include"ChessBoard.h"
#include"Pawn.hpp"

Pawn::Pawn(ChessBoard* theChessboard, Colour theColour):
  Piece(theChessboard, theColour, "Pawn")
{
  setDirection();
}

void Pawn::setDirection()
{
  verticaldir = (colour == WHITE ? 1 : -1);
}

bool Pawn::isValidMove(std::string const source, std::string const destination)
{
  setData(source, destination);

  if (firstMove) {
    if (d_rank == s_rank + 2*verticaldir && d_file == s_file) {
      if (isUnobstructed()) {
	return true;
      }
    }
  }

  if (d_rank == s_rank + verticaldir && d_file == s_file) {
    if (isUnobstructed()) {
      return true;
    }
  }

  if (d_rank == s_rank + verticaldir) {
    if (d_file == s_file + verticaldir || d_file == s_file - verticaldir) {
      if (!isUnobstructed()) {
	  return true;
      }
    }
  }

  return false;
}

bool Pawn::isUnobstructed()
{
  if (d_rank == s_rank + 2*verticaldir && d_file == s_file) {
    if (board->getPiece(s_rank + verticaldir, d_file)
	|| board->getPiece(d_rank, d_file)) {
      return false;
    }
  }

  if (d_rank == s_rank + verticaldir) {
    if (board->getPiece(d_rank, d_file)) {
      return false;
    }
  }

  return true;;
}
