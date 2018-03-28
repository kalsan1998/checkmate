#ifndef STD_MOVE_H
#define STD_MOVE_H

#include "chessmove.h"

class Piece;
class std::shared_ptr<Piece>;
struct Location;

class StandardMove: public ChessMove{
	public:
	StandardMove(std::shared_ptr<Piece> piece, Location end);
	StandardMove(StandardMove &&other) noexcept;
	StandardMove &operator=(StandardMove &&other) noexcept;
};


#endif 
