#ifndef PIECE_ADD_H
#define PIECE_ADD_H

#include "boardedit.h"
#include "location.h"
#include <memory>

class Piece;

class PieceAdd: public BoardEdit{
	Location location;
	public:
	PieceAdd(std::shared_ptr<Piece> piece, Location location);
	
	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &board) const override;
};

#endif
