#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "location.h"
#include <memory>

class Pawn: public Piece{
	bool firstMove = true;
	Location movementDirection;
	Location sideDirection;

	void checkCaptureMoves(const ChessBoard &board);
	void checkEnPassantMoves(const ChessBoard &board);
	void checkStandardMoves(const ChessBoard &board);
	void updateLegalMoves(const ChessBoard &board) override;	
	
	public:
	Pawn(Colour colour, Location direction);
	void setLocation(const Location &location) override;
	void setFirstMove(bool b);
};


#endif

