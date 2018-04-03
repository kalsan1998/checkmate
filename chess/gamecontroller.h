#ifndef GAME_CONTROLLER_H
#define GAME_CONTOLLER_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "player.h"
#include "colour.h"
#include "chessboard.h"
#include "boarddisplay.h"


class GameController{
	std::istream &in;
	std::ostream &out;
	std::vector<std::unique_ptr<Player>> players;
	std::vector<std::unique_ptr<BoardDisplay>> displays;
	std::map<Colour, long> scoreBoard;
	std::unique_ptr<ChessBoard> board;
	int turn;
	int playerCount; //amount of players
	
	void updateDisplays() const;

	//reset() clears players and sets turn and playerCount to 0
	void reset();
	int nextTurn(); //changes turn
	int prevTurn(); //changes turn
	void setTurn(Colour colour); //sets turn to colour or does nothing if colour DNE
	
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
