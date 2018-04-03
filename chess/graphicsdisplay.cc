#include "graphicsdisplay.h"
#include "window.h"
#include <string>
#include <vector>
#include "chessboard.h"
#include <sstream>
#include <memory>
using namespace std;

GraphicsDisplay::~GraphicsDisplay(){}
GraphicsDisplay::GraphicsDisplay(const ChessBoard &board): BoardDisplay{board}, window{500,500}{
	squareWidth = 500/(width+1);
	squareHeight = 500/(height+1);
}

void GraphicsDisplay::displayBoard(){
	const vector<vector<string>> internal = getBoardInternal();
	for(int row = height - 1; row > -1; --row){
		int y = (height - row -1) * squareHeight;
		ostringstream oss;
		oss << (row + 1);
		string rowStr = oss.str();
		window.drawString(0 + squareHeight/2, y + squareHeight/2, rowStr ); //display number on side
		vector<string> rowVec = internal[row];
		for(int col = 0; col < width; ++col){
			int x = (col+1) *squareWidth;
			if((row + col)%2 == 0){
				window.fillRectangle(x,y,squareWidth,squareHeight,Xwindow::White);
			}else{
				window.fillRectangle(x,y,squareWidth,squareHeight,Xwindow::Black);
			}
			string symbol = rowVec[col];
			if(symbol != "-") window.drawString(x + squareWidth/2, y + squareHeight/2, symbol, Xwindow::Blue);
		}
	}	
	//display bottom markings
	char colDisplay = 'a';
	for(int i = 1; i <= width; ++i){
		ostringstream oss;
		oss << colDisplay;
		window.drawString(i*squareWidth + squareWidth/2, height*squareHeight + squareHeight/2, oss.str());
		++colDisplay;
	}
}
