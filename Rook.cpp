//
// Rook.cpp Implementation of Rook class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#include"ChessBoard.h"
#include"Rook.hpp"

Rook::Rook(ChessBoard* theChessboard, Colour theColour):
  Piece(theChessboard, theColour, "Rook") {}

bool Rook::isValidMove(std::string const source, std::string const destination)
{
  setData(source, destination);

  if (s_rank == d_rank && s_file != d_file) {
    if (isUnobstructed()) {
      return true;
    }
  }

  if (s_rank != d_rank && s_file == d_file) {
    if (isUnobstructed()) {
      return true;
    }
  }

  return false;
}

bool Rook::isUnobstructed()
{
  int r_diff = d_rank - s_rank;
  int f_diff = d_file - s_file;

  verticaldir = 1;
  if (r_diff < 0) {
    verticaldir = -1;
  }

  horizontaldir = 1;
  if (f_diff < 0) {
    horizontaldir = -1;
  }

  if (s_rank == d_rank && s_file != d_file) {
    for (int i = 1; i < abs(f_diff); i++) {
      if (board->getPiece(s_rank, s_file+(i*horizontaldir))) {
	return false;
      }
    }
  }

  if (s_rank != d_rank && s_file == d_file) {
    for (int i = 1; i < abs(r_diff); i++) {
      if (board->getPiece(s_rank+(i*verticaldir), s_file)) {
	return false;
      }
    }
  }

  return true;
}
