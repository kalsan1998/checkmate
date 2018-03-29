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
	Location(int col, int row);
	Location(const Location &other);
	Location &operator=(const Location &other);

	//returns true if this is directly horizontal/vertical/diagonal to the other location
	bool isInLine(const Location &location) const;

	bool operator==(const Location &other);
	bool operator+(const Location &other);
	bool operator-(const Location &other);
	bool operator+=(const Location &other);
	bool operator-=(const Location &other);
};
#endif
