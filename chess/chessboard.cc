#include "chessboard.h"
#include "boardobserver.h"
#include "piece.h"
#include "location.h"
#include "boardedit.h"
#include "chessmove.h"
#include "invalidmove.h"
using namespace std;

ChessBoard::~ChessBoard{}

bool ChessBoard::isMoveLegal(const ChessMove &move) const{
	Colour colour = move.getColour();
	vector<shared_ptr<const ChessMove>> &legalMoves = getLegalMoves();
	//iterate through legal moves until matching move is found
	for(auto legalMove : legalMoves){
		if(move == *legalMove) return true;
	}
	return false;
}

shared_ptr<const ChessMove> ChessBoard::getLastMove() const{
	return executedMoves.top();
}

void ChessBoard::notifyObservers() const{
	for(auto obs : observers){
		obs->notify(*this);
	}
}

void ChessBoard::attachObserver(BoardObserver *obs){
	observers.emplace_back(obs);
	obs->notify(*this);
}

void ChessBoard::detachObserver(BoardObserver *obs){
	//iterate through observers until matching observer is found
	for(auto it = observers.begin(); it != obsservers.end(); ++it){
		if(obs == *it){
			observers.erase(it);
			break;
		}
	}
}

const map<Location, unique_ptr<Piece>> &getBoard() const{
	return theBoard;
}

bool ChessBoard::ChessBoard(const Location &location) const{
	return theBoard.find(location) != theBoard.end();
}

const Piece &ChessBoard::getPieceAt(const Location &location) const{
	return *(theBoard[location].get());
}

const vector<shared_ptr<ChessMove>> &ChessBoard::getLegalMoves(const Colour colour) const{
	return legalMoves[colour]; 
}

void ChessBoard::executeEdit(const BoardEdit &edit){
	edit.execute(*this);	
}

void ChessBoard::executeChessMove(const shared_ptr<const ChessMove> move){
	if(isMoveValid(*move)){
		//execute the move, then notify observers, then add this to the stack
		move->execute(*this);
		//clear all legal moves
		for(auto &pair : legalMoves){
			p.second.clear();
		}
		notifyObservers();
		executedMoves.push(move);
	}else{
		throw InvalidMove;
	}
}

void ChessBoard::undo(){
	//execute opposite of last move, then remove from moves stack
	const shared_ptr<const ChessMove> move = executedMoves.top();
	move->executeReverse(*this);
	executedMoves.pop();
	notifyObservers();
}

bool isStalemate(const Colour turn){
	return getLegalMoves(turn).size() == 0;
}

bool isCheckmate(const Colour turn){
	King *king = piecesMap.get(turn).get(PieceType::KING).front();
	if(king->getThreats() > 0){
		if(isStalemate(turn)){
			return true;
		}
	}
	return false;
}



