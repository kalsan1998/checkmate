#include "pawnend.h"
#include "piece.h"
#include "pawn.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


PawnEnd::PawnEnd(shared_ptr<Pawn> pawn, shared_ptr<Piece> newPiece, Location end){	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn));
	editSequence.emplace_back(make_unique<const PieceAdd>(newPiece, end)); 

	setEditSequence(move(editSequence));
}

PawnEnd::PawnEnd(PawnEnd &&other): ChessMove(move(other)){}
PawnEnd &PawnEnd::operator=(PawnEnd &&other){
	ChessMove::operator=(move(other));
	return *this;
}
