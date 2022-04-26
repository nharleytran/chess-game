#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Board.h"

namespace Chess
{
	class Rook : public Piece {

	public:
    bool legal_move_shape(const Position& start, const Position& end) const override;

	// check for obstruction along movement path
	bool obstruction_check(const Position& start, const Position& end, const Board& board) const;

		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		char to_ascii() const override { return is_white() ? 'R' : 'r';	}
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		std::string to_unicode() const override { return is_white() ? "\u2656" : "\u265C"; }

	private:
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		Rook(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};
}
#endif // ROOK_H
