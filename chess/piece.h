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

	int moveCount = 0;

	const bool isDiagonal; //piece can move diagonally unlimited (ie bishop or queen)
	const bool isStraight; //piece can move straight unlimited (ie rook or queen)

	std::vector<std::shared_ptr<Piece>> moveableSquares;
	std::vector<std::shared_ptr<Piece>> threats;
	
	//this will update all the legal moves of the piece, it will also update
	// the list of capturable pieces (and update those pieces' threats field)
	virtual void updateLegalMoves(const ChessBoard &board) = 0;

	protected:
	std::vector<std::shared_ptr<Piece>> &getMoveableSquares() const;
	void clearMoveableSquares()
	void addMoveableSquare(std::shared_ptr<Piece>> square); //means this piece can move to the sqaures location, also updates squares 'threats' field
	void clearThreats();
	void addThreat(std::shared_ptr<Piece> threat); //means threat can move to this piece's location
	std::vector<std::shared_ptr<const ChessMove>> legalMoves;
	Piece(PieceType type, Colour colour, int value, bool isDiag, bool isStraigt);

	//returns true if there is a queen/bishop/rook that would
	//check the king if this piece were removed
	bool isBlockingCheck(const ChessBoard &board) const;
	bool isMoveOk(const ChessBoard &board, const Location &location) const;
	
	public:
	Colour getColour() const;
	PieceType getType() const;
	int getValue() const;
	int &getMoveCount() const;
	Location getLocation() const;
	virtual void setLocation(const Location &location);

	const std::vector<std::shared_ptr<Piece>> &getThreats() const;
	const std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves() const;

	bool isEmpty() const;
	bool isDiagonalMover() const;
	bool isStraightMover() const;

	//this will get all the valid moves on the board, then
	//update the board's legal moves
	virtual void notify(ChessBoard &board) override;

	bool operator==(const Piece &other) const;
};

#endif
