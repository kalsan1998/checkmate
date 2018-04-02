#include "location.h"
#include <limits.h>
#include <vector>
using namespace std;

string InvalidLocation::what() const{
	return message; 
}

Location::Location(string loc){
	try{
		col = static_cast<int>(loc[0]);
		row = loc[1];
	}catch(...){
		throw InvalidLocation{};
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
	return (colDiff == 0) || (rowDiff == 0) || (rowDiff == colDiff);
}

Location Location::getRelativeDirection(const Location &other) const{
	int vertDir = other.row == row ? 0 : 1;
	vertDir *= row < other.row  ? -1 : 1;
	int horzDir = other.col == col ? 0 : 1;
	horzDir *= col < other.col  ? -1 : 1;
	
	return Location{vertDir, horzDir};
}

bool Location::operator<(const Location &other) const{
	vector<int> locVec = {row, col};
	vector<int> otherLocVec = {other.row, other.col};
	return locVec < otherLocVec; //use vector operator for simplicity
}

bool Location::operator==(const Location &other) const{
	return (col == other.col) && (row == other.row);
}

bool Location::operator!=(const Location &other) const{
	return (col != other.col) || (row != other.row);
}

Location Location::operator+(const Location &other) const{
	return Location{col + other.col, row + other.row};
}

Location Location::operator-(const Location &other) const{
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
