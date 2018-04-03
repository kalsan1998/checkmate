#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H

#include "boarddisplay.h"
#include <memory>

class Xwindow;
class ChessBoard;

class GraphicsDisplay: public BoardDisplay{
	int squareWidth;
	int squareHeight;
	void displayBoard() override;
	std::shared_ptr<Xwindow> window;
	
	public:
	GraphicsDisplay(const ChessBoard &board);
};


#endif

