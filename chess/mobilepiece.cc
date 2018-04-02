#include "mobilepiece.h"
#include "chessboard.h"
#include "location.h"
#include "piecetype.h"
#include "colour.h"
#include "capture.h"
#include "standardmove.h"
#include <vector>
#include <memory>
#include <string>
using namespace std;

MobilePiece::MobilePiece(PieceType type, Colour colour, string displaySymbol, int value, bool isDiag, bool isStraight, vector<Location> directions):
	Piece(type, colour, displaySymbol, value, isDiag, isStraight), directions{directions}{}
	
void MobilePiece::checkRegularMoves(ChessBoard &board){	
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	//check all the squares in every direction
	for(size_t i = 0; i < directions.size(); ++i){
		Location direction = directions[i];
		Location newLocation = getLocation() + direction;
		while(board.isInBounds(newLocation)){
			//if in bounds, add to moveable squares
			shared_ptr<Piece> piece = board.getPieceAt(newLocation);
			piece->addThreat(sharedThis);
			//if the move is legal, etiher add chessmove for capture
			//or regular move
			
			if(isMoveOk(board, newLocation)){
				if(piece->isEmpty()){
					legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, newLocation));
				}else{
					if(piece->getColour() != getColour()){
						legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
					}
					
					//can't go past a piece
					break;
				}
			}
			newLocation += direction;		
		}
	}
}
void MobilePiece::updateLegalMoves(ChessBoard &board){
	legalMoves.clear();
	checkRegularMoves(board);
}

