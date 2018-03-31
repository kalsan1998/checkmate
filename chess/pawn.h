#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "location.h"
#include <memory>
#include <vector>

class Pawn: public Piece{
	Location movementDirection;
	Location sideDirection;

	std::vector<std::shared_ptr<Piece>> boardEndPieces; //possible pieces to end once reaching end of board

	void checkCaptureMoves(const ChessBoard &board);
	void checkEnPassantMoves(const ChessBoard &board);
	void checkStandardMoves(const ChessBoard &board);
	void updateLegalMoves(const ChessBoard &board) override;	
	
	public:
	Pawn(Colour colour, Location direction);
};


#endif

