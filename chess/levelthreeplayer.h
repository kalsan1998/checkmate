#ifndef LEVEL_THREE_PLAYER_H
#define LEVEL_THREE_PLAYER_H

#include "computerplayer.h"
#include <memory>
#include "leveltwoplayer.h"
#include "leveloneplayer.h"

class ChessBoard;

class LevelThreePlayer: public ComputerPlayer{	
	const std::unique_ptr<LevelTwoPlayer> levelTwo;
	public:
	~LevelThreePlayer() override;
	//prefers avoiding capture
	LevelThreePlayer(Colour colour);
	void play(ChessBoard &board) const override;
};

#endif


