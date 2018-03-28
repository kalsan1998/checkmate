#include "standardmove.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


StandardMove::StandardMove(shared_ptr<Piece> piece, Location end){	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplaceBack(make_unique<const PieceRemove>(piece));
	editSequence.emplaceBack(make_unique<const PieceAdd>(piece, end)); 

	setEditSequence(move(editSequence));
}

StandardMove::StandardMove(StandardMove &&other): ChessMove(other){}
StandardMove &StandardMove::operator=(StandardMove &&other){
	ChessMove::operator=(other);
}
