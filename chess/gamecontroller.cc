#include "gamecontroller.h"
#include "classicchessboard.h"
#include "piecefactory.h"
#include "piece.h"
#include "location.h"
#include "pieceadd.h"
#include "pieceremove.h"
#include "chessmove.h"
#include "invalidmove.h"
#include "colour.h"
#include "player.h"
#include "humanplayer.h"
//#include "computerplayer.h"
#include "textdisplay.h"
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
		try{
			if(cmd == "done"){
				break;
			//add a piece
			}else if(cmd == "+"){
				char pieceChar;
				string locationStr;
				//get the piece type and location, then execute
				if((in >> pieceChar) && (in >> locationStr)){
					shared_ptr<Piece> piece = PieceFactory::generatePiece(pieceChar);
					Location location = Location{locationStr};
					board->executeEdit(PieceAdd{piece, location});
					board->attachObserver(piece);
					board->notifyObservers();
				}
			//remove a piece
			}else if(cmd == "-"){
				string locationStr;
				//get location then execute command to remove
				if(in >> locationStr){
					Location location{locationStr};
					shared_ptr<Piece> piece = board->getPieceAt(location);
					board->executeEdit(PieceRemove{piece});
					board->detachObserver(piece);
					board->notifyObservers();
				}
			}else if(cmd == "="){
				string colourStr;
				if(in >> colourStr){
					if(colourStr == "black") setTurn(Colour::WHITE);
					if(colourStr == "white") setTurn(Colour::BLACK);
				}
			}
		}catch(...){
			out << "Invalid" << endl;
		}
	}
}

void GameController::runGame(){
	Colour winner = Colour::NO_COLOUR;
	string cmd = "move";
	do{
		unique_ptr<Player> &currentPlayer = players[turn];
		if(board->isCheckmate(currentPlayer->getColour())){
			winner = players[nextTurn()]->getColour();
			out << "Checkmate! " << endl;
			break;
		}else if(board->isStalemate(currentPlayer->getColour())){
			out << "Stalemate!" << endl;
			break;
		}
		if(cmd == "move"){
			try{
				currentPlayer->play(*board);
				nextTurn();
			}catch(InvalidMove &e){
				out << e.what() << endl;
			}catch(InvalidLocation &e){
				out << e.what() <<endl;
			}
		}else if(cmd == "resign"){
			//the next player is displayed as the winner
			winner = players[nextTurn()]->getColour();
		}
	}while(in >> cmd);

	if(winner != Colour::NO_COLOUR){
		if(winner == Colour::WHITE){
			out << "Black" << endl;
		}else if(winner == Colour::BLACK){
			out << "white" << endl;
		}
		out << " wins!" << endl;
	}
}

void GameController::startGame(){
	board->notifyObservers();
	bool gameRunning = false;
	string cmd;
	while(in >> cmd){
		if((cmd == "setup") and !gameRunning){
			setupMode(); //runs until user inputs 'done'
		}else if(cmd == "move"){
			gameRunning = true;
			runGame(); //runs until resign or winner/draw
			break;
		}
	}
}

void GameController::init(){
	string cmd;
	while(in >> cmd){
		int addedPlayers;
		int playerCount;
		vector<Colour> colours;
		reset();
		bool readPlayers = true; //set false if invalid initialization command
		if(cmd == "game"){
			//standard game
			playerCount = 2;
			colours = {Colour::WHITE, Colour::BLACK};
			board = make_unique<ClassicChessBoard>();
		
			//ADD DISPLAYS
			shared_ptr<TextDisplay> textDisplay = make_shared<TextDisplay>(*board, out);
			board->attachObserver(textDisplay);
		}else{
			readPlayers = false;
		}
		if(readPlayers){
			// add players until count is met
			addedPlayers = 0;
			string player;
			while((addedPlayers < playerCount) && (in >> player)){
				//check human player
				if(player == "human"){
					players.emplace_back(make_unique<HumanPlayer>(colours[addedPlayers], in));
					++addedPlayers;
				//check computer player
				/*}else if((player.len() == 10) && (player.substr(0, 8) == "computer")){
					string levelStr = player[9];
					istringstream iss{levelstr};
					int level;
					if(iss >> level){
						players.emplace_back(unique_ptr<Player>{new ComputerPlayer{colours[addedPlayers], board, level}};
						++addedPlayers;
					}else{
						break;
					}
				*/}else{
					//if invalid player input, then user has to type "game..." again
					out << "Invalid player type" << endl;
					break;
				}
			}
		}
		if(readPlayers && (addedPlayers == playerCount)){
			startGame();
			reset();
		}
	}
}
