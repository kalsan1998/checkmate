#include "enpassant.h"
#include "location.h"
#include "pawn.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;

EnPassant::EnPassant(shared_ptr<Pawn> pawn1, shared_ptr<Pawn> pawn2, Location pawn1End): ChessMove{pawn1}, captured{pawn2}{
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn1)); 
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn2)); 
	editSequence.emplace_back(make_unique<const PieceAdd>(pawn1, pawn1End));

	setEditSequence(move(editSequence));
}

EnPassant::EnPassant(EnPassant &&other): ChessMove(move(other)){}
EnPassant &EnPassant::operator=(EnPassant &&other){
	ChessMove::operator=(move(other));
	return *this;
}

void EnPassant::execute(ChessBoard &board) const{
	ChessMove::execute(board);
	board.detach(captured);
}

void EnPassant::executeReverse(ChessBoard &board) const{
	ChessMove::executeReverse(board);
	board.attach(captured);
}
