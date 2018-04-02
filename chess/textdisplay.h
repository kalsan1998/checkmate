#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include "boarddisplay.h"
#include <iostream>

class ChessBoard;

class TextDisplay: public BoardDisplay{
	std::ostream &out;
	void displayBoard() const override;
	
	public:
	TextDisplay(ChessBoard &board, std::ostream &out);
};


#endif
