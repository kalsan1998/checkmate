#ifndef LEVEL_THREE_PLAYER_H
#define LEVEL_THREE_PLAYER_H

#include "computerplayer.h"
#include <memory>

class LevelTwoPlayer;
class ChessBoard;

class LevelThreePlayer: public ComputerPlayer{	
	const std::shared_ptr<LevelTwoPlayer> levelTwo;
	public:
	//prefers avoiding capture
	LevelThreePlayer(Colour colour);
	void play(ChessBoard &board) const override;
};

#endif


