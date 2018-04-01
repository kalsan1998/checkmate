#include "knight.h"
#include "capture.h"
#include "chessboard.h"
#include "piecetype.h"
#include "location.h"
#include "colour.h"
#include "standardmove.h"
#include <memory>
#include <vector>
using namespace std;

Knight::Knight(Colour colour): 
	Piece{PieceType::KNIGHT, colour, 3, false, false}{}

void Knight::checkAllMoves(const ChessBoard &board){
	shared_ptr<Knight> sharedThis{this};
	Location moves[8] = {{1,2},{2,1},{-1,2},{2,-1},{1,-2},{-2,1},{-1,-2},{-2,-1}};
	
	//iterate through all 8 moves
	for(int i = 0; i < 8; ++i){
		Location newLocation = getLocation() + moves[i];
		//if the move is in bounds, mark the square as reachable
		if(board.isInBounds(newLocation)){
			shared_ptr<Piece> piece = board.getPieceAt(newLocation);
			addReachablePiece(piece);
			if(isMoveOk(board, newLocation)){
				//if square is empty, then do standard move
				if(piece->isEmpty()){
					legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, newLocation));
				//if square belongs to opponent, then do capture
				}else if(piece->getColour() != getColour()){
					legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));	
				}
			}
		}

	}

}
		

void Knight::updateLegalMoves(const ChessBoard &board){
	clearReachablePieces();
	legalMoves.clear();
	checkAllMoves(board);
}
