#include "gamecontroller.h"
#include "classicchessboard.h"
#include "piecefactory"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "piecemove.h"
#include "colours.h"
#include "humanplayer.h"
#include "computerplayer.h"

using namespace std;

GameController::GameController(istream &in, ostream &out): in{in}, out{out} {}

void GameController::reset(){
	turn = 0;
	playerCount = 0;
	players.clear();
}

int GameController::nextTurn(){
	turn = (++turn) % playerCount;
	return turn;
}

void GameController::setTurn(Colour colour){
	for(int i = 0; i < playerCount; ++i){
		if(players[i]->getColour() == colour){
			turn = i;
			break;
		}
	}
}

void GameController::setupMode(){
	string cmd;
	while(in >> cmd){
		if(cmd == "done"){
			break;
		//add a piece
		}else if(cmd == "+"){
			char pieceChar;
			string locationStr;
			//get the piece type and location, then execute
			if((in >> pieceChar) && (in >> location)){
				shared_ptr<Piece> piece = make_shared<Piece>{PieceFactory::generatePiece(pieceChar)};
				Location location = Location{locationStr};
				board->executeEdit(PieceAdd{location, piece});
			}
		//remove a piece
		}else if(cmd == "-"){
			string locationStr;
			//get location then execute command to remove
			if(in >> locationStr){
				Location location{locationStr};
				shared_ptr<Piece> piece = board->getPieceAt(location);
				board->executeEdit(PieceRemove{piece});
			}
		}else if(cmd == "="){
			string colourStr;
			if(in >> colourStr){
				Colour colour = Colour::parse(colour);
				setTurn(colour);
			}
		}
	}
}

void GameController::runGame(){
	Colour winner = Colour::NO_COLOUR;
	string cmd;
	while(in >> cmd){
		Player currentPlayer = players[turn];
		if(board->isCheckMate(currentPlayer.getColour())){
			winner = players[nextTurn()].getColour();
			out << "Checkmate! " << endl;
			break;
		}else if(board->isStaleMate(currentPlayer.getColour())){
			out << "Stalemate!" << endl;
			break;
		}
		if(cmd == "move"){
			try{
				shared_ptr<PieceMove> move = currentPlayer->getMove();
				board->executeChessMove(move);
				nextTurn();
			}catch(InvalidMove &e){
				out << e.getMessage() << endl;
			}
		}else if(cmd == "resign"){
			//the next player is displayed as the winner
			winner = players[nextTurn()]->getColour();
		}
	}
	if(winner != Colour::NO_COLOUR){
		out << colourToString() + " wins!" << endl;
	}
}

void GameController::startGame(){
	bool gameRunning = false;
	string cmd;
	while(in >> cmd){
		if((cmd == "setup") and !gameRunning){
			setupMode(); //runs until user inputs 'done'
		}else if(cmd == move){
			gameRunning = true;
			runGame(); //runs until resign or winner/draw
			break;
		}
	}
}

void GameController::init(){
	string cmd;
	while(in >> cmd){
		reset();
		bool readPlayers = true; //set false if invalid initialization command
		if(cmd == "game"){
			//standard game
			playerCount = 2;
			Colour colours[2] = {Colour::WHITE, Colour::BLACK};
			board = unique_ptr<ChessBoard>{new ClassicChessBoard};
			
			/* ---------------------------------------------------------------------------------------
			ADD DISPLAYS HERE
			unique_ptr<GraphicDisplay>
			board->attachObserver()

			-------------------------------------------------------------------------------*/
		}else{
			readPlayers = false
		}
		if(readPlayers){
			// add players until count is met
			int addedPlayers = 0;
			string player;
			while((in >> player) && addedPlayers < playerCount){
				//check human player
				if(player == "human"){
					players.emplace_back(unique_ptr<Player>{new HumanPlayer{in, colours[addedPlayers]}}
					++addedPlayers;
				//check computer player
				}else if((player.len() == 10) && (player.substr(0, 8) == "computer")){
					string levelStr = player[9];
					istringstream iss{levelstr};
					int level;
					if(iss >> level){
						players.emplace_back(unique_ptr<Player>{new ComputerPlayer{board, level, colours[addedPlayers]}};
						++addedPlayers;
					}else{
						break;
					}
				}else{
					//if invalid player input, then user has to type "game..." again
					break;
				}
			}
		}
		if(addedPlayers = playerCount){
			startGame();
			reset();
		}
	}
}
