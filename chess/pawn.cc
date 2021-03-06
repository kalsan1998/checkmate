#include "pawn.h"
#include "chessboard.h"
#include "location.h"
#include "chessmove.h"
#include "standardmove.h"
#include "enpassant.h"
#include "capture.h"
#include <memory>
#include <vector>
using namespace std;

Pawn::Pawn(Colour colour, string displaySymbol, Location direction): 
	Piece{PieceType::PAWN, colour, displaySymbol, 1, false, true}, movementDirection{direction}{
	if(movementDirection.isInLine(Location{0,1})){
		sideDirection = Location{1, 0};
	}else{
		sideDirection = Location{0, 1};
	}
}

void Pawn::checkStandardMoves(ChessBoard &board){
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	Location oneForward = getLocation() + movementDirection;
	Location twoForward = oneForward + movementDirection;

	//standard forward move
	if(isMoveOk(board, oneForward)){
		if(board.getPieceAt(oneForward)->isEmpty()){
			//pawn reaching end
			legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, oneForward));
			//double forward for first move
			if(!(getMoveCount() > 1)){
				if(board.getPieceAt(twoForward)->isEmpty()){
					legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, twoForward));
				}
			}
		}
	}	
}

void Pawn::checkCaptureMoves(ChessBoard &board){
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	Location oneForward = getLocation() + movementDirection;

	//the two possible capture locations
	Location diag1 = oneForward + sideDirection; 
	Location diag2 = oneForward - sideDirection;
	vector<Location> diags{diag1, diag2};
	
	for(auto diag : diags){
		if(board.isInBounds(diag)){
			shared_ptr<Piece> piece = board.getPieceAt(diag);
			piece->addThreat(sharedThis);
			if(isMoveOk(board, diag)){	
				//piece is capturable
				if((piece->getColour() != getColour()) && (!piece->isEmpty())){	
					//just capture
					legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
				}
			}
		}
	}
}

void Pawn::checkEnPassantMoves(ChessBoard &board){
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	Location side1 = getLocation() + sideDirection;
	Location side2 = getLocation() - sideDirection;
	vector<Location> sides = {side1, side2};

	// for both directions check if there was a pawn
	// that skipped a square
	for(auto side : sides){
		if(isMoveOk(board, side + movementDirection)){
			shared_ptr<Piece> piece = board.getPieceAt(side);
			//check that the piece is an opponent pawn and only moved once
			if((piece->getColour() != getColour()) && (piece->getType() == PieceType::PAWN) && (piece->getMoveCount() == 2)){	
				//check if the last move was a pawn double
				StandardMove reqLastMove{piece, side};
				shared_ptr<const ChessMove> lastMove = board.getLastMove();
				if(lastMove && (reqLastMove == *lastMove)){
					piece->addThreat(sharedThis);
					legalMoves.emplace_back(make_shared<EnPassant>(sharedThis, piece, side + movementDirection)); 
				}
			}
		}
	}
}

void Pawn::updateLegalMoves(ChessBoard &board){
	legalMoves.clear();
	checkStandardMoves(board);
	checkCaptureMoves(board);
	checkEnPassantMoves(board);
}
