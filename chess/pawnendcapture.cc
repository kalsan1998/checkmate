#include "pawnendcapture.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "chessboard.h"
#include <memory>
using namespace std;


PawnEndCapture::PawnEndCapture(shared_ptr<Piece> pawn, shared_ptr<Piece> captured):
	ChessMove{pawn, captured->getLocation()}, pawn{pawn}, captured{captured}{	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn));
	editSequence.emplace_back(make_unique<const PieceRemove>(captured));

	setEditSequence(move(editSequence));
}

void PawnEndCapture::execute(ChessBoard &board) const{
	ChessMove::execute(board);
	//update move count for the new piece
	board.detachObserver(pawn);
	board.detachObserver(captured);
}

void PawnEndCapture::executeReverse(ChessBoard &board) const{
	ChessMove::executeReverse(board);
	board.attachObserver(pawn);
	board.attachObserver(captured);
}

