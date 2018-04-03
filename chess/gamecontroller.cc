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
#include "leveloneplayer.h"
#include "leveltwoplayer.h"
#include "levelthreeplayer.h"
#include "levelfourplayer.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <sstream>
using namespace std;

GameController::GameController(istream &in, ostream &out): in{in}, out{out} {}

void GameController::reset(){
	turn = 0;
	playerCount = 0;
	players.clear();
	displays.clear();
}

int GameController::nextTurn(){
	if(playerCount != 0){
		++turn;
		turn = turn%playerCount;
	}
	return turn;
}

int GameController::prevTurn(){
	if(playerCount != 0){
		--turn;
		turn += playerCount; //avoid neg
		turn = turn%playerCount;
	}
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

void GameController::updateDisplays() const{
	for(auto &display : displays){
		display->updateDisplay(*board);
	}
}

void GameController::setupMode(){
	string cmd;
	while(in >> cmd){
		try{
			if(cmd == "done"){
				board->notifyPieces();
				bool validBoardSetup = true;
				//check king count + check
				for(auto &player : players){
					Colour colour = player->getColour();
					vector<shared_ptr<Piece>> kings = (board->getPieces(colour).find(PieceType::KING))->second;
					if(kings.size() != 1){
						out << "Invalid King count" << endl;
						validBoardSetup = false;
						break;
					}else if(board->isCheck(colour)){
						out << "King is in check" << endl;
						validBoardSetup = false;
						break;
					}else{
						vector<shared_ptr<Piece>> pawns	= board->getPieces(colour).find(PieceType::PAWN)->second;
						for(auto pawn : pawns){
							Location pawnLoc = pawn->getLocation();
							if(!(board->isInBounds(pawnLoc + Location{0,1}) && board->isInBounds(pawnLoc - Location{0,1}))){
								out << "Pawns can't be at end" << endl;
								validBoardSetup = false;
								break;	
							}
						}
					}
				}
				if(validBoardSetup) break;
			//add a piece
			}else if(cmd == "+"){
				char pieceChar;
				string locationStr;
				//get the piece type and location, then execute
				if((in >> pieceChar) && (in >> locationStr)){
					shared_ptr<Piece> piece = PieceFactory::generatePiece(pieceChar);
					if(!piece->isEmpty()){
						Location location = Location{locationStr};
						board->executeEdit(PieceAdd{piece, location});
						updateDisplays();
					}
				}
			//remove a piece
			}else if(cmd == "-"){
				string locationStr;
				//get location then execute command to remove
				if(in >> locationStr){
					Location location{locationStr};
					shared_ptr<Piece> piece = board->getPieceAt(location);
					board->executeEdit(PieceRemove{piece, location});
					updateDisplays();
				}
			}else if(cmd == "="){
				string colourStr;
				if(in >> colourStr){
					if(colourStr == "black") setTurn(Colour::BLACK);
					if(colourStr == "white") setTurn(Colour::WHITE);
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
	board->notifyPieces();
	do{
		unique_ptr<Player> &currentPlayer = players[turn];
		if(cmd == "move"){
			try{
				currentPlayer->play(*board);
				updateDisplays();
				nextTurn();
			}catch(InvalidMove &e){
				out << e.what() << endl;
			}catch(InvalidLocation &e){
				out << e.what() <<endl;
			}
		}else if(cmd == "undo"){
			board->undo();
			updateDisplays();
			prevTurn();
		}else if(cmd == "resign"){
			//the next player is displayed as the winner
			winner = players[nextTurn()]->getColour();
			break;
		}
		Colour nextPlayerColour = players[turn]->getColour();
		if(board->isCheckmate(nextPlayerColour)){
			winner = currentPlayer->getColour();
			out << "Checkmate! " << endl;
			break;
		}else if(board->isStalemate(nextPlayerColour)){
			out << "Stalemate!" << endl;
			winner = Colour::NO_COLOUR;
			break;
		}
	}while(in >> cmd);

	if(winner != Colour::NO_COLOUR){
		if(winner == Colour::WHITE){
			out << "White";
		}else if(winner == Colour::BLACK){
			out << "Black";
		}
		out << " wins!" << endl;
		scoreBoard[winner] += 1; 
	}else{
		for(auto &player : players){
			scoreBoard[player->getColour()] += 0.5;
		}
	}
}

void GameController::startGame(){
	updateDisplays();
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
		playerCount = 0;
		vector<Colour> colours;
		reset();
		bool readPlayers = true; //set false if invalid initialization command
		if(cmd == "game"){
			//standard game
			playerCount = 2;
			colours = {Colour::WHITE, Colour::BLACK};
			board = make_unique<ClassicChessBoard>();
		
			//ADD DISPLAYS
			displays.emplace_back(make_unique<TextDisplay>(*board, out));
			displays.emplace_back(make_unique<GraphicsDisplay>(*board));
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
				}else if((player.length() >= 10) && (player.substr(0, 8) == "computer")){
					char levelStr = player[9];
					int level = levelStr - '0';
					if(level > 0){
						Colour colour = colours[addedPlayers];
						unique_ptr<Player> newPlayer;
						if(level == 1){
							newPlayer = make_unique<LevelOnePlayer>(colour);
						}else if(level == 2){
							newPlayer = make_unique<LevelTwoPlayer>(colour);
						}else if(level == 3){
							newPlayer = make_unique<LevelThreePlayer>(colour);
						}else{
							newPlayer = make_unique<LevelFourPlayer>(colour);
						}
						players.emplace_back(move(newPlayer));
						++addedPlayers;
					}else{
						break;
					}
				}else{
					//if invalid player input, then user has to type "game..." again
					out << "Invalid player type" << endl;
					break;
				}
			}
		}
		if(readPlayers && (addedPlayers == playerCount)){
			for(auto &player : players){
				scoreBoard[player->getColour()];
			}
			startGame();
		 	displays.clear();
		}
	}
	out << "Final Score:"<< endl;
	for(auto &pair : scoreBoard){
		string colour = (pair.first == Colour::BLACK) ? "Black" : "White";
		out << colour << ": " << pair.second << endl;
	}
	reset();
}
