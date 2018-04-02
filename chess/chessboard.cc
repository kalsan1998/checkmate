#include "chessboard.h"
#include "boardobserver.h"
#include "piece.h"
#include "king.h"
#include "standardmove.h"
#include "emptypiece.h"
#include "location.h"
#include "boardedit.h"
#include "chessmove.h"
#include "invalidmove.h"

#include <iostream>

using namespace std;

ChessBoard::~ChessBoard(){
	cout << "BOARD DESTROYED" << endl;
	legalMoves.clear();

	for(auto &pair : theBoard){
		pair.second->clearThreats();
		pair.second->clearLegalMoves();
	}
}
const shared_ptr<const ChessMove> ChessBoard::getLastMove() const{
	if(executedMoves.size() != 0) return executedMoves.top();
	
	//return dummy move otherwise
	shared_ptr<Piece> empty = make_shared<EmptyPiece>();
	return make_shared<const StandardMove>(empty, empty->getLocation());
}

void ChessBoard::notifyObservers(){
	for(auto obs : observers){
		obs->notify(*this);
	}

	for(auto &p: piecesMap){
		//kings need to update their moves last so they can see all the squares in danger
		getKing(p.first)->kingNotify(*this);
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

map<Location, shared_ptr<Piece>> &ChessBoard::getBoard(){
	return theBoard;
}

const map<PieceType, vector<shared_ptr<Piece>>> &ChessBoard::getPieces(Colour colour){
	return piecesMap[colour]; 
}

shared_ptr<King> ChessBoard::getKing(Colour colour){
	vector<shared_ptr<Piece>> &pieceVec = piecesMap[colour][PieceType::KING];
	return static_pointer_cast<King>(pieceVec.front());
}
	
bool ChessBoard::isInBounds(const Location location) const{
	return theBoard.find(location) != theBoard.end();
}

shared_ptr<Piece> ChessBoard::getPieceAt(const Location location) const{
	auto it = theBoard.find(location);
	if(it != theBoard.end()) return it->second;
	return make_shared<EmptyPiece>();
}

vector<shared_ptr<const ChessMove>> &ChessBoard::getLegalMoves(Colour colour){
	cout << "LEGAL MOVES: " << legalMoves[colour].size() << endl;
	return legalMoves[colour]; 
}

void ChessBoard::executeEdit(const BoardEdit &edit){
	edit.execute(*this);	
}

void ChessBoard::executeMove(Colour colour, const Location start, const Location end){
	vector<shared_ptr<const ChessMove>> legals = getLegalMoves(colour);
	for(auto move : legals){
			if((start == move->getStartLocation()) && (end == move->getEndLocation())){
				executeChessMove(move);
				return;
			}
	}
	throw InvalidMove{};
}


void ChessBoard::executeChessMove(const shared_ptr<const ChessMove> move){
	//execute the move, then notify observers, then add this to the stack
	move->execute(*this);
	//clear all legal moves
	for(auto &pair : legalMoves){
		pair.second.clear();
	}
	//clear all threats of pieces
	for(auto &pair : theBoard){
		pair.second->clearThreats();
	}
	notifyObservers();
	executedMoves.push(move);
}

void ChessBoard::undo(){
	//execute opposite of last move, then remove from moves stack
	const shared_ptr<const ChessMove> move = executedMoves.top();
	move->executeReverse(*this);
	executedMoves.pop();
	notifyObservers();
}

bool ChessBoard::isLocationSafe(const Location location, Colour colour) const{
	const vector<shared_ptr<Piece>> threats = getPieceAt(location)->getThreats();
	for(auto piece : threats){
		if(piece->getColour() != colour) return true;
	}
	return false;
}

bool ChessBoard::isCheck(Colour turn){
	shared_ptr<King> king = getKing(turn);
	return isLocationSafe(king->getLocation(), turn);
}

bool ChessBoard::isStalemate(Colour turn){
	return (legalMoves.find(turn)->second).size() == 0;
}

bool ChessBoard::isCheckmate(Colour turn){
	return isCheck(turn) && isStalemate(turn);
}



