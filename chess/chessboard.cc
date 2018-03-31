#include "chessboard.h"
#include "boardobserver.h"
#include "piece.h"
#include "king.h"
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

const map<Location, shared_ptr<Piece>> &ChessBoard::getBoard() const{
	return theBoard;
}

const map<PieceType, shared_ptr<Piece>> &ChessBoard::getPieces(Colour colour) const{
	return piecesMap[colour]; 
}

const King &ChessBoard::getKing(const Colour colour) const{
	return piecesMap[colour][PieceType::KING];
}
	
bool ChessBoard::isInBounds(const Location &location) const{
	return theBoard.count(location) == 1;
}

shared_ptr<Piece> ChessBoard::getPieceAt(const Location &location) const{
	return theBoard[location];
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
		//clear all threats of pieces
		for(auto &pair : theBoard){
			pair.second->clearThreats();
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

bool ChessBoard::isStalemate(const Colour turn){
	return getLegalMoves(turn).size() == 0;
}

bool ChessBoard::isCheckmate(const Colour turn){
	shared_ptr<King> king = piecesMap[turn][PieceType::KING].front();
	if(king->getThreats() > 0){
		if(isStalemate(turn)){
			return true;
		}
	}
	return false;
}



