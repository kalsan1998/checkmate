#ifndef PIECE_REMOVE_H
#define PIECE_REMOVE_H

#include "boardedit.h"
#include "location.h"
#include <memory>

class Piece;

class PieceRemove: public BoardEdit{
	Location location;
	public:
	PieceRemove(std::shared_ptr<Piece> piece);
	
	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &board) const override;
};

#endif

