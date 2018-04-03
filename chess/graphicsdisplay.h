#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H

#include "boarddisplay.h"
#include "window.h"

class ChessBoard;

class GraphicsDisplay: public BoardDisplay{
	int squareWidth;
	int squareHeight;
	void displayBoard() override;
	Xwindow window;
	
	public:
	~GraphicsDisplay();
	GraphicsDisplay(const ChessBoard &board);
};


#endif

