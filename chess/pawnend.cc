#include "pawnend.h"
#include "piece.h"
#include "chessboard.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


PawnEnd::PawnEnd(shared_ptr<Piece> pawn, Location end): ChessMove{pawn, end}, pawn{pawn}{	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn, pawn->getLocation()));
	editSequence.emplace_back(make_unique<const PieceAdd>(pawn, end));
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn, end));
	setEditSequence(move(editSequence));
}

PawnEnd::PawnEnd(PawnEnd &&other) noexcept: ChessMove(move(other)){}
PawnEnd &PawnEnd::operator=(PawnEnd &&other) noexcept{
	ChessMove::operator=(move(other));
	return *this;
}
