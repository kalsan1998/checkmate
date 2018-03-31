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
	shared_ptr<King> sharedThis{this};
	//castling is only availbale if king has not moved yet and is not in check
	if(!(moveCount > 1) && !(board.isCheck(getColour()))){
		//go over all the rooks
		vector<shared_ptr<Piece>> &rooks = board.getPieces(colour)[PieceType::ROOK];
		for(auto &rook : rooks){
			//check if rook moved first
			if(!(rook->getMoveCount() > 1)){
				Location rookLocation = rook->getLocation();
				Location direction = location.getRelativeDirection(rookLocation);
				
				//check both squares in direction of rook
				Location newLocation = location;
				bool castlingEnabled = true;
				
				for(int i = 0; i < 2; ++i){
					newLocation += direction;
					//if one of the two squares arent safe then caslting is invalid
					if(!board.isLocationSafe(newLocation, colour)){
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

void King::checkStandardMoves(const ChessBoard &board){
	shared_ptr<King> sharedThis{this};
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

void King::updateLegalMoves(ChessBoard &board){
	notify();
	legalMoves.clear();
	checkStandardMoves(board);
	checkCastlingMoves(board);
}

void King::kingNotify(Chessboard &board){
	Piece::notify(board);
}

