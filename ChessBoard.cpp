//
// ChessBoard.cpp Implementation of ChessBoard class
// This file is part of ChessPlusPlus
//
// Created by Davide Locatelli on Nov 18 2019
//

#include"ChessBoard.h"
#include"Piece.hpp"
#include"Rook.hpp"
#include"Knight.hpp"
#include"Bishop.hpp"
#include"Queen.hpp"
#include"King.hpp"
#include"Pawn.hpp"
#include <iostream>
#include <cmath> //for absolute value

ChessBoard::ChessBoard():
  state(START)
{
  resetBoard();
}

void ChessBoard::resetBoard()
{
  if (state == START) {
    initialiseBoard();
  }
  else {
    cleanBoard();
    initialiseBoard();
  }
  state = NEUTRAL;
  turn = WHITE;
  std::cout << "A new chess game is started!\n";

  board[0][0] = new Rook(this, WHITE);
  board[0][7] = new Rook(this, WHITE);
  board[0][1] = new Knight(this, WHITE);
  board[0][6] = new Knight(this, WHITE);
  board[0][2] = new Bishop(this, WHITE);
  board[0][5] = new Bishop(this, WHITE);
  board[0][3] = new Queen(this, WHITE);
  board[0][4] = new King(this, WHITE);
  for (int f = 0; f < FILES; f++) {
    board[1][f] = new Pawn(this, WHITE);
  }

  board[7][0] = new Rook(this, BLACK);
  board[7][7] = new Rook(this, BLACK);
  board[7][1] = new Knight(this, BLACK);
  board[7][6] = new Knight(this, BLACK);
  board[7][2] = new Bishop(this, BLACK);
  board[7][5] = new Bishop(this, BLACK);
  board[7][3] = new Queen(this, BLACK);
  board[7][4] = new King(this, BLACK);
  for (int f = 0; f < FILES; f++) {
    board[6][f] = new Pawn(this, BLACK);
  }
}

void ChessBoard::initialiseBoard()
{
  for (int r = 0; r < RANKS; r++) {
    for (int f = 0; f < FILES; f++) {
      board[r][f] = nullptr;
    }
  }
}

void ChessBoard::cleanBoard()
{
  for (int r = 0; r < RANKS; r++) {
    for (int f = 0; f < FILES; f++) {
      if (board[r][f] != nullptr) {
	delete board[r][f];
      }
    }
  }
}

void ChessBoard::submitMove(std::string const source,
			    std::string const destination)
{
  if (state == NEUTRAL) {

    if (isCastling(source, destination)) {
      makeCastling(source, destination);
      turn = (turn == WHITE ? BLACK : WHITE);
      return;
    }

    if (isLawfulMove(source, destination)) {
      std::cout << sourceColour << "'s " << sourceName << " moves from "
		<< source << " to " << destination;

      if (board[d_rank][d_file] != nullptr
	  && sourceColour != destinationColour) {
	delete board[d_rank][d_file];
	std::cout << " taking " << destinationColour
		  << "'s " << destinationName << '\n';
      }
      else {
	std::cout << '\n';
      }

      //make the move
      board[d_rank][d_file] = board[s_rank][s_file];
      board[s_rank][s_file] = nullptr;

      //signal the piece has moved
      board[d_rank][d_file]->hasMoved();

      //swap turns
      turn = (turn == WHITE ? BLACK : WHITE);

      std::string theColour = turn == WHITE ? "White" : "Black";

      if (isCheckmate()) {
	state = CHECKMATE;
	std::cout << theColour << " is in checkmate\n";
	return;
      }

      if (isStalemate()) {
	state = STALEMATE;
	std::cout << theColour << " is in stalemate. The game ends in a draw\n";
	return;
      }

      if (isCheck()) {
	std::cout << theColour << " is in check\n";
      }
    }
  }

  else {
    char answer;

    do {
      std::cerr << "The game is over."
		<< "Enter R to reset the board or C to continue: ";
      std::cin >> answer;
      std::cerr << '\n';
    } while (answer != 'R' && answer != 'r' && answer != 'C' && answer != 'c');

    if (answer == 'R' || answer == 'r') {
      resetBoard();
    }
  }
}

