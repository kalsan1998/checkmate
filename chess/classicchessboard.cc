#include "classicchessboard.h"
#include "piecefactory.h"
using namespace std;

ClassicChessBoard::ClassicChessBoard(){
	const int blackBigPieceRow = 8;
	const int whiteBigPieceRow = 1;
	const int blackPawnRow = 7;
	const int whitePawnRow = 2;
	//initialize 'empty' board, then add the pieces using the edit class
	for(char col = 'a'; col <= 'h'; ++col){
		for(int row = 1; row<= 8; ++row){
			Location location{col, row};
			getBoard()[Location] = make_unique<NoPiece>();
		}
	}

	for(col = 'a'; col <= 'h'; ++col){
		//add the Pawns
		executeEdit(PieceAdd{Location{col, whitePawnRow}, PieceFactory::generatePiece('P')}); 
		executeEdit(PieceAdd{Location{col, blackPawnRow}, PieceFactory::generatePiece('p')}); 
		
		//determine the bigger piece type based on column
		char type = '-';
		if((col == 'a') || (col == 'h')){
			type = 'r';
		}else if((col == 'b') || (col == 'g')){
			type = 'n';
		}else if((col == 'c') || (col == 'f')){
			type = 'b';
		}else if(col == 'd'){
			type = 'q';
		}else if(col == 'e'){
			type = 'k';
		}
		//execute the edit, this will handle adding piece to 
		//the board and the pieces map
		//Add white
		executeEdit(PieceAdd{Location{col, whiteBigPieceRow}, PieceFactory::generatePiece(type - 32)}});
		//Add black
		executeEdit(PieceAdd{Location{col, blackBigPieceRow}, PieceFactory::generatePiece(type)});
	}
	//notify all the pawns to get the legal moves
	notifyObservers();
}

