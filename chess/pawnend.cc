#include "standardmove.h"
#include "piece.h"
#include "pawn.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


StandardMove::StandardMove(shared_ptr<Pawn> pawn, shared_ptr<Piece> newPiece, Location end){	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplaceBack(make_unique<const PieceRemove>(pawn));
	editSequence.emplaceBack(make_unique<const PieceAdd>(newPiece, end)); 

	setEditSequence(move(editSequence));
}

StandardMove::StandardMove(StandardMove &&other): ChessMove(move(other)){}
StandardMove &StandardMove::operator=(StandardMove &&other){
	ChessMove::operator=(move(other));
	return *this;
}
