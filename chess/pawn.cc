#include "pawn.h"
#include "capture.h"
#include "enpassant.h"
#include "pawnend.h"
#include "chessboard.h"
#include "pawnendcapture.h"
#include "standardmove.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "piecetype.h"
#include "location.h"
#include "colour.h"
#include <memory>
#include <vector>
using namespace std;

Pawn::Pawn(Colour colour, Location direction): 
	Piece{PieceType::PAWN, colour, 1, false, false}, movementDirection{direction}{
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
			legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, oneForward));
			//double forward for first move
			if(!(getMoveCount() > 1)){
				if(board.getPieceAt(twoForward)->isEmpty()){
					legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, twoForward));
				}
			}
			//pawn reaching end
			if(!board.isInBounds(twoForward)){
				legalMoves.emplace_back(make_shared<PawnEnd>(sharedThis, oneForward));
			}
		}
	}	
}

void Pawn::checkCaptureMoves(ChessBoard &board){
	shared_ptr<Piece> sharedThis = board.getPieceAt(getLocation());
	Location oneForward = getLocation() + movementDirection;
	Location twoForward = oneForward + movementDirection;

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
					//capture piece and make it to end
					if(!board.isInBounds(twoForward)){	
						legalMoves.emplace_back(make_shared<PawnEndCapture>(sharedThis, piece));
					//just capture
					}else{
						legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
					}
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
			if(piece->getType() == PieceType::PAWN){	
				//check if the last move was a pawn double
				StandardMove reqLastMove{static_pointer_cast<Piece>(piece), side};
				shared_ptr<const ChessMove> lastMove = board.getLastMove();
				if(lastMove && (*lastMove == reqLastMove)){
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
