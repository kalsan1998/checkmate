#include "standardmove.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


Capture::Capture(shared_ptr<Piece> piece, shared_ptr<Piece> captured){
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(piece));
	editSequence.emplace_back(make_unique<const PieceRemove>(captured));
	editSequence.emplace_back(make_unique<const PieceAdd>(piece, captured.getLocation())); 
	editSequence.emplace_back(make_unique<const PieceAdd>(captured, piece.getLocation())); 

	setEditSequence(move(editSequence));
}

Capture::Capture(Capture &&other): ChessMove(move(other)){}
Capture &Capture::operator=(Capture &&other){
	ChessMove::operator=(move(other));
	return *this;
}
