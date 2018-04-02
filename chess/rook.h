#ifndef ROOK_H
#define ROOK_H

#include "mobilepiece.h"
#include <string>

class Rook: public MobilePiece{
	public:
	Rook(Colour colour, std::string displaySymbol);
};

#endif
