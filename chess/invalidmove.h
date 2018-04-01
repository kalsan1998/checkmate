#ifndef INVALID_MOVE_H
#define INVALID_MOVE_H

#include <string>

class InvalidMove{
	std::string message = "Invalid move, try again";
	public:
	std::string what() const;
};

#endif
