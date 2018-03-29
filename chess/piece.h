#ifndef PIECED_H
#define PIECE_H

#include <stdlib>
#include <memory>
#include "boardobserver.h"
#include "piecetype.h"
#include "colour.h"

class ChessBoard;

class Piece: public BoardObserver{
	const PieceType type;
	const Colour colour;
	int value;
	Location location;
	
	virtual shared_ptr<std::vector<std::shared_ptr<ChessMove>>> getLegalMoves() const = 0;

	protected:
	std::vector<std::shared_ptr<Piece>> capturablePieces;
	std::vector<std::shared_ptr<Piece>> threats;
	Piece(PieceType type, Colour colour, int value);

	//returns true if there is a queen/bishop/rook that would
	//check the king if this piece were removed
	bool isBlockingCheck(Board &board) const;
	
	public:
	Colour getColour() const;
	PieceType getType() const;
	int getValue() const;
	Location getLocation() const;
	void setLocation(Location location);

	//this will get all the valid moves on the board, then
	//update the board's legal moves
	void notify(Board &board) override;
};

#endif
