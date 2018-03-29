#include "location.h"
using namespace std;

const char* InvalidLocationException::what(){
	return message; 
}

Location::Location(string loc){
	try{
		col = loc[0];
		row = loc[1];
	}catch(...){
		throw InvalidLocationException;
	}
}

bool Location::isInLine(const Location &location) const{
	int colDiff = col - location.col;
	int rowDiff = row - location.row;
	
	//returns true if diagonal, or horizontal, or vertical
	return (col == 0) || (row == 0) || (row == col);
}
