#include "boardedit.h"
using namespace std;

BoardEdit::~BoardEdit() {}

BoardEdit::BoardEdit(shared_ptr<Piece> piece): pieceAffected{piece}{}
BoardEdit &operator=(BoardEdit &&other){
	BoardEdit tmp{other};
	swap(pieceAffected, tmp.pieceAffected);
	return *this;
}
BoardEdit::BoardEdit(BoardEdit &&other): pieceAffected{other.pieceAffected}{}
bool BoardEdit::operator==(BoardEdit &edit) const{
	return pieceAffected == edit.pieceAffected;
}

bool BoardEdit::operator!=(BoardEdit &edit) const{
	return pieceAffected != edit.pieceAffected;
}


