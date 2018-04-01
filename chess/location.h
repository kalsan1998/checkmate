#ifndef LOCATION_H
#define LOCATION_H

#include <stdexcept>

class InvalidLocation{
	std::string message = "Invalid location format";
	public:
	std::string what() const;
};

struct Location{
	int col;
	int row;
	Location();
	Location(std::string loc);
	Location(int col, int row);
	Location(const Location &other);
	Location &operator=(const Location &other);

	//returns true if this is directly horizontal/vertical/diagonal to the other location
	bool isInLine(const Location &location) const;
	//returns a 'unit location' in the direction from this to other
	Location getRelativeDirection(const Location &other) const;

	bool operator==(const Location &other) const;
	bool operator!=(const Location &other) const;
	bool operator<(const Location &other) const;
	Location &&operator+(const Location &other) const;
	Location &&operator-(const Location &other) const;
	Location &operator+=(const Location &other);
	Location &operator-=(const Location &other);
};
#endif
