#ifndef LEVEL_FOUR_PLAYER_H
#define LEVEL_FOUR_PLAYER_H

#include "computerplayer.h"
#include <memory>

class LevelThreePlayer;
class ChessBoard;

class LevelFourPlayer: public ComputerPlayer{	
	const std::shared_ptr<LevelThreePlayer> levelThree;

	public:
	//prefers avoiding capture + capturing others simultaneously
	LevelFourPlayer(Colour colour);
	void play(ChessBoard &board) const override;
};

#endif


