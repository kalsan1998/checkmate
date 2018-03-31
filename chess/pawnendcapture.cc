#include "pawnendcapture.h"
#include "piece.h"
#include "pawn.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


PawnEndCapture::PawnEndCapture(shared_ptr<Pawn> pawn, shared_ptr<Piece> captured, shared_ptr<Piece> newPiece){	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn));
	editSequence.emplace_back(make_unique<const PieceRemove>(captured));
	editSequence.emplace_back(make_unique<const PieceAdd>(newPiece, captured.getLocation())); 

	setEditSequence(move(editSequence));
}

