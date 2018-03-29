#include "piece.h"
using namespace std;

Piece::Piece(PieceType type, Colour colour, int value): type{type}, colour{colour}, value{value}{}

Colour Piece::getColour const{
	return colour;
}

PieceType Piece::getType() const{
	return type;
}

int Piece::getValue() const{
	return value
}

Location Piece::getLocation() const{
	return location;
}

Location Piece::setLocation(Location otherLocation) const{
	location = otherLocation;
}

void Piece::notify(ChessBoard &board) override{
	//add this pieces legal moves to the board's legal moves
	vector<shared_ptr<ChessMove>> boardLegalMoves = board.getLegalMoves(colour);
	vector<shared_ptr<ChessMove>> legalMoves = getLegalMoves();
	legalMoves.insert(legalMoves.end(), legalMoves.start(), legalMoves.end()); 
}

bool Piece::isBlockingCheck(ChessBoard &board){
	Location kingLocation = board.getPieces(colour)[PieceType::KING].getLocation();
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
			if(board.getPieceAt(currLocation).getType() != PieceType::EMPTY_PIECE) return false;
			currLocation += lineDirection;
		}
		//if no piece was found between this and the king, continue along the line until
		//a piece is found or location is out of bounds
		currLocation{horz, vert} += lineDirection;
		while(board.isInBounds(currLocation){
			PieceType currType = board.getPieceAt(currLocation).getType();
			//non empty piece found: check if its a piece that can attack the king
			if(currType != PieceType::EMPTY_PIECE){
				if(type = PieceType::QUEEN){
					return true;
				}else if(type == PieceType::ROOK){
					return (horzDir * vertDir) == 0; //not diagonal
				}else if(type == PieceType::BISHOP){
					return (horzDir * vertDir) != 0; //diagonal
				}else{
					return false;
				}
			}
		}
	}
	return false;
}
