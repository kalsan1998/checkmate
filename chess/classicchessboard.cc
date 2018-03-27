#include "classicchessboard.h"
using namespace std;

ClassicChessBoard::ClassicChessBoard(){
	for(char col = 'a'; col <= 'h'; ++col){ //SWITCH THIS TO ROW
		//White Pieces
		Location whitePawnLoc = Location{col, 2};
		
		theBoard[whitePawnLoc] = make_unique<Pawn>(Colour::WHITE, whitePawnLoc);
		theBoard[whiteRookLoc]
		//Black Pawns
		Location blackLocation = Location{col, 7};
		theBoard[blackLocation] = make_unique<Pawn>(Colour::BLACK, blackLocation);
	}
}

