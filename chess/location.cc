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

Location::Location(int col, int row): col{col}, row{row}{}
Location::Location(const Location &other): col{other.col}, row{other.row}{}
Location &Location::operator=(const Location &other){
	col = other.col;
	row = other.row;
	return *this;
}

bool Location::isInLine(const Location &location) const{
	int colDiff = col - location.col;
	int rowDiff = row - location.row;
	
	//returns true if diagonal, or horizontal, or vertical
	return (col == 0) || (row == 0) || (row == col);
}

bool Location::operator==(const Location &other){
	return (col == other.col) && (row == other.row);
}

Location &&Location::operator+(const Location &other){
	return Location{col + other.col, row + other.row};
}

Location &&Location::operator-(const Location &other){
	return Location{col - other.col, row - other.row};
}

Location &Location::operator+=(const Location &other){
	*this = *this + other;
	return *this;
}

Location &Location::operator-=(const Location &other){
	*this = *this - other;
	return *this;
}
