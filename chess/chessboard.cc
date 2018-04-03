#include "chessboard.h"
#include "piece.h"
#include "king.h"
#include "standardmove.h"
#include "emptypiece.h"
#include "location.h"
#include "boardedit.h"
#include "chessmove.h"
#include "invalidmove.h"
using namespace std;

ChessBoard::~ChessBoard(){
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

void ChessBoard::notifyPieces(){
	legalMoves.clear();
	//clear all threats of pieces
	for(auto &pair : theBoard){
		pair.second->clearThreats();
	}
	for(auto &pair : theBoard){
		pair.second->notify(*this);
	}
	for(auto &p: piecesMap){
		//kings need to update their moves last so they can see all the squares in danger
		(static_pointer_cast<King>(getKing(p.first)))->kingNotify(*this);
	}
	filterCheckMoves();
}

vector<Colour> ChessBoard::getColours() const{
	vector<Colour> colours;
	for(auto &p : piecesMap){
		colours.emplace_back(p.first);
	}
	return colours;
}

map<Location, shared_ptr<Piece>> &ChessBoard::getBoard(){
	return theBoard;
}

const map<PieceType, vector<shared_ptr<Piece>>> &ChessBoard::getPieces(Colour colour){
	return piecesMap[colour]; 
}

shared_ptr<Piece> ChessBoard::getKing(Colour colour){
	vector<shared_ptr<Piece>> &pieceVec = piecesMap[colour][PieceType::KING];
	if(pieceVec.size() > 0){
		return pieceVec.front();
	}
	return make_shared<EmptyPiece>();
}
	
bool ChessBoard::isInBounds(const Location &location) const{
	return theBoard.find(location) != theBoard.end();
}

shared_ptr<Piece> ChessBoard::getPieceAt(const Location &location) const{
	auto it = theBoard.find(location);
	if(it != theBoard.end()) return it->second;
	return make_shared<EmptyPiece>();
}

vector<shared_ptr<const ChessMove>> &ChessBoard::getLegalMoves(Colour colour){
	return legalMoves[colour]; 
}

void ChessBoard::executeEdit(const BoardEdit &edit){
	edit.execute(*this);	
}

void ChessBoard::filterCheckMoves(){
	vector<Colour> coloursInCheck;
	for(auto &p : legalMoves){
		if(isCheck(p.first)){
			coloursInCheck.emplace_back(p.first);
		}
	}
	for(auto colour: coloursInCheck){
		shared_ptr<Piece> king = getKing(colour);
		Location kingLoc = king->getLocation();
		vector<shared_ptr<const ChessMove>> &questionMoves = getLegalMoves(colour);
		vector<shared_ptr<Piece>> threats = king->getOpponentThreats();
		//if the king is vulnerable from two locations, then the only option is to move
		//the king, so remove all other moves
		if(threats.size() > 1){
			auto it = questionMoves.begin();
			while(it != questionMoves.end()){
				if(kingLoc != (*it)->getStartLocation()){
					it = questionMoves.erase(it);
				}else{
					++it;
				}
			}
		}else{
			shared_ptr<Piece> threat = threats.front();
			Location threatLoc = threat->getLocation();
			//if threat moves straight or diagonal, then option is block
			//otherwise, need to capture piece
			if(threat->isDiagonalMover() || threat->isStraightMover()){
				auto it = questionMoves.begin();
				while(it != questionMoves.end()){
					// if the king is moving then it is ok
					// if the piece is moving to a location between threat and king then it is ok
					Location startLoc = (*it)->getStartLocation();
					Location newLoc = (*it)->getEndLocation();
					if((startLoc != kingLoc) && (!newLoc.isBetween(kingLoc, threatLoc)) && (newLoc != threatLoc)){
						it = questionMoves.erase(it);
					}else{
						++it;
					}
				}
			}else{
				auto it = questionMoves.begin();
				while(it != questionMoves.end()){
					Location newLoc = (*it)->getEndLocation();
					if(newLoc != threatLoc){
						it = questionMoves.erase(it);
					}else{
						++it;
					}
				}
			}

		}
	}
}

void ChessBoard::executeMove(Colour colour, const Location &start, const Location &end){
	vector<shared_ptr<const ChessMove>> &legals = getLegalMoves(colour);
	for(auto move : legals){
		if((start == move->getStartLocation()) && (end == move->getEndLocation())){
			executeChessMove(move);
			return;
		}
	}
	//filter legal moves if any of the players are in check
	throw InvalidMove{};
}


void ChessBoard::executeChessMove(const shared_ptr<const ChessMove> move){
	//execute the move, then notify displays, then add this to the stack
	move->execute(*this);
	executedMoves.push(move);
	notifyPieces();
}

void ChessBoard::undo(){
	if(executedMoves.size() > 0){
		//execute opposite of last move, then remove from moves stack
		const shared_ptr<const ChessMove> move = executedMoves.top();
		move->executeReverse(*this);
		executedMoves.pop();
		notifyPieces();
	}
}

bool ChessBoard::isLocationSafe(const Location &location, Colour colour) const{
	const vector<shared_ptr<Piece>> threats = getPieceAt(location)->getThreats();
	for(auto piece : threats){
		if(piece->getColour() != colour) return false;
	}
	return true;
}

bool ChessBoard::isCheck(Colour turn){
	shared_ptr<Piece> king = getKing(turn);
	return king->getOpponentThreats().size() > 0;
}


bool ChessBoard::isStalemate(Colour turn){
	return (legalMoves.find(turn)->second).size() == 0;
}

bool ChessBoard::isCheckmate(Colour turn){
	return isCheck(turn) && isStalemate(turn);
}



