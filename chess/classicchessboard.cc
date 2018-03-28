#include "classicchessboard.h"
#include "pieceinfo.h"
using namespace std;

ClassicChessBoard::ClassicChessBoard(){
	const int blackBigPieceRow = 8;
	const int whiteBigPieceRow = 1;
	const int blackPawnRow = 7;
	const int whitePawnRow = 2;
	//initialize "empty" board, then add the pieces using the edit class
	for(char col = 'a'; col <= 'h'; ++col){
		for(int row = 1; row<= 8; ++row){
			Location location{col, row};
			getBoard()[Location] = make_unique<NoPiece>();
		}
	}

	for(col = 'a'; col <= 'h'; ++col){
		//add the Pawns
		executeEdit(PieceAdd{Location{col, whitePawnRow}, PieceInfo{PieceType::PAWN, Colour::WHITE}}); 
		executeEdit(PieceAdd{Location{col, blackPawnRow}, PieceInfo{PieceType::PAWN, Colour::BLACK}}); 
		
		//determine the bigger piece type based on column
		PieceType type;
		if((col == 'a') || (col == 'h')){
			type = PieceType::ROOK;
		}else if((col == 'b') || (col == 'g')){
			type = PieceType::KNIGHT;
		}else if((col == 'c') || (col == 'f')){
			type = PieceType::BISHOP;
		}else if(col == 'd'){
			type = PieceType::QUEEN;
		}else if(col == 'e'){
			type = PieceType::KING;
		}
		//execute the edit, this will handle adding piece to 
		//the board and the pieces map
		executeEdit(PieceAdd{Location{col, whiteBigPieceRow}, PieceInfo{type, Colour::WHITE}});
		executeEdit(PieceAdd{Location{col, blackBigPieceRow}, PieceInfo{type, Colour::BLACK}});
	}
	//notify all the pawns to get the legal moves
	notifyObservers();
}

