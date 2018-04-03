#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "player.h"
#include <vector>
#include <memory>

class ChessBoard;
class ChessMove;

class ComputerPlayer: public Player{	
	protected:
	const std::vector<std::shared_ptr<const ChessMove>> getAllMoves(ChessBoard &board) const;
	std::shared_ptr<const ChessMove> getBestAvoidCaptureMove(ChessBoard &board) const;
	std::shared_ptr<const ChessMove> getBestCaptureMove(ChessBoard &board) const;

	public:
	virtual ~ComputerPlayer() override;
	ComputerPlayer(Colour colour);
};

#endif
