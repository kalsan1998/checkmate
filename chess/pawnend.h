#ifndef PAWN_END_H
#define PAWN_END_H

#include "chessmove.h"
#include <memory>

class Piece;
struct Location;

class PawnEnd: public ChessMove{
	std::shared_ptr<Piece> pawn;

	public:
	PawnEnd(std::shared_ptr<Piece> pawn, Location end);
	PawnEnd(PawnEnd &&other) noexcept;
	PawnEnd &operator=(PawnEnd &&other) noexcept;
};


#endif 

