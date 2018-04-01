#include "rook.h"
#include <vector>
#include "colour.h"
#include "piecetype.h"
#include "location.h"
using namespace std;

Rook::Rook(Colour colour): 
	MobilePiece{PieceType::ROOK, colour, 5, false, true,{{1,0},{0,1},{-1,0},{0,-1}}} {}


