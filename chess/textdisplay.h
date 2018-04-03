#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include "boarddisplay.h"
#include <iostream>

class ChessBoard;

class TextDisplay: public BoardDisplay{
	std::ostream &out;
	void displayBoard()  override;
	
	public:
	TextDisplay(const ChessBoard &board, std::ostream &out);
};


#endif
