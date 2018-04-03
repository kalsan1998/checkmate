#include "computerplayer.h"
#include <vector>
#include <memory>
#include "colour.h"
#include "location.h"
#include "chessmove.h"
#include "chessboard.h"
#include "piece.h"
#include "piecetype.h"
using namespace std;

ComputerPlayer::ComputerPlayer(Colour colour): Player{colour}{}
ComputerPlayer::~ComputerPlayer(){}

const vector<shared_ptr<const ChessMove>> ComputerPlayer::getAllMoves(ChessBoard &board) const{
	return board.getLegalMoves(getColour());
}

shared_ptr<const ChessMove> ComputerPlayer::getBestAvoidCaptureMove(ChessBoard &board) const{
	shared_ptr<const ChessMove> bestSave{nullptr};
	int saveVal = 1;

	const map<PieceType, vector<shared_ptr<Piece>>> &piecesMap = board.getPieces(getColour());
	for(auto &p : piecesMap){
		vector<shared_ptr<Piece>> pieces = p.second;
		for(auto piece : pieces){
			//check if in danger
			if(piece->getOpponentThreats().size() > 0){
				int pieceVal = piece->getValue();
				if(pieceVal > saveVal){
					const vector<shared_ptr<const ChessMove>> &legalMoves = piece->getLegalMoves();
					//add the moves that bring the piece to safety
					for(auto move : legalMoves){
						Location endLocation = move->getEndLocation();
						if(board.isLocationSafe(endLocation, getColour())){
							bestSave = move;
							saveVal = pieceVal;
							break;
						}
					}
				}
			}
		}

	}
	return bestSave;
}

shared_ptr<const ChessMove> ComputerPlayer::getBestCaptureMove(ChessBoard &board) const{
	vector<shared_ptr<const ChessMove>> moves;
	shared_ptr<const ChessMove> bestMove{nullptr};
	int maxVal = 1;
	const vector<shared_ptr<const ChessMove>> &legalMoves = board.getLegalMoves(getColour());
	//iterate through moves and see which ones end up in a square occupied
	//by an enemy piece
	for(auto move : legalMoves){
		Location endLocation = move->getEndLocation();
		shared_ptr<Piece> pieceAtEnd = board.getPieceAt(endLocation);
		if(pieceAtEnd->getValue() > maxVal) bestMove = move;
	}
	return bestMove;
}




