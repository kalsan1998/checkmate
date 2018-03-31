#include "castling.h"
#include "king.h"
#include "rook.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


Castling::Castling(shared_ptr<King> king, shared_ptr<Rook> rook, Location kingEnd, Location rookEnd){	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(king));
	editSequence.emplace_back(make_unique<const PieceRemove>(rook))
	editSequence.emplace_back(make_unique<const PieceAdd>(kingEnd, king)); 
	editSequence.emplace_back(make_unique<const PieceAdd>(rookEnd, rook));

	setEditSequence(move(editSequence));
}

Castling::Castling(Castling &&other): ChessMove(move(other)){}
Castling &Castling::operator=(Castling &&other){
	ChessMove::operator=(move(other));
	return *this;
}
