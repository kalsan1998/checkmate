#include "location.h"
#include <limits.h>
using namespace std;

string InvalidLocationException::what() const{
	return message; 
}

Location::Location(string loc){
	try{
		col = static_cast<int>(loc[0]);
		row = loc[1];
	}catch(...){
		throw InvalidLocationException{};
	}
}

Location::Location(): col{INT_MAX}, row{INT_MAX}{} 
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
	return (colDiff == 0) || (rowDiff == 0) || (rowDiff == col);
}

bool Location::operator<(const Location &other) const{
	if(col < other.col) return true;
	if(col > other.col) return false;
	return (row < other.row);
}

bool Location::operator==(const Location &other) const{
	return (col == other.col) && (row == other.row);
}

bool Location::operator!=(const Location &other) const{
	return (col != other.col) || (row != other.row);
}

Location &&Location::operator+(const Location &other) const{
	return move(Location{col + other.col, row + other.row});
}

Location &&Location::operator-(const Location &other) const{
	return move(Location{col - other.col, row - other.row});
}

Location &Location::operator+=(const Location &other){
	*this = *this + other;
	return *this;
}

Location &Location::operator-=(const Location &other){
	*this = *this - other;
	return *this;
}
