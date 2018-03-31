#include "piece.h"
#include "chessboard.h"
#include "location.h"
#include "king.h"
using namespace std;

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

int &getMoveCount() const{
	return moveCount;
}

Location Piece::getLocation() const{
	return location;
}

void Piece::setLocation(const Location &otherLocation){
	location = otherLocation;
	++moveCount;
}

vector<shared_ptr<Piece>> &Piece::getMoveableSquares() const{
	return moveableSquares;
}

void Piece::clearMoveableSquares{
	moveableSquares.clear();
}

void Piece::addMoveableSquare(shared_ptr<Piece> square){
	moveableSquares.emplace_back(square);
	square->addThreat(make_shared<Piece>(this));
}

void Piece::clearThreats(){
	threats.clear();
}

void Piece::addThreat(shared_ptr<Piece> threat){
	threats.emplace_back(threat);
}

const vector<shared_ptr<Piece>> &getThreats() const{
	return threats;
}

bool Piece::isEmpty() const{
	return type != PieceType::EMPTY_PIECE;
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
	legalMoves.insert(legalMoves.end(), legalMoves.begin(), legalMoves.end()); 
}

const vector<shared_ptr<const ChessMove>> &Piece::getLegalMoves() const{
	return legalMoves;
}

bool Piece::isBlockingCheck(const ChessBoard &board) const{
	Location kingLocation = board.getKing(colour).getLocation();
	//if theres no piece between this and its king, check if there is a queen/rook/bishop
	//that is along the line 
	if(location.isInLine(kingLocation)){
		//get relative direction 
		int vertDir = kingLocation.row == location.row ? 0 : 1;
		vertDir *= location.row < kingLocation.row  ? -1 : 1;
		int horzDir = kingLocation.col == location.col ? 0 : 1;
		horzDir *= location.col < kingLocation.col  ? -1 : 1;
		
		Location lineDirection{horzDir, vertDir};
		//iterate along line to see if theres anypiece between this and the king
		//if a piece is found between them then this piece can move without worrying about 
		//opening a check
		int horz = kingLocation.col + horzDir;
		int vert = kingLocation.row + vertDir;
		Location currLocation{horz, vert};
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
					return (horzDir * vertDir) == 0; //not diagonal
				}else if(currPiece->isDiagonalMover()){
					return (horzDir * vertDir) != 0; //diagonal
				}else{
					return false;
				}
			}
		}
	}
	return false;
}

bool Piece::isMoveOk(const ChessBoard &board, const Location &location) const{
	return (!isBlockingCheck(board) || board.getKing(colour).getLocation().isInLine(location)) && board.isInBounds(location);
}
