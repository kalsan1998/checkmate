#include "humanplayer.h"
#include "chessboard.h"
#include "chessmove.h"
#include "piece.h"
#include "pawnend.h"
#include "pieceadd.h"
#include "invalidmove.h"
#include "pawnendcapture.h"
#include "piecefactory.h"
#include "colour.h"
#include <iostream>
#include <memory>
using namespace std;

HumanPlayer::HumanPlayer(Colour colour, istream &in): Player{colour}, in{in}{} 

void HumanPlayer::play(ChessBoard &board) const{
	string start;
	string end;
	if((in >> start) && (in >> end)){
		Location startLocation{start};
		Location endLocation{end};
			board.executeMove(getColour(), startLocation, endLocation);
			
			//check if pawn promotion
			const shared_ptr<const ChessMove> lastMovePtr = board.getLastMove();
			const PawnEnd pawnEnd{board.getPieceAt(startLocation), endLocation};
			const PawnEndCapture pawnEndCap{board.getPieceAt(startLocation), board.getPieceAt(endLocation)};
			if((*lastMovePtr == pawnEnd) || (*lastMovePtr == pawnEndCap)){
				char newPieceChar;
				if(in >> newPieceChar){
					shared_ptr<Piece> newPiece = PieceFactory::generatePiece(newPieceChar);
					if(newPiece->getColour() == getColour()){
						board.executeEdit(PieceAdd{newPiece, endLocation});
						board.attachObserver(newPiece);
						board.notifyObservers();
					}else{
						throw InvalidMove{};
					}
				}
			}
	}
}
