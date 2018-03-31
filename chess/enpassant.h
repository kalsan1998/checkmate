#ifndef EN_PASSANT_H
#define EN_PASSANT_H

#include "chessmove.h"
#include <memory>

class Pawn;
class Location;

class EnPassant: public ChessMove{
	public:
	EnPassant(std::shared_ptr<Pawn> pawn1, std::shared_ptr<Pawn> pawn2, Location pawn1End);
	EnPassant(EnPassant &&other) noexcept;
	EnPassant &operator=(EnPassant &&other) noexcept;
};


#endif 
