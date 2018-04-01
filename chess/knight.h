#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "location.h"
#include <memory>
#include <vector>

class Knight: public Piece{
	void checkAllMoves(ChessBoard &board);
	void updateLegalMoves(ChessBoard &board) override;	
	
	public:
	Knight(Colour colour);
};


#endif


