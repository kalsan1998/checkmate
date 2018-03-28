#include "enpassant.h"
#include "location.h"
#include "pawn.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;

EnPassant::EnPassant(shared_ptr<Pawn> pawn1, shared_ptr<Pawn> pawn2, Location pawn1End){
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplaceBack(make_unique<const PieceRemove>(pawn1)); 
	editSequence.emplaceBack(make_unique<const PieceRemove>(pawn2)); 
	editSequence.emplaceBack(make_unique<const PieceAdd>(pawn1, pawn1End));

	setEditSequence(move(editSequence));
}

EnPassant::EnPassant(EnPassant &&other): ChessMove(move(other)){}
EnPassant &EnPassant::operator=(EnPassant &&other){
	ChessMove::operator=(move(other));
	return *this;
}
