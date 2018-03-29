#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <stdlib>
#include <memory>
#include "colour.h"
#include "piecetype.h"

class BoardObserver;
class Piece;
class BoardEdit;
class ChessMove;
struct Location;

class ChessBoard{
	friend BoardChange;

	std::map<Colour, std::map<PieceType, std::vector<shared_ptr<const Piece>>> piecesMap;
	std::vector<BoardObserver *> observers;
	std::stack<shared_ptr<const ChessMove>> executedMoves;
	std::map<Colour, std::vector<std::shared_ptr<const ChessMove>>> legalMoves;
	
	bool isMoveLegal(const ChessMove &move) const; //checks if the given move is legal
	std::shared_ptr<const ChessMove> getLastMove() const;

	protected:
	std::map<Location, std::shared_ptr<Piece>> theBoard;

	public:
	const std::map<Location, std::shared_ptr<Piece>> &getBoard() const; //returns the board
	const std::map<PieceType, std::shared_ptr<Piece>> &getPiece(Colour colour) const; //gets the pieces for a colour
	
	void attachObserver(BoardObserver *obs);
	void detachObserver(BoardObserver *obs);
	void notifyObservers();
	
	bool isInBounds(const Location &location) const; //returns true if location is valid on the board
	const Piece &getPieceAt(const Location &location) const; //get the Piece at a location on the board
	const std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves(const Colour colour) const; //returns all legal moves for a player
	
	void executeEdit(const BoardEdit &edit); //Executes a add/removal without updating state
	void executeChessMove(shared_ptr<const ChessMove> move); //Execute a move and updates state + store move
	void undo(); //undoes the last move executed

	bool isStaleMate(const Colour turn); //returns true if turn has no legal moves left
	bool isCheckmate(const Colour turn); //returns true if the person whose turn it is is checkmated
	
	virtual ~ChessBoard() = 0;
};
#endif
