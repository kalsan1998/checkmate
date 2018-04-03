#ifndef PIECE_REMOVE_H
#define PIECE_REMOVE_H

#include "boardedit.h"
#include <memory>
#include "location.h"

class Piece;

class PieceRemove: public BoardEdit{
	Location location;
	public:
	PieceRemove(std::shared_ptr<Piece> piece, Location location);
	
	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &board) const override;
};

#endif

