#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "boardobserver.h"
#include "piecetype.h"
#include "colour.h"
#include "chessmove.h"
#include "location.h"
#include <memory>
#include <string>

class ChessBoard;

class Piece: public BoardObserver{
	const PieceType type;
	const Colour colour;
	const std::string displaySymbol;
	const int value;
	Location location{-1,-1};

	int moveCount = 1;

	const bool isDiagonal; //piece can move diagonally unlimited (ie bishop or queen)
	const bool isStraight; //piece can move straight unlimited (ie rook or queen)

	std::vector<std::shared_ptr<Piece>> threats;
	
	//this will update all the legal moves of the piece, it will also update
	// the list of capturable pieces (and update those pieces' threats field)
	virtual void updateLegalMoves(ChessBoard &board) = 0;

	protected:
	//const std::vector<std::shared_ptr<Piece>> &getReachablePieces() const;
	std::vector<std::shared_ptr<const ChessMove>> legalMoves;
	Piece(PieceType type, Colour colour, std::string displaySymbol, int value, bool isDiag, bool isStraigt);

	//returns true if there is a queen/bishop/rook that would
	//check the king if this piece were removed
	bool isBlockingCheck( ChessBoard &board) const;
	bool isMoveOk(ChessBoard &board, const Location location) const;
	
	public:
	~Piece();

	Colour getColour() const;
	PieceType getType() const;
	std::string getDisplaySymbol() const;
	int getValue() const;
	int &getMoveCount();
	Location getLocation() const;
	virtual void setLocation(const Location location);

	const std::vector<std::shared_ptr<Piece>> &getThreats() const; //gets all pieces that can reach this location
	std::vector<std::shared_ptr<Piece>> getOpponentThreats() const; //gets threats from opponents
	void addThreat(std::shared_ptr<Piece> threat); //means threat can move to this piece's location
	void clearThreats();

	const std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves() const;
	void clearLegalMoves();

	bool isEmpty() const;
	bool isDiagonalMover() const;
	bool isStraightMover() const;

	//this will get all the valid moves on the board, then
	//update the board's legal moves
	virtual void notify(ChessBoard &board) override;

	bool operator==(const Piece &other) const;
};

#endif
