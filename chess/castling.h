#ifndef CASTLING_H
#define CASTLING_H

#include "chessmove.h"

class King;
class Rook;
class shared_ptr<T>;
struct Location;

class Castling: public ChessMove{
	public:
	Castling(shared_ptr<King> king, shared_ptr<Rook>, Location kingEnd, Location rookEnd);
	Castling(Castling &&other) noexcept;
	Castling &operator=(Castling &&other) noexcept;
}


#endif 
