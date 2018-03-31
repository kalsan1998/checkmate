#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "location.h"
#include <memory>
#include <vector>

class Rook: public Piece{
	void chechAllMoves(const ChessBoard &board);
	void updateLegalMoves(const ChessBoard &board) override;

	public:
	Rook(Colour colour);
}

#endif
