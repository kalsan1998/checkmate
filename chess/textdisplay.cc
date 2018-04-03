#include "textdisplay.h"
#include <iostream>
#include <string>
#include <vector>
#include "chessboard.h"
using namespace std;

TextDisplay::TextDisplay(const ChessBoard &board, ostream &out): BoardDisplay{board}, out{out}{}

void TextDisplay::displayBoard() {
	const vector<vector<string>> internal = getBoardInternal();
	for(int row = height - 1; row > -1; --row){
		out << (row + 1) << " "; //display number on side
		vector<string> rowVec = internal[row];
		for(auto symbol : rowVec){
			out << symbol;
		}
		out << endl;
	}
	//line between board and markings
	for(int i = 0; i < width + 2; ++i){
		out << " ";
	}
	out << endl << "  ";
	
	//display bottom markings
	char colDisplay = 'a';
	for(int i = 0; i < width; ++i){
		out << colDisplay;
		++colDisplay;
	}
	out << endl;
	
}
