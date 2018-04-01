#include "piecefactory.h"
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "emptypiece.h"
#include "colour.h"
#include <memory>
using namespace std;

PieceFactory::~PieceFactory(){}

shared_ptr<Piece> PieceFactory::generatePiece(char c){
	Colour colour = Colour::WHITE;
	if(c > 'Z'){
		colour = Colour::BLACK;
		c -= 32;
	}
	if(c == 'P'){
		if(colour == Colour::BLACK){
			Location dir{-1, 0};
			return make_shared<Pawn>(colour,dir);
		}
		Location dir{1,0};
		return make_shared<Pawn>(colour, dir);
	}
	if(c == 'K') return make_shared<King>(colour);
	if(c == 'Q') return make_shared<Queen>(colour);
	if(c == 'N') return make_shared<Knight>(colour);
	if(c == 'B') return make_shared<Bishop>(colour);
	if(c == 'R') return make_shared<Rook>(colour);
	
	//return empty piece if anything else
	return make_shared<EmptyPiece>();
}
