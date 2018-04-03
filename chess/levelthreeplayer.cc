#include "levelthreeplayer.h"
#include "leveltwoplayer.h"
#include <vector>
#include "chessboard.h"
#include "chessmove.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

LevelThreePlayer::LevelThreePlayer(Colour colour): ComputerPlayer{colour}, levelTwo{make_shared<LevelTwoPlayer>(colour)}{}

void LevelThreePlayer::play(ChessBoard &board) const{
	const vector<shared_ptr<const ChessMove>> moves = getAvoidCaptureMoves(board);
	int size = moves.size();
	if(size > 0){
		int randomMove = rand() % size;
		board.executeChessMove(moves[randomMove]);
	}else{
		levelTwo->play(board);
	}
}

