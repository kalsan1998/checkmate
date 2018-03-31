#include "pieceadd.h"
#include "pieceremove.h"
#include "chessboard.h"
#include "piece.h"
#include "emptypiece.h"
#include <vector>
#include <memory>
using namespace std;

PieceRemove::PieceRemove(shared_ptr<Piece> piece): BoardEdit{piece}{}

void PieceRemove::execute(ChessBoard &board) const{
	board.theBoard[pieceAffected->getLocation()] = make_shared<EmptyPiece>();
	vector<shared_ptr<const Piece>> &pieceVector = board.piecesMap[pieceAffected->getColour()][pieceAffected->getType()];
	for(auto it = pieceVector.begin(); it != pieceVector.end(); ++it){
		//find and remove the piece from the mapping
		if(*it == pieceAffected){
			pieceVector.erase(it);
			break;
		}
	}
}

void PieceRemove::executeReverse(ChessBoard &board) const{
	PieceAdd{pieceAffected->getLocation(), pieceAffected}.execute(board);
}

