#ifndef CAPTURE_H
#define CAPTURE_H

#include "chessmove.h"
#include <memory>

class Piece;

class Capture: public ChessMove{
	std::shared_ptr<Piece> captured;
	
	public:
	Capture(std::shared_ptr<Piece> piece, std::shared_ptr<Piece> captured);
	Capture(Capture &&other) noexcept;
	Capture &operator=(Capture &&other) noexcept;
/*TODO	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &board) const override;
*/};


#endif 
