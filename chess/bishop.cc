#include "bishop.h"
#include <vector>
#include "colour.h"
#include "piecetype.h"
#include "location.h"
#include <string>
using namespace std;

Bishop::Bishop(Colour colour, string displaySymbol): 
	MobilePiece{PieceType::BISHOP, colour, displaySymbol, 3, true, false,{{1,-1},{-1,1},{1,1},{-1,-1}}} {}


