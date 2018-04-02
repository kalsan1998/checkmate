#ifndef KING_H
#define KING_H

#include "piece.h"
#include <vector>
#include <string>

class King: public Piece{
	void checkCastlingMoves(ChessBoard &board);	
	void checkStandardMoves(ChessBoard &board);

	void updateLegalMoves(ChessBoard &board) override;

	std::vector<Location> moveableLocation;
	
	public:
	King(Colour colour, std::string displaySymbol);
	void notify(ChessBoard &board) override;
	
	//this is a special notify because the king's possible
	//moves depends on the other pieces possible moves, so it must
	//be analyzed last
	void kingNotify(ChessBoard &board);

};


#endif
