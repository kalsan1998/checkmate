#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "boardchange.h"

class BoardEdit;

class ChessMove: public BoardChange{
	const std::vector<std::unique_ptr<const BoardEdit>> editSequence;

	public:
	void execute(ChessBoard &board) const override;
	void executeReverse(ChessBoard &booard) const override;
	bool operator==(ChessMove &move) const;
	bool operator!=(ChessMove &move) const;

	void setEditSequence(std::vector<std::unique_ptr<const BoardEdit>> &&sequence);
	ChessMove(ChessMove &&other) noexcept;
	ChessMove &operator=(ChessMove &&other) noexcept;
	virtual ~ChessMove() = 0;
};

#endif
