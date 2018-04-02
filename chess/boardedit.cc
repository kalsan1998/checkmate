#include "boardedit.h"
#include "piece.h"
#include <memory>
using namespace std;

BoardEdit::~BoardEdit() {
}

BoardEdit::BoardEdit(shared_ptr<Piece> piece): pieceAffected{piece}{}
BoardEdit &BoardEdit::operator=(BoardEdit &&other) noexcept{;
	swap(pieceAffected, other.pieceAffected);
	return *this;
}
BoardEdit::BoardEdit(BoardEdit &&other) noexcept: pieceAffected{other.pieceAffected}{}
bool BoardEdit::operator==(const BoardEdit &edit) const{
	return (*pieceAffected) == (*edit.pieceAffected);
}

bool BoardEdit::operator!=(const BoardEdit &edit) const{
	return !(operator==(edit));
}


