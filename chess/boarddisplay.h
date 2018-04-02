#ifndef BOARD_DISPLAY_H
#define BOARD_DISPLAY_H

#include "boardobserver.h"
#include <vector>
#include <string>

class ChessBoard;
struct Location;

class BoardDisplay: public BoardObserver{
	int rowMin;
	int rowMax;
	int colMin;
	int colMax;
	std::vector<std::vector<std::string>> boardInternal;
	
	virtual void displayBoard() const = 0;
	void updateBoardInternal(ChessBoard &board);
	std::string getEmptySquareSymbol(Location location) const;
	
	protected:
	int height;
	int width;
	const std::vector<std::vector<std::string>> &getBoardInternal() const;
	
	public:
	BoardDisplay(ChessBoard &board);
	void notify(ChessBoard &board) override;
};

#endif
