#ifndef PAWN_END_CAPTURE_H
#define PAWN_END_CAPTURE_H

#include "chessmove.h"
#include <memory>

class Piece;
struct Location;

class PawnEndCapture: public ChessMove{
	std::shared_ptr<Piece> pawn;
	std::shared_ptr<Piece> captured;

	public:
	PawnEndCapture(std::shared_ptr<Piece> pawn, std::shared_ptr<Piece> captured);
	void execute(ChessBoard &board) const;
	void executeReverse(ChessBoard &board) const;
};

#endif

