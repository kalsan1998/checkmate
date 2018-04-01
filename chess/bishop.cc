#include "bishop.h"
#include <vector>
#include "colour.h"
#include "piecetype.h"
#include "location.h"
using namespace std;

Bishop::Bishop(Colour colour): 
	MobilePiece{PieceType::BISHOP, colour, 3, true, false,{{1,-1},{-1,1},{1,1},{-1,-1}}} {}


