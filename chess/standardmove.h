#ifndef STD_MOVE_H
#define STD_MOVE_H

#include "chessmove.h"

class Piece;
class shared_ptr<T>;
struct Location;

class StandardMove: public ChessMove{
	public:
	StandardMove(shared_ptr<Piece> piece, Location end);
	StandardMove(StandardMove &&other) noexcept;
	StandardMove &operator=(StandardMove &&other) noexcept;
}


#endif 
