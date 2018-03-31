#ifndef PAWN_DOUBLE_H
#define PAWN_DOUBLE_H

#include "chessmove.h"
#include <memory>

class Pawn;
struct Location;

class PawnDouble: public ChessMove{
	public:
	PawnDouble(std::shared_ptr<Pawn> pawn, Location end);
	PawnDouble(PawnDouble &&other) noexcept;
	PawnDouble &operator=(PawnDouble &&other) noexcept;
};
#endif
