#include "pawnendcapture.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "chessboard.h"
#include <memory>
using namespace std;


PawnEndCapture::PawnEndCapture(shared_ptr<Piece> pawn, shared_ptr<Piece> captured):
	ChessMove{pawn, captured->getLocation()}, pawn{pawn}, captured{captured}{	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn, pawn->getLocation()));
	editSequence.emplace_back(make_unique<const PieceRemove>(captured, captured->getLocation()));

	setEditSequence(move(editSequence));
}
