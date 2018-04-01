#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <vector>
#include <memory>
#include "boardchange.h"
#include "location.h"

class Piece;
class BoardEdit;

class ChessMove: public BoardChange{
	std::vector<std::unique_ptr<const BoardEdit>> editSequence;
	std::shared_ptr<Piece> pieceMoved;
	Location startLocation;
	Location endLocation;

	protected:
	void setEditSequence(std::vector<std::unique_ptr<const BoardEdit>> &&sequence);
	
	public: 
	ChessMove(std::shared_ptr<Piece> piece, Location endLocation);
	ChessMove(ChessMove &&other) noexcept;
	ChessMove &operator=(ChessMove &&other) noexcept;
	Location getStartLocation() const;
	Location getEndLocation() const;
	virtual void execute(ChessBoard &board) const override;
	virtual void executeReverse(ChessBoard &booard) const override;
	bool operator==(const ChessMove &move) const;
	bool operator!=(const ChessMove &move) const;

	virtual ~ChessMove() = 0;
};

#endif
