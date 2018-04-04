#ifndef LEVEL_TWO_PLAYER_H
#define LEVEL_TWO_PLAYER_H

#include "computerplayer.h"
#include "leveloneplayer.h"
#include <memory>

class ChessBoard;

class LevelTwoPlayer: public ComputerPlayer{	
	const std::unique_ptr<LevelOnePlayer> levelOne;
	public:
	~LevelTwoPlayer() override;
	//prefers captures and checks
	LevelTwoPlayer(Colour colour);
	void doPlay(ChessBoard &board) const override;
};

#endif

