#ifndef CAPTURE_H
#define CAPTURE_H

#include "chessmove.h"
#include <memory>

class Piece;

class Capture: public ChessMove{
	public:
	Capture(std::shared_ptr<Piece> piece, std::shared_ptr<Piece> captured);
	Capture(Capture &&other) noexcept;
	Capture &operator=(Capture &&other) noexcept;
};


#endif 
