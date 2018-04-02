#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "location.h"
#include <memory>
#include <vector>
#include <string>

class Knight: public Piece{
	void checkAllMoves(ChessBoard &board);
	void updateLegalMoves(ChessBoard &board) override;	
	
	public:
	Knight(Colour colour, std::string displaySymbol);
};


#endif


