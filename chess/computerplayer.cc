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

const vector<shared_ptr<const ChessMove>> ComputerPlayer::getAllMoves(ChessBoard &board) const{
	return board.getLegalMoves(getColour());
}

const vector<shared_ptr<const ChessMove>> ComputerPlayer::getAvoidCaptureMoves(ChessBoard &board) const{
	vector<shared_ptr<const ChessMove>> moves;
	const map<PieceType, vector<shared_ptr<Piece>>> &piecesMap = board.getPieces(getColour());
	for(auto &p : piecesMap){
		vector<shared_ptr<Piece>> pieces = p.second;
		for(auto piece : pieces){
			//check if in danger
			if(piece->getOpponentThreats().size() > 0){
				const vector<shared_ptr<const ChessMove>> &legalMoves = piece->getLegalMoves();
				//add the moves that bring the piece to safety
				for(auto move : legalMoves){
					Location endLocation = move->getEndLocation();
					if(board.isLocationSafe(endLocation, getColour())){
						moves.emplace_back(move);
					}
				}
			}
		}

	}
	return moves;
}

const vector<shared_ptr<const ChessMove>> ComputerPlayer::getPreferCaptureMoves(ChessBoard &board) const{
	vector<shared_ptr<const ChessMove>> moves;
	Colour colour = getColour();
	vector<Colour> opponentColours = board.getColours();//for purpose of finding checks

	const vector<shared_ptr<const ChessMove>> &legalMoves = board.getLegalMoves(colour);
	//iterate through moves and see which ones end up in a square occupied
	//by an enemy piece
	for(auto move : legalMoves){
		Location endLocation = move->getEndLocation();
		shared_ptr<Piece> pieceAtEnd = board.getPieceAt(endLocation);
		if(pieceAtEnd->getColour() != colour){
			moves.emplace_back(move);
		}else{
			//check for check
			board.executeChessMove(move);
			for(auto oppColour : opponentColours){
				if(board.isCheck(oppColour)){
					moves.emplace_back(move);
					board.undo();
				}
			}
		}
	}

	return moves;
}




