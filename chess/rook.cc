#include "rook.h"
#include <vector>
#include <string>
#include "colour.h"
#include "piecetype.h"
#include "location.h"
using namespace std;

Rook::Rook(Colour colour, string displaySymbol): 
	MobilePiece{PieceType::ROOK, colour, displaySymbol, 5, false, true,{{1,0},{0,1},{-1,0},{0,-1}}} {}


