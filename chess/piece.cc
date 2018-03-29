#include "piece.h"
using namespace std;

Piece::Piece(PieceType type, Colour colour, int value): type{type}, colour{colour}, value{value}{}

Colour Piece::getColour const{
	return colour;
}

PieceType Piece::getType() const{
	return type;
}

int Piece::getValue() const{
	return value
}

Location Piece::getLocation() const{
	return location;
}

Location Piece::setLocation(Location otherLocation) const{
	location = otherLocation;
}

void Piece::notify(Board &board) override{
	//add this pieces legal moves to the board's legal moves
	vector<shared_ptr<ChessMove>> boardLegalMoves = board.getLegalMoves(colour);
	vector<shared_ptr<ChessMove>> legalMoves = getLegalMoves();
	legalMoves.insert(legalMoves.end(), legalMoves.start(), legalMoves.end()); 
}

bool Piece::isBlockingCheck
