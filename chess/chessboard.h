#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <map>
#include <stack>
#include <memory>
#include "colour.h"
#include "piecetype.h"

class BoardDisplay;
class BoardEdit;
class PieceAdd;
class PieceRemove;
class ChessMove;
class Piece;
class King;
struct Location;

class ChessBoard{
	friend PieceAdd;
	friend PieceRemove;

	std::map<Colour, std::map<PieceType, std::vector<std::shared_ptr<Piece>>>> piecesMap;
	std::vector<std::shared_ptr<BoardDisplay>> displays;
	std::stack<std::shared_ptr<const ChessMove>> executedMoves;
	std::map<Colour, std::vector<std::shared_ptr<const ChessMove>>> legalMoves;

	protected:
	std::map<Location, std::shared_ptr<Piece>> theBoard;

	public:
	std::vector<Colour> getColours() const;
	std::map<Location, std::shared_ptr<Piece>> &getBoard();
	virtual const std::vector<std::vector<int>> getBounds() const = 0; //returns bounds as {col_min, col_max}}{row_min, row_max}}
	bool isInBounds(const Location &location) const; //returns true if location is valid on the board

	std::shared_ptr<Piece> getPieceAt(const Location &location) const; //get the Piece at a location on the board
	const std::map<PieceType, std::vector<std::shared_ptr<Piece>>> &getPieces(Colour colour); //gets the pieces for a colour
	std::shared_ptr<King> getKing(Colour colour);
	void notifyPieces();

	void attachDisplay(std::shared_ptr<BoardDisplay> obs);
	void detachDisplay(std::shared_ptr<BoardDisplay> obs);
	void notifyDisplays();
	
	std::vector<std::shared_ptr<const ChessMove>> &getLegalMoves(Colour colour); //returns all legal moves for a player
	const std::shared_ptr<const ChessMove> getLastMove() const;
	void filterCheckMoves(); //filters "legal moves" during check
	
	void executeEdit(const BoardEdit &edit); //Executes a add/removal without updating state
	void executeMove(Colour colour, const Location &start, const Location &end); //Execute a move if valid, else throws
	void executeChessMove(const std::shared_ptr<const ChessMove>); // execute move and save to stack
	void undo(); //undoes the last move executed

	bool isLocationSafe(const Location &location, Colour colour) const; //returns true if the location has no opponents threatening it
	bool isCheck(Colour turn); //returns true if turn is in check
	bool isStalemate(Colour turn); //returns true if turn has no legal moves left
	bool isCheckmate(Colour turn); //returns true if the person whose turn it is is checkmated
	
	virtual ~ChessBoard() = 0;
};
#endif
