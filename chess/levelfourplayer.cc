#include "levelfourplayer.h"
#include "levelthreeplayer.h"
#include <vector>
#include "chessboard.h"
#include "chessmove.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

LevelFourPlayer::LevelFourPlayer(Colour colour): ComputerPlayer{colour}, levelThree{make_shared<LevelThreePlayer>(colour)}{}

void LevelFourPlayer::play(ChessBoard &board) const{
	const vector<shared_ptr<const ChessMove>> captureMoves = getPreferCaptureMoves(board);
	const vector<shared_ptr<const ChessMove>> avoidMoves = getAvoidCaptureMoves(board);
	vector<shared_ptr<const ChessMove>> moves;
	//try to find moves in both categories
	for(auto move1 : captureMoves){
		for(auto move2 : avoidMoves){
			if(move1 == move2){
				moves.emplace_back(move1);
				break;
			}
		}
	}
	int size = moves.size();
	if(size > 0){
		int randomMove = rand() % size;
		board.executeChessMove(moves[randomMove]);
	}else{
		levelThree->play(board);
	}
}

