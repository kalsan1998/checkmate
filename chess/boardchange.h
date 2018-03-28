#ifndef BOARD_CHANGE_H
#define BOARD_CHANGE_H

class ChessBoard;

class BoardChange{
	public:
	virtual void execute(ChessBoard &board) const = 0;  //executes this
	virtual void executeReverse(ChessBoard &board) const = 0; //executes the reverse of this
};

#endif
