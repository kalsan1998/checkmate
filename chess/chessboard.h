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

	std::map<Colour, std::map<PieceType, std::vector<std::shared_ptr<Piece>>>> piecesMap;
	std::vector<std::shared_ptr<BoardObserver>> observers;
	std::stack<std::shared_ptr<const ChessMove>> executedMoves;
	std::map<Colour, std::vector<std::shared_ptr<const ChessMove>>> legalMoves;
	void executeChessMove(const std::shared_ptr<const ChessMove>); // execute move and save to stack

	protected:
	std::map<Location, std::shared_ptr<Piece>> theBoard;

	public:
	const std::map<PieceType, std::vector<std::shared_ptr<Piece>>> &getPieces(Colour colour); //gets the pieces for a colour
	King &getKing(Colour colour);
	
	void attachObserver(std::shared_ptr<BoardObserver> obs);
	void detachObserver(std::shared_ptr<BoardObserver> obs);
	void notifyObservers();
	
	bool isInBounds(const Location &location) const; //returns true if location is valid on the board
	std::shared_ptr<Piece> getPieceAt(const Location &location) const; //get the Piece at a location on the board
	std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves(Colour colour); //returns all legal moves for a player
	const ChessMove &getLastMove() const;
	
	void executeEdit(const BoardEdit &edit); //Executes a add/removal without updating state
	void executeMove(Colour colour, Location start, Location end); //Execute a move if valid, else throws
	void undo(); //undoes the last move executed

	bool isLocationSafe(const Location &location, Colour colour) const; //returns true if the location has no opponents threatening it
	bool isCheck(Colour turn); //returns true if turn is in check
	bool isStalemate(Colour turn); //returns true if turn has no legal moves left
	bool isCheckmate(Colour turn); //returns true if the person whose turn it is is checkmated
	
	virtual ~ChessBoard() = 0;
};
#endif
