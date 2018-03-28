#include "pieceadd.h"
#include "pieceremove.h"
#include "piece.h"
#include "emptypiece.h"
#include <stdlib>
using namespace std;

PieceRemove::PiecAdd(shared_ptr<Piece> piece): BoardEdit{piece}{}

void PieceRemove::execute(ChessBoard &board) const{
	board.theBoard[pieceAffected.getLocation()] = make_shared<EmptyPiece>();
	vector<shared_ptr<Piece>> &pieceVector = board.piecesMap[pieceAffected.getColour()][pieceAffected.getType()];
	for(auto it = pieceVector.begin(); it != pieceVector.end(); ++it){
		//find and remove the piece from the mapping
		if(*it == pieceAffected){
			pieceVector.erase(it);
			break;
		}
	}
}

void PieceRemove::executeReverse(ChessBoard &board) const{
	PieceAdd{pieceAffected.getLocation(), pieceAffected}.execute();
}

