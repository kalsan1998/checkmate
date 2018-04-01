#include "chessmove.h"
#include "boardedit.h"
#include "chessboard.h"
#include "piece.h"
using namespace std;

ChessMove::~ChessMove(){}

ChessMove::ChessMove(shared_ptr<Piece> pieceMoved, Location endLocation): 
	pieceMoved{pieceMoved}, startLocation{pieceMoved->getLocation()}, endLocation{endLocation}{}
ChessMove::ChessMove(ChessMove &&other) noexcept: editSequence{move(other.editSequence)}{}
ChessMove &ChessMove::operator=(ChessMove &&other) noexcept{
	swap(editSequence, other.editSequence);
	return *this;
}

Location ChessMove::getStartLocation() const{ return startLocation; }
Location ChessMove::getEndLocation() const{ return endLocation; }

void ChessMove::executeReverse(ChessBoard &board) const{
	for(auto it = editSequence.rbegin(); it != editSequence.rend(); ++it){
		(*it)->executeReverse(board);
	}
	--(pieceMoved->getMoveCount());
}

void ChessMove::execute(ChessBoard &board) const{
	for(auto it = editSequence.begin(); it != editSequence.end(); ++it){
		(*it)->execute(board);
	}
	++(pieceMoved->getMoveCount());
}

bool ChessMove::operator==(const ChessMove &move) const{
	const vector<unique_ptr<const BoardEdit>> &otherSeq = move.editSequence;
	if(otherSeq.size() != editSequence.size()) return false;
	for(size_t i = 0; i < editSequence.size(); ++i){
		if(*(editSequence[i]) != *(otherSeq[i])) return false;
	}
	return true;
}

bool ChessMove::operator!=(const ChessMove &move) const{
	return !(*this == move);
}

void ChessMove::setEditSequence(vector<unique_ptr<const BoardEdit>> &&sequence){
	editSequence = move(sequence);
}

