#include "castling.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include <memory>
using namespace std;


Castling::Castling(shared_ptr<Piece> king, shared_ptr<Piece> rook, Location kingEnd, Location rookEnd): ChessMove{king, kingEnd}, rook{rook}{	
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(king, king->getLocation()));
	editSequence.emplace_back(make_unique<const PieceRemove>(rook, rook->getLocation()));
	editSequence.emplace_back(make_unique<const PieceAdd>(king, kingEnd)); 
	editSequence.emplace_back(make_unique<const PieceAdd>(rook, rookEnd));

	setEditSequence(move(editSequence));
}

Castling::Castling(Castling &&other) noexcept: ChessMove(move(other)){}
Castling &Castling::operator=(Castling &&other) noexcept{
	ChessMove::operator=(move(other));
	return *this;
}

void Castling::execute(ChessBoard &board) const{
	ChessMove::execute(board);
	++(rook->getMoveCount());
}

void Castling::executeReverse(ChessBoard &board) const{
	ChessMove::executeReverse(board);
	--(rook->getMoveCount());
}
