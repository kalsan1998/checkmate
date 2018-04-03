#include "enpassant.h"
#include "location.h"
#include "piece.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "chessboard.h"
#include <memory>
using namespace std;

EnPassant::EnPassant(shared_ptr<Piece> pawn1, shared_ptr<Piece> pawn2, Location pawn1End): ChessMove{pawn1, pawn1End}, captured{pawn2}{
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn1, pawn1->getLocation())); 
	editSequence.emplace_back(make_unique<const PieceRemove>(pawn2, pawn1End)); 
	editSequence.emplace_back(make_unique<const PieceAdd>(pawn1, pawn1End));

	setEditSequence(move(editSequence));
}

EnPassant::EnPassant(EnPassant &&other) noexcept: ChessMove(move(other)){}
EnPassant &EnPassant::operator=(EnPassant &&other) noexcept{
	ChessMove::operator=(move(other));
	return *this;
}
