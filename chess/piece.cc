#include <iostream>
#include "piece.h"
#include "chessboard.h"
#include "location.h"
#include "king.h"
using namespace std;

Piece::~Piece(){
	cout << "CALLING DESTRUCTOR ON: " << location.col << "/" << location.row << endl;
}

Piece::Piece(PieceType type, Colour colour, int value, bool isDiag, bool isStraigt): 
	type{type}, colour{colour}, value{value}, isDiagonal{isDiag}, isStraight{isStraight} {}

Colour Piece::getColour() const{
	return colour;
}

PieceType Piece::getType() const{
	return type;
}

int Piece::getValue() const{
	return value;
}

int &Piece::getMoveCount(){
	return moveCount;
}

Location Piece::getLocation() const{
	return location;
}

void Piece::setLocation(const Location otherLocation){
	location = otherLocation;
}

/*void Piece::removeReachablePiece(shared_ptr<Piece> rmPiece){
	for(auto it = reachablePieces.begin(); it != reachablePieces.end(); ++it){
		if(*it == rmPiece){
			*(*it) = make_shared<EmptyPiece>();
			break;
		}
	}
}

void Piece::removeThreat(shared_ptr<Piece> threat){
	for(auto it = threats.begin(); it != threats.end(); ++it){
		if(*it == threat){
			threats.erase(it);
			break;
		}
	}
}

const vector<shared_ptr<Piece>> &Piece::getReachablePieces() const{
	return reachablePieces;
}

void Piece::clearReachablePieces(){
	reachablePieces.clear();
}

void Piece::addReachablePiece(shared_ptr<Piece> square){
	reachablePieces.emplace_back(square);
	square->addThreat(shared_ptr<Piece>{this});
}
*/
void Piece::clearLegalMoves(){
	legalMoves.clear();
}
void Piece::clearThreats(){
	threats.clear();
}

void Piece::addThreat(shared_ptr<Piece> threat){
	threats.emplace_back(threat);
}

const vector<shared_ptr<Piece> > &Piece::getThreats() const{
	return threats;
}

bool Piece::isEmpty() const{
	return type == PieceType::EMPTY_PIECE;
}
bool Piece::isDiagonalMover() const{
	return isDiagonal;
}
bool Piece::isStraightMover() const{
	return isStraight;
}

bool Piece::operator==(const Piece &other) const{
	return (colour == other.colour) && (type == other.type) && (location == other.location);
}

void Piece::notify(ChessBoard &board){
	clearThreats();
	cout << "NOTIFYING COL/ROW: " << location.col << "/" << location.row << endl;
	updateLegalMoves(board);
	cout << "LEGAL MOVES: " << legalMoves.size() << endl;
	//add this pieces legal moves to the board's legal moves
	vector<shared_ptr<const ChessMove>> boardLegalMoves = board.getLegalMoves(colour);
	boardLegalMoves.insert(boardLegalMoves.end(), legalMoves.begin(), legalMoves.end());

}

const vector<shared_ptr<const ChessMove>> &Piece::getLegalMoves() const{
	return legalMoves;
}

bool Piece::isBlockingCheck(ChessBoard &board) const{
	Location kingLocation = board.getKing(colour)->getLocation();
	//if theres no piece between this and its king, check if there is a queen/rook/bishop
	//that is along the line 
	if(location.isInLine(kingLocation)){
		//get relative direction 
		Location lineDirection = kingLocation.getRelativeDirection(location);
		
		//iterate along line to see if theres anypiece between this and the king
		//if a piece is found between them then this piece can move without worrying about 
		//opening a check
		Location currLocation = kingLocation + lineDirection;

		while(currLocation != location){
			if(board.getPieceAt(currLocation)->isEmpty()) return false;
			currLocation += lineDirection;
		}
		//if no piece was found between this and the king, continue along the line until
		//a piece is found or location is out of bounds
		currLocation += lineDirection;
		while(board.isInBounds(currLocation)){
			shared_ptr<Piece> currPiece = board.getPieceAt(currLocation);
			//non empty piece found: check if its a piece that can attack the king
			if(currPiece->isEmpty()){				
				if(currPiece->isStraightMover()){
					return (lineDirection.col * lineDirection.row) == 0; //not diagonal
				}else if(currPiece->isDiagonalMover()){
					return (lineDirection.col * lineDirection.row) != 0; //diagonal
				}else{
					return false;
				}
			}
		}
	}
	return false;
}

bool Piece::isMoveOk(ChessBoard &board, const Location newLocation) const{
	shared_ptr<King> king = board.getKing(colour);
	Location kingLocation = king->getLocation();
	bool isBlocking = isBlockingCheck(board);
	bool isInLine = location.getRelativeDirection(kingLocation) == newLocation.getRelativeDirection(kingLocation);
	bool isInBounds = board.isInBounds(newLocation);
	return (!isBlocking || isInLine) && isInBounds;
}
