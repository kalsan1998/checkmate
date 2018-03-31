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
		shared_ptr<Pawn> whitePawn = PieceFactory::generatePiece('P');
		shared_ptr<Pawn> blackPawn = PieceFactory::generatePiece('p');
		executeEdit(PieceAdd{Location{col, whitePawnRow}, whitePawn);
		executeEdit(PieceAdd{Location{col, blackPawnRow}, blackPawn);
		attachObserver(whitePawn);
		attachObserver(blackPawn);
		
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
		shared_ptr<Piece> whitePiece = PieceFactory::generatePiece(type - 32);
		shared_ptr<Piece> blackPiece = PieceFactory::generatePiece(type);
		executeEdit(PieceAdd{Location{col, whiteBigPieceRow}, whitePiece);
		executeEdit(PieceAdd{Location{col, blackBigPiecenRow}, blackPiece);
		attachObserver(whitePiece);
		attachObserver(blackPiece);
	}
	//notify all the pieces to get the legal moves
	notifyObservers();
}

