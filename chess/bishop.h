#ifndef BISHOP_H
#define BISHOP_H

#include "mobilepiece.h"
#include <string>

class Bishop: public MobilePiece{
	public:
	Bishop(Colour colour, std::string displaySymbol);
};

#endif

