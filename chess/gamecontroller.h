#ifndef GAME_CONTROLLER_H
#define GAME_CONTOLLER_H

#include <iostream>
#include <memory>
#include <stdlib>

class Player;
class ChessBoard;

class GameController{
	std::istream &in;
	std::ostream &out;
	std::vector<std::unique_ptr<Player>> players;
	std::unique_ptr<ChessBoard> board;
	int turn;
	int playerCount; //amount of players
	
	//reset() clears players and sets turn and playerCount to 0
	void reset();
	int nextTurn(); //changes turn
	void setTurn(Colour); //sets turn to colour or does nothing if colour DNE
	
	//setupMode() enters setup mode for the board and reads input for commands
	void setupMode();
	
	//runGame() will run the game until any of checkmate, stalemate, or resign is encountered
	void runGame(); 

	//startGame() will put the board into setup mode, then run the game
	void startGame(); 

	public:
	GameController(std::istream &in, std::ostream &out);
	//this is used to start reading commands from the input stream
	//once the player starts the game, startGame will be called
	void init();
};


#endif
