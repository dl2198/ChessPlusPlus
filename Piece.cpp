//
// Piece.cpp Implementation of Piece class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#include"ChessBoard.h"
#include"Piece.hpp"

Piece::Piece(ChessBoard* theChessboard, Colour theColour, std::string theName):
  board(theChessboard), colour(theColour), name(theName) {}

Colour Piece::getColour() const
{
  return colour;
}

std::string Piece::getName() const
{
  return name;
}

void Piece::hasMoved()
{
  firstMove = false;
}

bool Piece::isFirstMove()
{
  return firstMove;
}

void Piece::setData(std::string const source, std::string const destination)
{
  s_file = source[0] - 'A';
  s_rank = source[1] - '1';
  d_file = destination[0] - 'A';
  d_rank = destination[1] - '1';
}