bool ChessBoard::isLawfulMove(std::string const source,
			      std::string const destination)
{
  setData(source, destination);

  if (!isValidPosition(source)) {
    std::cerr << source << " is not a valid source\n";
    return false;
  }

  if (!isValidPosition(destination)) {
    std::cerr << destination << " is not a valid destination\n";
    return false;
  }

  if (board[s_rank][s_file] == nullptr) {
    std::cerr << "There is no piece at position " << source << "!\n";
    return false;
  }

  if (turn == WHITE && sourceColour == "Black") {
    std::cerr << "It is not Black's turn to move!\n";
    return false;
  }

  if (turn == BLACK && sourceColour == "White") {
    std::cerr << "It is not White's turn to move!\n";
    return false;
  }

  if (board[d_rank][d_file] != nullptr && sourceColour == destinationColour) {
    std::cerr << sourceColour << "s cannot capture " << sourceColour << "s.\n";
    return false;
  }

  if (!board[s_rank][s_file]->isValidMove(source, destination)) {
    std::cerr << sourceColour << "'s " << sourceName
	      << " cannot move to " << destination << '\n';
    return false;
  }

  if (unsafeKing()) {
    return false;
  }

  return true;
}

void ChessBoard::setData(std::string const source,
			 std::string const destination)
{
  s_file = source[0] - 'A';
  s_rank = source[1] - '1';
  d_file = destination[0] - 'A';
  d_rank = destination[1] - '1';

  if (board[s_rank][s_file] != nullptr)
    {
      sourceName = board[s_rank][s_file]->getName();
      sourceColour = board[s_rank][s_file]->getColour() == WHITE ?
	"White" : "Black";
    }

  if (board[d_rank][d_file] != nullptr)
    {
      destinationName = board[d_rank][d_file]->getName();
      destinationColour = board[d_rank][d_file]->getColour() == WHITE ?
	"White": "Black";
    }
}

bool ChessBoard::isValidPosition(std::string const square)
{
  int field = square[0] - 'A';
  if (field < 0 || field > RANKS)
    {
      return false;
    }

  int rank = square[1] - '1';
  if (rank < 0 || rank > FILES)
    {
      return false;
    }

  return true;
}

bool ChessBoard::unsafeKing()
{
  std::string theColour = turn == WHITE ? "White" : "Black";

  Piece* temp = nullptr;
  if (board[d_rank][d_file] != nullptr) {
    temp = board[d_rank][d_file];
  }

  if (isCheck()) {
    //attempt the move
    board[d_rank][d_file] = board[s_rank][s_file];
    board[s_rank][s_file] = nullptr;
    //check if it saved the king
    if (isCheck()) {
      std::cerr << theColour << ", you must save your King!\n";
      //undo move
      board[s_rank][s_file] = board[d_rank][d_file];
      board[d_rank][d_file] = temp;
      return true;
    }
    //undo move
    board[s_rank][s_file] = board[d_rank][d_file];
    board[d_rank][d_file] = temp;
  }

  //attempt the move
  board[d_rank][d_file] = board[s_rank][s_file];
  board[s_rank][s_file] = nullptr;
  //check if it saved the king
  if (isCheck()) {
    std::cerr << theColour << ", you can't betray your King!\n";
    //undo move
    board[s_rank][s_file] = board[d_rank][d_file];
    board[d_rank][d_file] = temp;
    return true;
  }
  //undo move
  board[s_rank][s_file] = board[d_rank][d_file];
  board[d_rank][d_file] = temp;
  return false;
}

bool ChessBoard::isCheck()
{
  std::string kingSquare = findKingSquare();

  //for every piece of the opposite colour
  //try to kill the king
  for (int r = 0; r < RANKS; r++) {
    for (int f = 0; f < FILES; f++) {
      if (board[r][f] != nullptr) {
	if (board[r][f]->getColour() != turn) {
	  char sourceRank = (char) r + '1';
	  char sourceField = (char) f + 'A';
	  std::string sourceSquare = "";
	  sourceSquare += sourceField;
	  sourceSquare += sourceRank;
	  if (board[r][f]->isValidMove(sourceSquare, kingSquare)) {
	    return true;
	  }
	}
      }
    }
  }
  return false;
}
std::string ChessBoard::findKingSquare()
{
  for (int r = 0; r < RANKS; r++) {
    for (int f = 0; f < FILES; f++) {
      if (board[r][f] != nullptr) {
	if (board[r][f]->getColour() == turn) {
	  if (board[r][f]->getName() == "King") {
	    char rank = r + '1';
	    char field = f + 'A';
	    std::string kingSquare = "";
	    kingSquare += field;
	    kingSquare += rank;
	    return kingSquare;
	  }
	}
      }
    }
  }
  return "";
}

