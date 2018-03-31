#include "king.h"
#include "rook.h"
#include "ccastling.h"
#include "chessboard.h"
#include "standardmove.h"
#include "capture.h"
#include <memory>
#include <vector>
#include <limits.h>
using namespace std;

King::King(Colour colour): Piece{PieceType::KING, colour, INT_MAX, false false}{}

void King::checkCastlingMoves(const ChessBoard &board){
}

void King::checkStandardMoves(const ChessBoard &board){
	vector<shared_ptr<Piece>> &moveableSqrs = getMovableSquares();
	for(auto piece : moveableSqrs){
		//regular move
		if(piece->isEmpty()){
			legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, movement));
		//capture move	
		}else if(piece->getColour() != colour){
			legalMoves.emplace(make_shared<Capture>(sharedThis, piece));
		}	
	}
}

void King::notify(ChessBoard &board){
	clearMoveableSquares();
	shared_ptr<King> sharedThis{this};
	for(int row = -1; row < 2; ++row){
		for(int col = -1; col <2; ++col){
			if((col != 0) || (row != 0)){
				Location movement = location + Location{row, col};
				if(board.isInBounds(movement)){
					addMoveableSquare(board.getPieceAt(movement));
				}
			}
		}
	}
}

void King::kingNotify(ChessBoard &board){
	notify();
	legalMoves.clear();
	checkStandardMoves(board);
	checkCastlingMoves(board);
}

