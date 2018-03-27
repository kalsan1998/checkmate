#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <stdlib>
#include <memory>
#include "colour.h"
#include "piecetype.h"

class BoardObserver;
class Piece;
class BoardChange;
class ChessMove;
struct Location;

class ChessBoard{
	friend BoardChange;

	std::map<Location, std::unique_ptr<Piece>> theBoard;
	std::map<Colour, std::map<PieceType, std::vector<const Piece *>> piecesMap;
	std::vector<BoardObserver *> observers;
	std::stack<shared_ptr<const ChessMove>> executedMoves;
	std::map<Colour, std::vector<std::shared_ptr<const ChessMove>>> legalMoves;
	
	bool isMoveLegal(const ChessMove &move) const;
	std::shared_ptr<const ChessMove> getLastMove() const;
	
	void notifyObservers();

	virtual ~ChessBoard() = 0;


	public:
	void attachObserver(BoardObserver *obs);
	void detachObserver(BoardObserver *obs);

	const Piece &getPieceAt(const Location location) const; //get the Piece at a location on the board
	const std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves(const Colour colour) const; //returns all legal moves for a player
	
	void executeEdit(const BoardChange &edit); //Executes a move/add/removal without updating state
	void executeChessMove(const shared_ptr<const ChessMove> move); //Execute a move/add/removal and updates state + store move
	void undo(); //undoes the last move executed

	bool isStaleMate(const Colour turn); //returns true if turn has no legal moves left
	bool isCheckmate(const Colour turn); //returns true if the person whose turn it is is checkmated
};
#endif
