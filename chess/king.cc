#include "king.h"
#include "rook.h"
#include "castling.h"
#include "chessboard.h"
#include "standardmove.h"
#include "capture.h"
#include <memory>
#include <vector>
#include <limits.h>
#include <string>
using namespace std;

King::King(Colour colour, string displaySymbol): Piece{PieceType::KING, colour, displaySymbol, INT_MAX, false, false}{}

void King::checkCastlingMoves(ChessBoard &board){
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	//castling is only availbale if king has not moved yet and is not in check
	if(!(getMoveCount() > 1) && !(board.isCheck(getColour()))){
		//go over all the rooks
		const vector<shared_ptr<Piece>> &rooks = board.getPieces(getColour()).find(PieceType::ROOK)->second;
		for(auto rook : rooks){
			//check if rook moved first
			if(!(rook->getMoveCount() > 1)){
				Location rookLocation = rook->getLocation();
				Location direction = getLocation().getRelativeDirection(rookLocation);
				
				//check both squares in direction of rook
				Location newLocation = getLocation();
				bool castlingEnabled = true;
				
				for(int i = 0; i < 2; ++i){
					newLocation += direction;
					//if one of the two squares arent safe then caslting is invalid
					if(!board.isLocationSafe(newLocation, getColour())){
						castlingEnabled = false;
						break;
					}
				}
				if(castlingEnabled){
					legalMoves.emplace_back(make_shared<Castling>(sharedThis, rook, newLocation, newLocation - direction));
				}
			}
		}
	}
}

void King::checkStandardMoves(ChessBoard &board){
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	for(auto location : moveableLocation){
		if(board.isLocationSafe(location, getColour())){
			shared_ptr<Piece> piece = board.getPieceAt(location);
			//regular move
			if(piece->isEmpty()){
				legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, location));
			//capture move	
			}else if(piece->getColour() != getColour()){
				legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
			}
		}
	}
}

void King::notify(ChessBoard &board){
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	moveableLocation.clear();
	for(int row = -1; row < 2; ++row){
		for(int col = -1; col <2; ++col){
			if((col != 0) || (row != 0)){
				Location movement = getLocation() + Location{row, col};
				if(board.isInBounds(movement)){
					board.getPieceAt(movement)->addThreat(sharedThis);
					moveableLocation.emplace_back(movement);
				}
			}
		}
	}
}

void King::updateLegalMoves(ChessBoard &board){
	legalMoves.clear();
	checkStandardMoves(board);
	checkCastlingMoves(board);
}

void King::kingNotify(ChessBoard &board){
	notify(board);
	Piece::notify(board);
}