bool ChessBoard::isCheckmate()
{
  if (isCheck()) {
    for (int r = 0; r < RANKS; r++) {
      for (int f = 0; f < FILES; f++) {
	if (board[r][f] != nullptr) {
	  if (board[r][f]->getColour() == turn) {
	    char sourceRank = (char) r + '1';
	    char sourceField = (char) f + 'A';
	    std::string source = "";
	    source += sourceField;
	    source += sourceRank;
	    if (canSaveKing(source)) {
	      return false;
	    }
	  }
	}
      }
    }
    return true;
  }
  return false;
}

bool ChessBoard::canSaveKing(std::string source)
{
  for (int r1 = 0; r1 < RANKS; r1++) {
    for (int f1 = 0; f1 < FILES; f1++) {
      if (board[r1][f1] == nullptr || board[r1][f1]->getColour() != turn) {
	char destRank = (char) r1 + '1';
	char destField = (char) f1 + 'A';
	std::string destination = "";
	destination += destField;
	destination += destRank;
	int r = source[1] - '1';
	int f = source[0] - 'A';
	if (board[r][f]->isValidMove(source, destination)) {
	  Piece* temp = nullptr;
	  if (board[r1][f1] != nullptr) {
	    temp = board[r1][f1];
	  }
	  //attemp the move
	  board[r1][f1] = board[r][f];
	  board[r][f] = nullptr;
	  //check if it saved the king
	  if (!isCheck()) {
	    //undo move
	    board[r][f] = board[r1][f1];
	    board[r1][f1] = temp;
	    return true;
	  }
	  //undo move
	  board[r][f] = board[r1][f1];
	  board[r1][f1] = temp;
	}
      }
    }
  }
  return false;
}

bool ChessBoard::isStalemate()
{
  std::cerr.setstate(std::ios_base::failbit); //don't print error messages
  if (!isCheck()) {
    for (int r = 0; r < RANKS; r++) {
      for (int f = 0; f < FILES; f++) {
	if (board[r][f] != nullptr) {
	  if (board[r][f]->getColour() == turn) {
	    std::string sourceSquare = "";
	    char sourceRank = r + '1';
	    char sourceField = f + 'A';
	    sourceSquare += sourceField;
	    sourceSquare += sourceRank;
	    for (int r1 = 0; r1 < RANKS; r1++) {
	      for (int f1 = 0; f1 < FILES; f1++) {
		std::string destSquare = "";
		char destRank = r1 + '1';
		char destField = f1 + 'A';
		destSquare += destField;
		destSquare += destRank;
		if (isLawfulMove(sourceSquare, destSquare)) {
		  std::cerr.clear(); //reset error stream
		  return false;
		}
	      }
	    }
	  }
	}
      }
    }
    std::cerr.clear(); //reset to printing errors to cerr
    return true;
  }

  std::cerr.clear();
  return false;
}

