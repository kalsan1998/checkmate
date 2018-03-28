#include "pieceadd.h"
#include "pieceremove.h"
#include "piece.h"
#include <stdlib>
using namespace std;

PieceAdd::PiecAdd(Location location, shared_ptr<Piece> piece): BoardEdit{piece}, location{location}{}

void PieceAdd::execute(ChessBoard &board) const{
	if(board.isInBounds(location)){
		board.theBoard[location] = pieceAffected;
		board.piecesMap[pieceAffected.getColour()][pieceAffected.getType()].emplace_back(pieceAffected);.
		pieceAffected.setLocation(location);
	}
	//do nothing if out of bounds
}

void PieceAdd::executeReverse(ChessBoard &board) const{
	PieceRemove{pieceAffected}.execute();
}
