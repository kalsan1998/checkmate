#include "chessmove.h"
#include "boardedit.h"
using namespace std;

ChessMove::~ChessMove(){}

void ChessMove::executeReverse(ChessBoard &board) const{
	for(auto it = editSequence.rbegin(); it != editSequence.rend(); ++it){
		(*it)->executeReverse(board);
	}
}

void ChessMove::execute(ChessBoard &board) const{
	for(auto it = editSequence.begin(); it != editSequence.end(); ++it){
		(*it)->execute(board);
	}
}

bool ChessMove::operator==(ChessMove &move){
	vector<shared_ptr<const BoardEdit>> &otherSeq = move.editSequence;
	if(otherSeq.size() != editSequence.size()) return false;
	for(int i = 0; i < editSequence.size(); ++i){
		if(*(editSequence[i]) != *(otherSeq[i])) return false;
	}
	return true;
}

bool ChessMove::operator!=(ChessMove &move){
	return !(*this == move);
}

ChessMove &ChessMove::operator=(ChessMove &&other){
	ChessMove tmp{move};
	swap(editSequence, tmp.editSequence);
	return *this;
}

void setEditSequence(vector<unique_ptr<const BoardEdit>> &&sequence){
	editSequence = sequence;
}

