#ifndef PLAYER_H
#define PLAYER_H

#include "colour.h"

class ChessBoard;

class Player{
	Colour colour;

	protected:
	bool isPawnPromotion(ChessBoard &board) const;

	public:
	virtual ~Player(){}
	Player(Colour colour);
	virtual void play(ChessBoard &board) const = 0;
	Colour getColour() const;
};

#endif

