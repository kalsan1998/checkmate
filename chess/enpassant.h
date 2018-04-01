#ifndef EN_PASSANT_H
#define EN_PASSANT_H

#include "chessmove.h"
#include <memory>

class Piece;
class Location;

class EnPassant: public ChessMove{
	std::shared_ptr<Piece> captured;

	public:
	EnPassant(std::shared_ptr<Piece> pawn1, std::shared_ptr<Piece> pawn2, Location pawn1End);
	EnPassant(EnPassant &&other) noexcept;
	EnPassant &operator=(EnPassant &&other) noexcept;

	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &board) const override;

};


#endif 
