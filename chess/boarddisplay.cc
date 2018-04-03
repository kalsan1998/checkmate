#include "boarddisplay.h"
#include <vector>
#include <memory>
#include <string>
#include "chessboard.h"
#include "piece.h"
using namespace std;

BoardDisplay::~BoardDisplay(){}
BoardDisplay::BoardDisplay(const ChessBoard &board){
	const vector<vector<int>> bounds = board.getBounds();
	colMin = bounds[0][0];
	colMax = bounds[0][1];
	rowMin = bounds[1][0];
	rowMax = bounds[1][1];
	width = colMax - colMin + 1;
	height = rowMax - rowMin + 1;
	updateBoardInternal(board);
}

string BoardDisplay::getEmptySquareSymbol(Location location) const{
	int row = rowMax - location.row;
	int col = colMax - location.col;
	string symbol = (row + col)%2 == 0 ? " " : "-";
	return symbol;
}

const vector<vector<string>> &BoardDisplay::getBoardInternal() const{
	return boardInternal;
}

void BoardDisplay::updateBoardInternal(const ChessBoard &board){
	boardInternal.clear();
	for(int row = rowMin; row <= rowMax; ++row){
		vector<string> rowVec;
		for(int col = colMin; col <= colMax; ++col){
			Location location{col, row};
			string symbol = " ";
			//check that the location is part of the board because some 
			//boards might have random gaps or something (eg 4 player board)
			if(board.isInBounds(location)){
				shared_ptr<Piece> piece = board.getPieceAt(location);
				//if empty piece, check the colour of square
				if(piece->isEmpty()){
					symbol = getEmptySquareSymbol(location);
				}else{
					symbol = piece->getDisplaySymbol();
				}
			}
			rowVec.emplace_back(symbol);
		}
		boardInternal.emplace_back(rowVec);
	}
}

void BoardDisplay::updateDisplay(const ChessBoard &board){
	updateBoardInternal(board);
	displayBoard();
}
