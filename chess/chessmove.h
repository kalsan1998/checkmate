#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <stdlib>
#include <memory>
#include "boardchange.h"


class BoardEdit;

class ChessMove: public BoardChange{
	const std::vector<std::unique_ptr<const BoardEdit>> editSequence;

	protected:
	void setEditSequence(std::vector<std::unique_ptr<const BoardEdit>> &&sequence);
	
	public:
	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &booard) const override;
	bool operator==(ChessMove &move) const;
	bool operator!=(ChessMove &move) const;

	ChessMove(ChessMove &&other) noexcept;
	ChessMove &operator=(ChessMove &&other) noexcept;
	virtual ~ChessMove() = 0;
};

#endif
