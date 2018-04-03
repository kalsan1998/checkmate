#ifndef BOARD_DISPLAY_H
#define BOARD_DISPLAY_H

#include <vector>
#include <string>

class ChessBoard;
struct Location;

class BoardDisplay{
	int rowMin;
	int rowMax;
	int colMin;
	int colMax;
	std::vector<std::vector<std::string>> boardInternal;
	void updateBoardInternal(const ChessBoard &board);
	
	virtual void displayBoard() = 0;
	
	protected:
	int height;
	int width;
	const std::vector<std::vector<std::string>> &getBoardInternal() const;
	std::string getEmptySquareSymbol(Location location) const;
	
	public:
	BoardDisplay(const ChessBoard &board);
	void updateDisplay(const ChessBoard &board);
};

#endif
