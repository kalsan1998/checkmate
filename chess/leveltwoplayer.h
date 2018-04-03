#ifndef LEVEL_TWO_PLAYER_H
#define LEVEL_TWO_PLAYER_H

#include "computerplayer.h"
#include <memory>

class LevelOnePlayer;
class ChessBoard;

class LevelTwoPlayer: public ComputerPlayer{	
	const std::shared_ptr<LevelOnePlayer> levelOne;
	public:
	//prefers captures and checks
	LevelTwoPlayer(Colour colour);
	void play(ChessBoard &board) const override;
};

#endif

