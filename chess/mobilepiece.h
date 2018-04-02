#ifndef MOBILE_PIECE_H
#define MOBILE_PIECE_H

#include "piece.h"
#include <vector>
#include <string>
#include "location.h"

class MobilePiece: public Piece{
	std::vector<Location> directions;

	//checkRegularMoves checks all moves going along the line that
	//the piece is moveable until it goes out of bounds or runs into another
	//piece. It adds the corresponding move/capture to legalMoves while doing so
	void checkRegularMoves(ChessBoard &board);

	void updateLegalMoves(ChessBoard &board) override;

	public:
	MobilePiece(PieceType type, Colour colour, std::string displaySymbol, int value, bool isDiag, bool isStraight, std::vector<Location> directions);
};

#endif
