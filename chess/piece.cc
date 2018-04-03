#include "piece.h"
#include "chessboard.h"
#include "location.h"
#include "king.h"
#include <vector>
using namespace std;

Piece::~Piece(){}

Piece::Piece(PieceType type, Colour colour, string displaySymbol, int value, bool isDiag, bool isStraigt): 
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
	Location kingLocation = board.getKing(colour)->getLocation();
	//if theres no piece between this and its king, check if there is a queen/rook/bishop
	//that is along the line 
	if(location.isInLine(kingLocation)){
		//get relative direction 
		Location lineDirection = location.getRelativeDirection(kingLocation);
		
		//iterate along line to see if theres anypiece between this and the king
		//if a piece is found between them then this piece can move without worrying about 
		//opening a check
		Location currLocation = kingLocation - lineDirection;

		while((currLocation != location) && board.isInBounds(currLocation)){
			if(!board.getPieceAt(currLocation)->isEmpty()) return false;
			currLocation -= lineDirection;
		}
		//if no piece was found between this and the king, continue along the line until
		//a piece is found or location is out of bounds
		currLocation -= lineDirection;
		while(board.isInBounds(currLocation)){
			shared_ptr<Piece> currPiece = board.getPieceAt(currLocation);
			//non empty piece found: check if its a piece that can attack the king
			if(!currPiece->isEmpty()){
				if(currPiece->getColour() == colour) return false;
				if(currPiece->isStraightMover() && currPiece->isDiagonalMover()){
					return true; //cant move
				}else if(currPiece->isStraightMover()){
					return (lineDirection.col * lineDirection.row) == 0; //not diagonal
				}else if(currPiece->isDiagonalMover()){
					return (lineDirection.col * lineDirection.row) != 0; //diagonal
				}else{
					return false;
				}
			}
			currLocation -= lineDirection;
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
