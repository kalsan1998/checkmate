#include "rook.h"
#include "capture.h"
#include "standardmove.h"
#include <memory>
#include <vector>
using namespace std;

Rook::Rook(Colour colour): Piece{PieceType::ROOK, colour, 5, false, true} {}

void Rook::checkAllMoves(const ChessBoard &board){
	shared_ptr<Rook> sharedThis{this};
	Location possibleDirections[4] = {Location{1,0}, Location{0,1}, Location{-1,0}, Location{0,-1}};
	
	//check all the squares in every direction
	for(int i = 0; i < 4; ++i){
		Location direction = possibleDirections[i];
		Location newLocation = location + direction;
		while(board.isInBounds(newLocation){
			//if in bounds, add to moveable squares
			shared_ptr<Piece> piece = board.getPieceAt(newLocation);
			addMoveableSquare(piece);
			//if the move is legal, etiher add chessmove for capture
			//or regular move
			if(isMoveOk(board, location)){
				if(piece.isEmpty()){
					legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, newLocation));
				}else{
					if(piece.getColour() != colour){
						legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
					}
					
					//can't go past a piece
					break;
				}
			}
				
		}
	}

}

void Rook::updateLegalMoves(const ChessBoard &board){
	clearMoveableSquares();
	legalMoves.clear();
	checkAllMoves(board);
}
