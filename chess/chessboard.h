#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <map>
#include <stack>
#include <memory>
#include "colour.h"
#include "piecetype.h"

class BoardObserver;
class Piece;
class BoardEdit;
class PieceAdd;
class PieceRemove;
class ChessMove;
class King;
struct Location;

class ChessBoard{
	friend PieceAdd;
	friend PieceRemove;

	std::map<Colour, std::map<PieceType, std::vector<std::shared_ptr<const Piece>>>> piecesMap;
	std::vector<std::shared_ptr<BoardObserver>> observers;
	std::stack<std::shared_ptr<const ChessMove>> executedMoves;
	std::map<Colour, std::vector<std::shared_ptr<const ChessMove>>> legalMoves;
	
	bool isMoveLegal(const ChessMove &move) const; //checks if the given move is legal

	protected:
	std::map<Location, std::shared_ptr<Piece> > theBoard;

	public:
	const std::map<Location, std::shared_ptr<Piece>> &getBoard() const; //returns the board
	const std::map<PieceType, std::vector<std::shared_ptr<Piece>>> &getPieces(Colour colour) const; //gets the pieces for a colour
	const King &getKing(const Colour colour) const;
	
	void attachObserver(BoardObserver *obs);
	void detachObserver(BoardObserver *obs);
	void notifyObservers();
	
	bool isInBounds(const Location &location) const; //returns true if location is valid on the board
	std::shared_ptr<Piece> getPieceAt(const Location &location) const; //get the Piece at a location on the board
	const std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves(const Colour colour) const; //returns all legal moves for a player
	std::shared_ptr<const ChessMove> getLastMove() const;
	
	void executeEdit(const BoardEdit &edit); //Executes a add/removal without updating state
	void executeChessMove(std::shared_ptr<const ChessMove> move); //Execute a move and updates state + store move
	void undo(); //undoes the last move executed

	bool isLocationSafe(const Location &location, const Colour colour); //returns true if the location has no opponents threatening it
	bool isCheck(const Colour turn) const; //returns true if turn is in check
	bool isStaleMate(const Colour turn) const; //returns true if turn has no legal moves left
	bool isCheckmate(const Colour turn) const; //returns true if the person whose turn it is is checkmated
	
	virtual ~ChessBoard() = 0;
};
#endif
