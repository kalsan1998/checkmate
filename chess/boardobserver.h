#ifndef BOARD_OBSERVER_H
#define BOARD_OBSERVER_H

class ChessBoard;

class BoardObserver{
	public:
	virtual void notify(ChessBoard &board) = 0;
};
	
#endif
