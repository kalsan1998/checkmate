#ifndef LOCATION_H
#define LOCATION_H
#include<exception>
class InvalidLocationException: public Exception{
	string message = "Invalid location format";
	const char* what() const override;
}

struct Location{
	char col;
	int row;
	Location(string loc);
	//returns true if this is directly horizontal/vertical/diagonal to the other location
	bool isInLine(const Location &location) const;
};
#endif
