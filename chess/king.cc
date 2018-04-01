#include "king.h"
#include "rook.h"
#include "castling.h"
#include "chessboard.h"
#include "standardmove.h"
#include "capture.h"
#include <memory>
#include <vector>
#include <limits.h>
using namespace std;

King::King(Colour colour): Piece{PieceType::KING, colour, INT_MAX, false, false}{}

void King::checkCastlingMoves(const ChessBoard &board){
	shared_ptr<King> sharedThis{this};
	//castling is only availbale if king has not moved yet and is not in check
	if(!(getMoveCount() > 1) && !(board.isCheck(getColour()))){
		//go over all the rooks
		const vector<shared_ptr<Piece>> &rooks = board.getPieces(getColour()).find(PieceType::ROOK)->second;
		for(auto &rook : rooks){
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
					legalMoves.emplace_back(make_shared<Castling>(sharedThis, static_pointer_cast<Rook>(rook), newLocation, newLocation - direction));
				}
			}
		}
	}
}

void King::checkStandardMoves(const ChessBoard &board){
	shared_ptr<King> sharedThis{this};
	const vector<shared_ptr<Piece>> &moveableSqrs = getReachablePieces();
	for(auto piece : moveableSqrs){
		//regular move
		if(piece->isEmpty()){
			legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, piece->getLocation()));
		//capture move	
		}else if(piece->getColour() != getColour()){
			legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
		}	
	}
}

void King::notify(ChessBoard &board){
	clearReachablePieces();
	for(int row = -1; row < 2; ++row){
		for(int col = -1; col <2; ++col){
			if((col != 0) || (row != 0)){
				Location movement = getLocation() + Location{row, col};
				if(board.isInBounds(movement)){
					addReachablePiece(board.getPieceAt(movement));
				}
			}
		}
	}
}

void King::updateLegalMoves(const ChessBoard &board){
	legalMoves.clear();
	checkStandardMoves(board);
	checkCastlingMoves(board);
}

void King::kingNotify(ChessBoard &board){
	notify(board);
	Piece::notify(board);
}

