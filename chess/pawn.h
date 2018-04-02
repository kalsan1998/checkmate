#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "location.h"
#include <vector>

class Pawn: public Piece{
	Location movementDirection;
	Location sideDirection;

	void checkCaptureMoves(ChessBoard &board);
	void checkEnPassantMoves(ChessBoard &board);
	void checkStandardMoves(ChessBoard &board);
	void updateLegalMoves(ChessBoard &board) override;	
	
	public:
	Pawn(Colour colour, Location direction);
};


#endif

