#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  const Piece* Board::operator()(const Position& position) const {
    if (occ.find(position) != occ.end())
      return occ.at(position);
    else
      return nullptr;
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {

  //invalid designator
    Piece* new_piece = create_piece(piece_designator);
    if (new_piece == nullptr) {
      throw Exception("invalid designator");
    }
  //invalid position
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        if(position.first == c && position.second == r){
          throw Exception("invalid position");
        }
      }
    }
    
  //position is occupied
    if (occ.find(position) != occ.end()) {
      throw Exception("position is occupied");
    }

  //create new piece at given position
    occ[position] = new_piece;
  }

  void Board::display() const {
    // TODO: edit to make output pretty
    std::cout << *this << "\n";
  }

  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin();
	 it != occ.end();
	 it++) {
      if (it->second) {
	switch (it->second->to_ascii()) {
	case 'K':
	  white_king_count++;
	  break;
	case 'k':
	  black_king_count++;
	  break;
	}
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }
}
