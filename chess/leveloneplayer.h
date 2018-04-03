#ifndef LEVEL_ONE_PLAYER_H
#define LEVEL_ONE_PLAYER_H

#include "computerplayer.h"

class ChessBoard;

class LevelOnePlayer: public ComputerPlayer{	
	public:
	//randomly selects moves
	LevelOnePlayer(Colour colour);
	void play(ChessBoard &board) const override;
};

#endif

