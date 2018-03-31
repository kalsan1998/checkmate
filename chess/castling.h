#ifndef CASTLING_H
#define CASTLING_H

#include "chessmove.h"

class King;
class Rook;
class std::shared_ptr<King>;
class std::shared_ptr<Rook>;
struct Location;

class Castling: public ChessMove{
	public:
	Castling(std::shared_ptr<King> king, std::shared_ptr<Rook> rook, Location kingEnd, Location rookEnd);
	Castling(Castling &&other) noexcept;
	Castling &operator=(Castling &&other) noexcept;
}


#endif 
