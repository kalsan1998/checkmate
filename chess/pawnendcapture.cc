#include "pawnendcapture.h"
#include "piece.h"
#include "pawn.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "chessboard.h"
#include <memory>
using namespace std;


PawnEndCapture::PawnEndCapture(shared_ptr<Pawn> pawn, shared_ptr<Piece> captured, shared_ptr<Piece> newPiece):
	ChessMove{pawn}, pawn{pawn}, captured{captured}, newPiece{newPiece}{	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn));
	editSequence.emplace_back(make_unique<const PieceRemove>(captured));
	editSequence.emplace_back(make_unique<const PieceAdd>(newPiece, captured->getLocation())); 

	setEditSequence(move(editSequence));
}

void PawnEndCapture::execute(ChessBoard &board) const{
	ChessMove::execute(board);
	//update move count for the new piece
	newPiece->getMoveCount() = pawn->getMoveCount();
	board.detachObserver(pawn);
	board.detachObserver(captured);
	board.attachObserver(newPiece);
}

void PawnEndCapture::executeReverse(ChessBoard &board) const{
	ChessMove::executeReverse(board);
	board.attachObserver(pawn);
	board.attachObserver(captured);
	board.detachObserver(newPiece);
}

