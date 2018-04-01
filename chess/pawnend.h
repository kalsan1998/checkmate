#ifndef PAWN_END_H
#define PAWN_END_H

#include "chessmove.h"
#include <memory>

class Piece;
class Pawn;
struct Location;

class PawnEnd: public ChessMove{
	std::shared_ptr<Pawn> pawn;
	std::shared_ptr<Piece> newPiece;

	public:
	PawnEnd(std::shared_ptr<Pawn> pawn, std::shared_ptr<Piece> newPiece, Location end);
	PawnEnd(PawnEnd &&other) noexcept;
	PawnEnd &operator=(PawnEnd &&other) noexcept;

	void execute(ChessBoard &board) const;
	void executeReverse(ChessBoard &board) const;
};


#endif 

