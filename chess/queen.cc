#include "queen.h"
#include <vector>
#include "colour.h"
#include "piecetype.h"
#include "location.h"
#include <string>
using namespace std;

Queen::Queen(Colour colour, string displaySymbol): MobilePiece{PieceType::QUEEN, colour, displaySymbol, 9, true, true,
	{{1,1},{1,-1},{1,0},{-1,1},{-1,-1},{-1,0},{0,1},{0,-1}}} {}

