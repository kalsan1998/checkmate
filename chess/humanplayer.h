#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"
#include <iostream>

class ChessBoard;

class HumanPlayer: public Player{
	std::istream &in;

	public:
	HumanPlayer(Colour colour, std::istream &in);
	void play(ChessBoard &board) const override;
};

#endif

