#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "boardobserver.h"
#include "piecetype.h"
#include "colour.h"
#include "chessmove.h"
#include "location.h"

class ChessBoard;

class Piece: public BoardObserver{
	const PieceType type;
	const Colour colour;
	const int value;
	Location location{0,0};

	const bool isDiagonal; //piece can move diagonally unlimited (ie bishop or queen)
	const bool isStraight; //piece can move straight unlimited (ie rook or queen)
	
	//this will update all the legal moves of the piece, it will also update
	// the list of capturable pieces (and update those pieces' threats field)
	virtual void updateLegalMoves(const ChessBoard &board);

	protected:
	std::vector<std::shared_ptr<const ChessMove>> legalMoves;
	std::vector<std::shared_ptr<Piece>> capturablePieces;
	std::vector<std::shared_ptr<Piece>> threats;
	Piece(PieceType type, Colour colour, int value, bool isDiag, bool isStraigt);

	//returns true if there is a queen/bishop/rook that would
	//check the king if this piece were removed
	bool isBlockingCheck(const ChessBoard &board) const;
	bool isMoveOk(const ChessBoard &board, const Location &location) const;
	
	public:
	Colour getColour() const;
	PieceType getType() const;
	int getValue() const;
	Location getLocation() const;
	virtual void setLocation(const Location &location);

	void clearThreats();
	void addThreat(std::shared_ptr<Piece> threat);
	const std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves() const;

	bool isEmpty() const;
	bool isDiagonalMover() const;
	bool isStraightMover() const;

	//this will get all the valid moves on the board, then
	//update the board's legal moves
	void notify(ChessBoard &board) override;

	bool operator==(const Piece &other) const;
};

#endif
