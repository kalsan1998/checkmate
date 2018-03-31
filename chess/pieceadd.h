#ifndef PIECE_ADD_H
#define PIECE_ADD_H

#include "boardedit.h"
#include "location.h"
#include <memory>

class Piece;

class PieceAdd: public BoardEdit{
	Location location;
	public:
	PieceAdd(const Location &location, std::shared_ptr<Piece> piece);
	
	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &board) const override;
};

#endif
