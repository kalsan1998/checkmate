#include "capture.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "chessboard.h"
#include <memory>
using namespace std;


Capture::Capture(shared_ptr<Piece> piece, shared_ptr<Piece> captured): ChessMove{piece, captured->getLocation()}, captured{captured}{
	vector<unique_ptr<const BoardEdit>> editSequence;
	editSequence.emplace_back(make_unique<const PieceRemove>(piece));
	editSequence.emplace_back(make_unique<const PieceRemove>(captured));
	editSequence.emplace_back(make_unique<const PieceAdd>(piece, captured->getLocation())); 

	setEditSequence(move(editSequence));
}

Capture::Capture(Capture &&other) noexcept: ChessMove(move(other)){}
Capture &Capture::operator=(Capture &&other) noexcept{
	ChessMove::operator=(move(other));
	return *this;
}

void Capture::execute(ChessBoard &board) const{
	ChessMove::execute(board);
	board.detachObserver(captured);
}

void Capture::executeReverse(ChessBoard &board) const{
	ChessMove::executeReverse(board);
	board.attachObserver(captured);
}
