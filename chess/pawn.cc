#include "pawn.h"
#include "capture.h"
#include "enpassant.h"
#include "pawnend.h"
#include "pawndouble.h"
#include "chessboard.h"
#include "pawnendcapture.h"
#include "standardmove.h"
/*#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
*/
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

void Pawn::setFirstMove(bool b){
	firstMove = b;
}

void Pawn::setLocation(const Location &location){
	firstMove = false;
	Piece::setLocation(location);
}

void Pawn::checkStandardMoves(const ChessBoard &board){
	shared_ptr<Pawn> sharedThis{this};
	Location oneForward =getLocation() + movementDirection;
	Location twoForward = oneForward + movementDirection;
		
	//standard forward move
	if(isMoveOk(board, oneForward)){
		if(board.getPieceAt(oneForward)->isEmpty()){
			legalMoves.emplace_back(make_shared<StandardMove>(sharedThis, oneForward));
			
			//double forward for first move
			if(firstMove){
				if(board.getPieceAt(twoForward)->isEmpty()){
					legalMoves.emplace_back(make_shared<PawnDouble>(sharedThis, oneForward));
				}
			}
			//pawn reaching end
			if(!board.isInBounds(twoForward)){
/*				legalMoves.emplace_back(make_shared<PawnEnd>(sharedThis, make_shared<Queen>(colour), oneForward));
				legalMoves.emplace_back(make_shared<PawnEnd>(sharedThis, make_shared<Rook>(colour), oneForward));
				legalMoves.emplace_back(make_shared<PawnEnd>(sharedThis, make_shared<Bishop>(colour), oneForward));
				legalMoves.emplace_back(make_shared<PawnEnd>(sharedThis, make_shared<Knight>(colour), oneForward));
*/			}
		}
	}	
}

void Pawn::checkCaptureMoves(const ChessBoard &board){
	shared_ptr<Pawn> sharedThis{this};
	Location oneForward = getLocation() + movementDirection;
	Location twoForward = oneForward + movementDirection;

	//the two possible capture locations
	Location diag1 = oneForward + sideDirection; 
	Location diag2 = oneForward - sideDirection;
	Location diags[2] = {diag1, diag2};
	
	for(int i = 0; i < 2; ++i){
		Location diag = diags[i];
		if(isMoveOk(board, diag)){
			shared_ptr<Piece> piece = board.getPieceAt(diag);
			
			//piece is capturable
			if(!piece->isEmpty() && (piece->getColour() != getColour())){	
				piece->addThreat(sharedThis);
				
				//capture piece and make it to end
				if(!board.isInBounds(twoForward)){	
	/*				legalMoves.emplace_back(make_shared<PawnEndCapture>(sharedThis, piece, make_shared<Queen>(colour)));
					legalMoves.emplace_back(make_shared<PawnEndCapture>(sharedThis, piece, make_shared<Rook>(colour)));
					legalMoves.emplace_back(make_shared<PawnEndCapture>(sharedThis, piece, make_shared<Bishop>(colour)));
					legalMoves.emplace_back(make_shared<PawnEndCapture>(sharedThis, piece, make_shared<Knight>(colour)));
	*/			//just capture
				}else{
					legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
					legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
					legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
					legalMoves.emplace_back(make_shared<Capture>(sharedThis, piece));
				}
			}
		}
	}
}

void Pawn::checkEnPassantMoves(const ChessBoard &board){
	shared_ptr<Pawn> sharedThis{this};
	Location side1 = getLocation() + sideDirection;
	Location side2 = getLocation() - sideDirection;
	Location sides[2] = {side1, side2};

	// for both directions check if there was a pawn
	// that skipped a square
	for(int i = 0; i < 2; ++i){
		Location side = sides[i];
		if(isMoveOk(board, side + movementDirection)){
			shared_ptr<Piece> piece = board.getPieceAt(side);
			if(piece->getType() == PieceType::PAWN){	
				PawnDouble reqLastMove{static_pointer_cast<Pawn>(piece), side};
				if(*(board.getLastMove()) == reqLastMove){
					piece->addThreat(sharedThis);
					legalMoves.emplace_back(make_shared<EnPassant>(sharedThis, static_pointer_cast<Pawn>(piece), side + movementDirection)); 
				}
			}
		}
	}
}

void Pawn::updateLegalMoves(const ChessBoard &board){
	capturablePieces.clear();
	legalMoves.clear();
	checkStandardMoves(board);
	checkCaptureMoves(board);
	checkEnPassantMoves(board);
}
