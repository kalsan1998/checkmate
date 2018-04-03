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
	const std::vector<std::shared_ptr<const ChessMove>> getAvoidCaptureMoves(ChessBoard &board) const;
	const std::vector<std::shared_ptr<const ChessMove>> getPreferCaptureMoves(ChessBoard &board) const;

	public:
	ComputerPlayer(Colour colour);
};

#endif
