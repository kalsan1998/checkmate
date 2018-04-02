#include "classicchessboard.h"
#include "piecefactory.h"
#include "pieceadd.h"
#include "location.h"
#include "piece.h"
#include "emptypiece.h"
#include <iostream>
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
			getBoard()[location] = make_shared<EmptyPiece>();
		}
	}

	for(char col = 'a'; col <= 'h'; ++col){
		//add the Pawns
		shared_ptr<Piece> whitePawn = PieceFactory::generatePiece('P');
		shared_ptr<Piece> blackPawn = PieceFactory::generatePiece('p');
		executeEdit(PieceAdd{whitePawn, Location{col, whitePawnRow}});
		executeEdit(PieceAdd{blackPawn, Location{col, blackPawnRow}});
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
		executeEdit(PieceAdd{whitePiece, Location{col, whiteBigPieceRow}});
		executeEdit(PieceAdd{blackPiece, Location{col, blackBigPieceRow}});
		attachObserver(whitePiece);
		attachObserver(blackPiece);
	}
	//notify all the pieces to get the legal moves
	cout << "NOTIFYING" << endl;
	notifyObservers();
	cout << "BOARD CREATED" << endl;
}

