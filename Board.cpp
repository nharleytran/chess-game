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

  //Copy Constructor
  Board::Board(const Board& rhs){
    *this = rhs;
  }

  // = operator overload
  Board & Board:: operator=(const Board& rhs){
  // Maybe need an if
    for (std::map<Position, Piece*>::const_iterator it = this->occ.begin();
	    it != this->occ.end();
	    it++)
    {
      Piece* temp = it->second;
      delete temp; 
    }
  for (std::map<Position, Piece*>::const_iterator it = rhs.occ.begin();
	 it != rhs.occ.end();
	 it++){
     this->occ[it->first] = it->second;
   }
    return *this;
  }

  // Destructor
  Board :: ~Board(){
    for (std::map<Position, Piece*>::const_iterator it = this->occ.begin();
	    it != this->occ.end();
	    it++)
    {
      Piece* temp = it->second;
      delete temp; 
    }
  }

  // char Board::get_piece_type(const Position& position) {
  //   if (occ.find(position) == occ.end()) {
  //     return '-';
  //   }
  //   else {
  //     return (*occ.at(position)).to_ascii();
  //   }
  // }

  Position Board::get_king(const bool white) const {
    Position x;
    if (white) {
      for (std::map<Position, Piece*>::const_iterator it = occ.begin();
	      it != occ.end();
	      it++) {
        if ((*it->second).to_ascii() == 'K') {
          x= it->first;
        }
      } 
    }
    else {
      for (std::map<Position, Piece*>::const_iterator it = occ.begin();
	      it != occ.end();
	      it++) {
        if ((*it->second).to_ascii() == 'k') {
          x= it->first;
        }
      } 
    }
    return x;
  }

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

  void Board::erase_piece(const Position& position) {
    delete occ.at(position);
    occ.erase(position);
  }

  void Board::move_piece(const Position& start, const Position& end){
    erase_piece(end);
    add_piece(end, occ.at(start)->to_ascii());
    erase_piece(start);
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
