#include "leveltwoplayer.h"
#include "leveloneplayer.h"
#include "chessboard.h"
#include "chessmove.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

LevelTwoPlayer::LevelTwoPlayer(Colour colour): ComputerPlayer{colour}, levelOne{make_shared<LevelOnePlayer>(colour)}{}

void LevelTwoPlayer::play(ChessBoard &board) const{
	shared_ptr<const ChessMove> bestMove = getBestCaptureMove();
	if(bestMove){
		board.executeChessMove(bestMove);
	}else{
		levelOne->play(board);
	}
}
