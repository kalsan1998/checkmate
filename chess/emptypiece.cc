#include "emptypiece.cc"
#include "location.h"
#include "colour.h"
using namespace std;

EmptyPiece::EmptyPiece(): Piece{PieceType::EMPTY_PIECE, Colour::NO_COLOUR, 0, false, false}{}
