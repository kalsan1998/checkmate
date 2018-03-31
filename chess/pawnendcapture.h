#ifndef PAWN_END_CAPTURE_H
#define PAWN_END_CAPTURE_H

#include "chessmove.h"
#include <memory>

class Piece;
class Pawn;
struct Location;

class PawnEndCapture: public ChessMove{
	public:
	PawnEndCapture(std::shared_ptr<Pawn> pawn, std::shared_ptr<Piece> captured, std::shared_ptr<Piece> newPiece, Location end);
};

#endif

