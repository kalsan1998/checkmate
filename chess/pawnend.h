#ifndef PAWN_END_H
#define PAWN_END_H

#include "chessmove.h"

class Piece;
class Pawn;
class std::shared_ptr<Piece>;
class std::shared_ptr<Pawn>;
struct Location;

class PawnEnd: public ChessMove{
	public:
	PawnEnd(std::shared_ptr<Pawn> pawn, std::shared_ptr<Piece> newPiece, Location end);
	PawnEnd(PawnEnd &&other) noexcept;
	PawnEnd &operator=(PawnEnd &&other) noexcept;
};


#endif 

