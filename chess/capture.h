#ifndef CAPTURE_H
#define CAPTURE_H

#include "chessmove.h"

class Piece;
class std::shared_ptr<Piece>;
struct Location;

class Capture: public ChessMove{
	public:
	Capture(std::shared_ptr<Piece> piece1, std::shared_ptr<Piece> captured);
	Capture(Capture &&other) noexcept;
	Capture &operator=(Capture &&other) noexcept;
};


#endif 
