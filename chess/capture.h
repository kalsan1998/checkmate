#ifndef CAPTURE_H
#define CAPTURE_H

#include "chessmove.h"

class Piece;
class shared_ptr<T>;
struct Location;

class Capture: public ChessMove{
	public:
	Capture(shared_ptr<Piece> piece1, shared_ptr<Piece> captured);
	Capture(Capture &&other) noexcept;
	Capture &operator=(Capture &&other) noexcept;
}


#endif 
