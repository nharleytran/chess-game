#include <cassert>
#include "Exceptions.h"
#include "Game.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	void Game::make_move(const Position& start, const Position& end) {
		//Make copy of the board
		
		//EXCEPTION: start position on board?
		if(!position_on_board(start)){
			throw Exception("start position is not on board");
		}
		//EXCEPTION: end position on board?
		if(!position_on_board(end)){
			throw Exception("end position is not on board");
		}
		//EXCEPTION: no piece at start position?
		if(board(start) == nullptr){
			throw Exception("no piece at start position");
		}
		//EXCEPTION: piece color and turn match?
		if ((board(start))->is_white() != is_white_turn){
			throw Exception("piece color and turn do not match");
		}

		//EXCEPTION: illegal move shape?
		if(!(board(start))->legal_move_shape(start,end)){
			throw Exception("illegal move shape");
		}
		//EXCEPTION: cannot capture own piece?
		if (board(end)!= nullptr){
			if (board(start)->is_white() == board(end)->is_white()){
				throw Exception("cannot capture own piece");
			}
		}

		//EXCEPTION: illegal capture shape?
		if (!(board(start)->legal_capture_shape(start,end))){
			throw Exception("illegal capture shape");
		}
		//EXCEPTION: path is not clear?
		if (!path_clear_check(start, end)){
			throw Exception("path is not clear");
		}

		//Move in actual board

		//EXCEPTION: move exposes check?

		//if does not pass exception, Actual board = copy board

	}

	bool Game::position_on_board(const Position& x){
		for(char r = '8'; r >= '1'; r--) {
      		for(char c = 'A'; c <= 'H'; c++) {
        		if(x.first == c && x.second == r){
					return true;}
			}
		}	
		return false;
	}

	bool Game::path_clear_check(const Position& start, const Position& end) const {
	
	int dx = end.first - start.first;
    int dy = end.second - start.second;

	// vertical movement
    if (dx == 0 && dy !=0) {
      if (dy > 0) {
        for (char row = start.second + 1; row < end.second; row++) {
          Position tmp = Position(start.first, row);
          if (board(tmp) != nullptr) {
            return false;
			}}
      	}else {
        for (char row = end.second + 1; row < start.second; row++) {
          Position tmp = Position(start.first, row);
          if (board(tmp) != nullptr) {
            return false;
			}}}}

    // horizontal movement
    if (dx != 0 && dy ==0) {
      if (dx > 0) {
        for (char col = start.first + 1; col < end.first; col++) {
          Position tmp = Position(col, start.second);
          if (board(tmp) != nullptr) {
            return false;
          	}}
      	}else {
        for (char col = end.first + 1; col < start.second; col++) {
          Position tmp = Position(col, start.second);
          if (board(tmp) != nullptr) {
            return false;
          	}}}}

	//diagonal movement
	if (dx == dy) {
		if (dx > 0){
			for (char i = '1', j ='A'; i < dx; i++, j++){
				Position tmp = Position(start.first+j, start.second+i);
				if (board(tmp)!= nullptr){
					return false;
					}}
		}else {
			for (char i = '1', j ='A'; i < dx; i++, j++){
				Position tmp = Position(end.first+j, end.second+i);
				if (board(tmp)!= nullptr){
					return false;
					}}}}
	return true;
	}


	bool Game::in_check(const bool& white) const{

		Position king_pos = board.get_king(white);
		for(char r = '8'; r >= '1'; r--) {
      		for(char c = 'A'; c <= 'H'; c++) {
        		Position tempo(c,r);
				//if there is a piece at tempo
				if (board(tempo)!= nullptr){
					//if that piece belong to the other team (different color)
					if(board(tempo)->is_white() != white){
						//if that piece has a legal move to capture king
						switch (board(tempo)->to_ascii()){
							case 'Q': case 'q': case 'R' : case 'r': case 'B': case 'b': case 'N': case 'n': 		//maybe account King
								if (path_clear_check(tempo,king_pos) &&
								board(tempo)->legal_move_shape(tempo, king_pos)){
									return true;
								}
								break;
							case 'P': case 'p':
								if (board(tempo)->legal_capture_shape(tempo,king_pos)){
									return true;
								}
								break;
							default:
								break;
						}
					}
				}
			}
		return false;
	}


	bool Game::in_mate(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return false;
	}


	bool Game::in_stalemate(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return false;
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
        return -1;
    }


      std::istream& operator>> (std::istream& is, Game& game) {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
