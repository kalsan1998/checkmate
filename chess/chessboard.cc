#include "chessboard.h"
#include "boardobserver.h"
#include "piece.h"
#include "king.h"
#include "location.h"
#include "boardedit.h"
#include "chessmove.h"
#include "invalidmove.h"
using namespace std;

ChessBoard::~ChessBoard(){}

bool ChessBoard::isMoveLegal(const ChessMove &move) const{
	for(auto &p : legalMoves){
		const vector<shared_ptr<const ChessMove>> &legalMovesVec = p.second;
		//iterate through legal moves until matching move is found
		for(auto legalMove : legalMovesVec){
			if(move == *legalMove) return true;
		}
	}
	return false;
}

shared_ptr<const ChessMove> ChessBoard::getLastMove() const{
	return executedMoves.top();
}

void ChessBoard::notifyObservers(){
	for(auto obs : observers){
		obs->notify(*this);
	}
	for(auto &p: piecesMap){
		//kings need to update their moves last so they can see all the squares in danger
		getKing(p.first).kingNotify(*this);
	}

}

void ChessBoard::attachObserver(shared_ptr<BoardObserver> obs){
	observers.emplace_back(obs);
}

void ChessBoard::detachObserver(shared_ptr<BoardObserver> obs){
	//iterate through observers until matching observer is found
	for(auto it = observers.begin(); it != observers.end(); ++it){
		if(obs == *it){
			observers.erase(it);
			break;
		}
	}
}

const map<Location, shared_ptr<Piece>> &ChessBoard::getBoard() const{
	return theBoard;
}

const map<PieceType, vector<shared_ptr<Piece>>> &ChessBoard::getPieces(Colour colour) const{
	return piecesMap.find(colour)->second; 
}

King &ChessBoard::getKing(Colour colour) const{
	return *(static_pointer_cast<King>(((getPieces(colour).find(PieceType::KING))->second).front()));
}
	
bool ChessBoard::isInBounds(const Location &location) const{
	return theBoard.count(location) == 1;
}

shared_ptr<Piece> ChessBoard::getPieceAt(const Location &location) const{
	return theBoard.find(location)->second;
}

vector<shared_ptr<const ChessMove>> &ChessBoard::getLegalMoves(Colour colour){
	return legalMoves.find(colour)->second; 
}

void ChessBoard::executeEdit(const BoardEdit &edit){
	edit.execute(*this);	
}

void ChessBoard::executeChessMove(const shared_ptr<const ChessMove> move){
	if(isMoveLegal(*move)){
		//execute the move, then notify observers, then add this to the stack
		move->execute(*this);
		//clear all legal moves
		for(auto &pair : legalMoves){
			pair.second.clear();
		}
		//clear all threats of pieces
		for(auto &pair : theBoard){
			pair.second->clearThreats();
			pair.second->clearReachablePieces();
		}
		notifyObservers();
		executedMoves.push(move);
	}else{
		throw InvalidMove{};
	}
}

void ChessBoard::undo(){
	//execute opposite of last move, then remove from moves stack
	const shared_ptr<const ChessMove> move = executedMoves.top();
	move->executeReverse(*this);
	executedMoves.pop();
	notifyObservers();
}

bool ChessBoard::isLocationSafe(const Location &location, Colour colour) const{
	const vector<shared_ptr<Piece>> &threats = getPieceAt(location)->getThreats();
	for(auto piece : threats){
		if(piece->getColour() != colour) return true;
	}
	return false;
}

bool ChessBoard::isCheck(Colour turn) const{
	King &king = getKing(turn);
	return isLocationSafe(king.getLocation(), turn);
}

bool ChessBoard::isStalemate(Colour turn) const{
	return (legalMoves.find(turn)->second).size() == 0;
}

bool ChessBoard::isCheckmate(Colour turn) const{
	return isCheck(turn) && isStalemate(turn);
}



