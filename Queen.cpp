//
// Queen.cpp Implementation of Queen class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#include"ChessBoard.h"
#include"Queen.hpp"

Queen::Queen(ChessBoard* theChessboard, Colour theColour):
  Piece(theChessboard, theColour, "Queen") {}

bool Queen::isValidMove(std::string const source, std::string const destination)
{
  setData(source, destination);

  int f_diff = d_file - s_file;
  int r_diff = d_rank - s_rank;

  if (r_diff && f_diff) {
    if (abs(r_diff) == abs(f_diff)) {
      if (isUnobstructed()) {
	return true;
      }
    }
  }

  if (r_diff && !f_diff) {
    if (isUnobstructed()) {
      return true;
    }
  }

  if (!r_diff && f_diff) {
    if (isUnobstructed()) {
      return true;
    }
  }

  return false;
}

bool Queen::isUnobstructed()
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

  if (r_diff && f_diff) {
    for (int i = 1; i < abs(r_diff); i++) {
      if (board->getPiece(s_rank + verticaldir*i, s_file + horizontaldir*i)) {
	return false;
      }
    }
  }

  if (r_diff && !f_diff) {
    for (int i = 1; i < abs(r_diff); i++) {
      if (board->getPiece(s_rank+(i*verticaldir), s_file)) {
	return false;
      }
    }
  }

  if (!r_diff && f_diff) {
    for (int i = 1; i < abs(f_diff); i++) {
      if (board->getPiece(s_rank, s_file+(i*horizontaldir))) {
	return false;
      }
    }
  }

  return true;
}

