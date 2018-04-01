#include "queen.h"
#include <vector>
#include "colour.h"
#include "piecetype.h"
#include "location.h"
using namespace std;

Queen::Queen(Colour colour): MobilePiece{PieceType::QUEEN, colour, 9, true, true,
	{{1,1},{1,-1},{1,0},{-1,1},{-1,-1},{-1,0},{0,1},{0,-1}}} {}