bool ChessBoard::isCastling(std::string const source,
			    std::string const destination)
{
  if (source != "E1" && source != "E8") {
    return false;
  }

  setData(source, destination);

  //the left rook file
  int const LEFT_ROOK_F = 0;

  //the right rook file
  int const RIGHT_ROOK_F = 7;

  //assuming right castling:

  //the distance between source file and dest file for it to be castling
  int const CASTLING_DISTANCE = 2;

  //the intermediate step the King has to take to do castling
  int const CASTLING_STEP1 = 1;

  if (abs(d_file) - abs(s_file) == CASTLING_DISTANCE) {
    //assume right-castling
    int step1 = CASTLING_STEP1; //the King will step +1 file
    int step2 = CASTLING_DISTANCE; //the King will step +2 files
    int theRookFile = RIGHT_ROOK_F;
    //if it's left-castling
    if (d_file - s_file < 0) {
      step1 *= -1; //the King will step -1 file
      step2 *= -1; //the King will step -2 files
      theRookFile = LEFT_ROOK_F;
    }
    if (board[s_rank][s_file] != nullptr
	&& board[s_rank][theRookFile] != nullptr) {
      if (board[s_rank][s_file]->isFirstMove()) {
	if (board[s_rank][theRookFile]->isFirstMove()) {
	  if (board[s_rank][s_file+step1] == nullptr
	      && board[s_rank][s_file+step2] == nullptr) {
	    if (!isCheck()) {
	      //attempt the first step
	      board[s_rank][s_file+step1] = board[s_rank][s_file];
	      board[s_rank][s_file] = nullptr;
	      //check it does not put the king in danger
	      if (!isCheck()) {
		//attemp the second step
		board[s_rank][s_file+step2] = board[s_rank][s_file+step1];
		board[s_rank][s_file+step1] = nullptr;
		//check it does not put the king in danger
		if (!isCheck()) {
		  //undo the moves
		  board[s_rank][s_file] = board[s_rank][s_file+step2];
		  board[s_rank][s_file+step2] = nullptr;
		  return true;
		}
		else {
		  //undo the moves
		  board[s_rank][s_file] = board[s_rank][s_file+step2];
		  board[s_rank][s_file+step2] = nullptr;
		  std::cerr << "Invalid castling: "
			    << "King would go in check!\n";
		  return false;
		}
	      }
	      else {
		//undo the move
		board[s_rank][s_file] = board[s_rank][s_file+step1];
		board[s_rank][s_file+step1] = nullptr;
		std::cerr << "Invalid castling: King woulg go in check!\n";
		return false;
	      }
	    }
	    else {
	      std::cerr << "Invalid castling: King is in check!\n";
	      return false;
	    }
	  }
	  else {
	    std::cerr << "Invalid castling: there are pieces between"
		      << " King and Rook!\n";
	    return false;
	  }
	}
      }
    }
  }

  return false;

}

void ChessBoard::makeCastling(std::string const source,
			      std::string const destination)
{
  //the left rook file
  int const LEFT_ROOK_F = 0;

  //the right rook file
  int const RIGHT_ROOK_F = 7;

  //assuming right castling:

  //the number of steps the king has to make
  int const KING_DEST = 2;

  //the distance between king and rook at the end
  int const ROOK_DEST = -1;

  int kDest = KING_DEST; //the king will step +2 files
  int rDest = ROOK_DEST; //the rook will be -1 files away
  int theRookFile = RIGHT_ROOK_F;
  if (d_file - s_file < 0) {
    //assume right castling
    kDest *= -1; //the king will step -2 files
    rDest *= -1; //the rook will be +1 files away
    theRookFile = LEFT_ROOK_F;
  }

  //move the king
  board[s_rank][s_file+kDest] = board[s_rank][s_file];
  board[s_rank][s_file] = nullptr;

  //signal that the king has moved
  board[s_rank][s_file+kDest]->hasMoved();

  //move the rook
  board[s_rank][s_file+kDest+rDest] = board[s_rank][theRookFile];
  board[s_rank][theRookFile] = nullptr;

  //signal that the rook has moved
  board[s_rank][s_file+kDest+rDest]->hasMoved();

  std::string colour = (turn == WHITE ? "White" : "Black");
  std::string rookSource = "";
  char rookRank = s_rank + '1';
  char rookFile = theRookFile + 'A';
  rookSource += rookFile;
  rookSource += rookRank;
  std::string rookDest = "";
  char newRookFile = s_file+kDest+rDest + 'A';
  rookDest += newRookFile;
  rookDest += rookRank;

  //print a custom message
  std::cout << "Castling was successful!\nThe " << colour
	    << " King has moved from " << source << " to "
	    << destination << '\n'
	    << "The " << colour << " Rook has moved from "
	    << rookSource << " to " << rookDest << '\n';
}

Piece* ChessBoard::getPiece(int rank, int file) const
{
  return board[rank][file];
}

ChessBoard::~ChessBoard()
{
  cleanBoard();
}
