#ifndef QUEEN_H
#define QUEEN_H

#include "mobilepiece.h"
#include <string>

class Queen: public MobilePiece{
	public:
	Queen(Colour colour, std::string displaySymbol);
};

#endif

