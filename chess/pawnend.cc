#include "pawnend.h"
#include "piece.h"
#include "pawn.h"
#include "chessboard.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


PawnEnd::PawnEnd(shared_ptr<Pawn> pawn, shared_ptr<Piece> newPiece, Location end): ChessMove{pawn}, pawn{pawn}, newPiece{newPiece}{	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn));
	editSequence.emplace_back(make_unique<const PieceAdd>(newPiece, end)); 

	setEditSequence(move(editSequence));
}

PawnEnd::PawnEnd(PawnEnd &&other) noexcept: ChessMove(move(other)){}
PawnEnd &PawnEnd::operator=(PawnEnd &&other) noexcept{
	ChessMove::operator=(move(other));
	return *this;
}

void PawnEnd::execute(ChessBoard &board) const{
	ChessMove::execute(board);
	newPiece->getMoveCount() = pawn->getMoveCount();
	board.detachObserver(pawn);
	board.attachObserver(newPiece);
}

void PawnEnd::executeReverse(ChessBoard &board) const{
	ChessMove::executeReverse(board);
	board.detachObserver(newPiece);
	board.attachObserver(pawn);
}
