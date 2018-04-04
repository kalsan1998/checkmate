#include "player.h"
#include <memory>
#include "chessboard.h"
#include "piece.h"
#include "piecetype.h"
#include "location.h"
using namespace std;

Player::Player(Colour colour): colour{colour}{}
Colour Player::getColour() const { return colour; }


bool Player::isPawnPromotion(ChessBoard &board) const{
	const shared_ptr<const ChessMove> lastMovePtr = board.getLastMove();
	Location startLocation = lastMovePtr->getStartLocation();
	Location endLocation = lastMovePtr->getEndLocation();
	shared_ptr<Piece> startPiece = board.getPieceAt(endLocation);
	if(startPiece->getType() == PieceType::PAWN){
		Location direction = startLocation.getRelativeDirection(endLocation);
		return (!board.isInBounds(endLocation + direction));
	}
	return false;
}

