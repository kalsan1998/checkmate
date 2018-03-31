#ifndef KING_H
#define KING_H

#include "piece.h"

class King: public Piece{
	void checkCastlingMoves(const ChessBoard &board);	
	void checkStandardMoves(const ChessBoard &board);

	public:
	King(Colour colour);
	void notify(ChessBoard &board) override;
	
	//this is a special notify because the king's possible
	//moves depends on the other pieces possible moves, so it must
	//be analyzed last
	void kingNotify(ChessBoard &board);

};


#endif
