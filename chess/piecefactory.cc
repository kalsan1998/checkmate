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
#include <sstream>
using namespace std;

PieceFactory::~PieceFactory(){}

shared_ptr<Piece> PieceFactory::generatePiece(char c){
	ostringstream oss;
	oss << c;
	string symbol = oss.str();
	Colour colour = Colour::WHITE;
	if(c > 'Z'){
		colour = Colour::BLACK;
		c -= 32;
	}
	if(c == 'P'){
		if(colour == Colour::BLACK){
			Location dir{0, -1};
			return make_shared<Pawn>(colour, symbol, dir);
		}
		Location dir{0,1};
		return make_shared<Pawn>(colour, symbol, dir);
	}
	if(c == 'K') return make_shared<King>(colour, symbol);
	if(c == 'Q') return make_shared<Queen>(colour, symbol);
	if(c == 'N') return make_shared<Knight>(colour, symbol);
	if(c == 'B') return make_shared<Bishop>(colour, symbol);
	if(c == 'R') return make_shared<Rook>(colour, symbol);
	
	//return empty piece if anything else
	return make_shared<EmptyPiece>();
}
