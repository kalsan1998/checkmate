#ifndef EMPTY_PIECE_H
#define EMPTY_PIECE_H

#include "piece.h"

class ChessBoard;

class EmptyPiece: public Piece{
	void updateLegalMoves(const ChessBoard &board) override;

	public:
	EmptyPiece();
};

#endif
