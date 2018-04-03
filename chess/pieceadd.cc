#include "pieceadd.h"
#include "pieceremove.h"
#include "chessboard.h"
#include "piece.h"
#include <vector>
#include <memory>
using namespace std;

PieceAdd::PieceAdd(shared_ptr<Piece> piece, Location location): BoardEdit{piece}, location{location}{}
void PieceAdd::execute(ChessBoard &board) const{
	if(board.isInBounds(location)){
		//clean up old piece
		shared_ptr<Piece> oldPiece = board.theBoard[location];
		PieceRemove{oldPiece, location}.execute(board);

		//add new piece
		board.theBoard[location] = pieceAffected;
		vector<shared_ptr<Piece>> &piecesVec = board.piecesMap[pieceAffected->getColour()][pieceAffected->getType()];
		piecesVec.emplace_back(pieceAffected);
		pieceAffected->setLocation(location);
	}
	//do nothing if out of bounds
}

void PieceAdd::executeReverse(ChessBoard &board) const{
	PieceRemove{pieceAffected, location}.execute(board);
}
