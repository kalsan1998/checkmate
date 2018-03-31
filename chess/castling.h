#ifndef CASTLING_H
#define CASTLING_H

#include "chessmove.h"
#include <memory>

class King;
class Rook;
struct Location;

class Castling: public ChessMove{
	std::shared_ptr<Rook> rook;

	public:
	Castling(std::shared_ptr<King> king, std::shared_ptr<Rook> rook, Location kingEnd, Location rookEnd);
	Castling(Castling &&other) noexcept;
	Castling &operator=(Castling &&other) noexcept;

	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &board) const override;

}


#endif 
