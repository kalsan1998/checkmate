#include "pawndouble.h"
#include "pawn.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "location.h"
#include <memory>
using namespace std;

PawnDouble::PawnDouble(shared_ptr<Pawn> pawn, Location end): ChessMove{pawn}{
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn));
	editSequence.emplace_back(make_unique<const PieceAdd>(pawn, end)); 

	setEditSequence(move(editSequence));
}
	
