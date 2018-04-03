#include "leveltwoplayer.h"
#include "leveloneplayer.h"
#include "chessboard.h"
#include "chessmove.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

LevelTwoPlayer::LevelTwoPlayer(Colour colour): ComputerPlayer{colour}, levelOne{make_unique<LevelOnePlayer>(colour)}{}
LevelTwoPlayer::~LevelTwoPlayer(){}

void LevelTwoPlayer::play(ChessBoard &board) const{
	shared_ptr<const ChessMove> bestMove = getBestCaptureMove(board);
	if(bestMove != nullptr){
		board.executeChessMove(bestMove);
	}else{
		levelOne->play(board);
	}
}
