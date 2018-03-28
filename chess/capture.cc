#include "standardmove.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


StandardMove::StandardMove(shared_ptr<Piece> piece, shared_ptr<Piece> captured){
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplaceBack(make_unique<const PieceRemove>(piece));
	editSequence.emplaceBack(make_unique<const PieceRemove>(captured));
	editSequence.emplaceBack(make_unique<const PieceAdd>(piece, captured.getLocation())); 
	editSequence.emplaceBack(make_unique<const PieceAdd>(captured, piece.getLocation())); 

	setEditSequence(move(editSequence));
}

StandardMove::StandardMove(StandardMove &&other): ChessMove(other){}
StandardMove &StandardMove::operator=(StandardMove &&other){
	ChessMove::operator=(other);
}
