#include "piece.h"
#include "chessboard.h"
#include "location.h"
#include "king.h"
#include <vector>
using namespace std;

Piece::~Piece(){}

Piece::Piece(PieceType type, Colour colour, string displaySymbol, int value, bool isDiag, bool isStraight): 
	type{type}, colour{colour}, displaySymbol{displaySymbol}, value{value}, isDiagonal{isDiag}, isStraight{isStraight} {}

Colour Piece::getColour() const{
	return colour;
}

PieceType Piece::getType() const{
	return type;
}

string Piece::getDisplaySymbol() const{
	return displaySymbol;
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

void Piece::clearLegalMoves(){
	legalMoves.clear();
}
void Piece::clearThreats(){
	threats.clear();
}

vector<shared_ptr<Piece>> Piece::getOpponentThreats() const{
	vector<shared_ptr<Piece>> opponentThreats;
	for(auto piece : threats){
		if(piece->colour != colour){
			opponentThreats.emplace_back(piece);
		}
	}
	return opponentThreats;
}

void Piece::addThreat(shared_ptr<Piece> threat){
	threats.emplace_back(threat);
}

const vector<shared_ptr<Piece>> &Piece::getThreats() const{
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
	updateLegalMoves(board);
	//add this pieces legal moves to the board's legal moves
	vector<shared_ptr<const ChessMove>> &boardLegalMoves = board.getLegalMoves(colour);
	for(auto move : legalMoves){
		boardLegalMoves.emplace_back(move);
	}

}

const vector<shared_ptr<const ChessMove>> &Piece::getLegalMoves() const{
	return legalMoves;
}

bool Piece::isBlockingCheck(ChessBoard &board) const{
	shared_ptr<Piece> king = board.getKing(colour);
	Location kingLocation = king->getLocation();
	if(location.isInLine(kingLocation)){
		//check if theres a piece between this and king
		Location direction = kingLocation.getRelativeDirection(location);
		Location currLocation = kingLocation + direction;
		while(currLocation != location){
			shared_ptr<Piece> piece = board.getPieceAt(currLocation);
			if(!piece->isEmpty()) return false;
			currLocation += direction;
		}
		currLocation += direction;
		//if theres nothing between this and king, see if a piece
		//is along the line in the other direction
		while(board.isInBounds(currLocation)){
			shared_ptr<Piece> piece = board.getPieceAt(currLocation);
			if(!piece->isEmpty()){
				if(piece->getColour() != colour){
					bool isStraightMove = piece->isStraightMover();
					bool isDiagMove = piece->isDiagonalMover();
					if(isStraightMove && isDiagMove) return true;
					if(isStraightMove){
						return (direction.col)*(direction.row) == 0; // means movement is straight
					}else if(isDiagMove){
						return (direction.col)*(direction.row) != 0;
					}else{
						return false;
					}
				}else{
					return false;
				}
			}
			currLocation += direction;
		}
	}
	return false;
}

bool Piece::isMoveOk(ChessBoard &board, const Location newLocation) const{
	shared_ptr<Piece> king = board.getKing(colour);
	Location kingLocation = king->getLocation();
	bool isBlocking = isBlockingCheck(board);
	bool isInLine = location.getRelativeDirection(kingLocation) == newLocation.getRelativeDirection(kingLocation);
	bool isInBounds = board.isInBounds(newLocation);
	return (!isBlocking || isInLine) && isInBounds;
}
