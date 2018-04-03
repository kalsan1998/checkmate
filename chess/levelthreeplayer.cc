#include "levelthreeplayer.h"
#include "leveltwoplayer.h"
#include "chessboard.h"
#include "chessmove.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

LevelThreePlayer::LevelThreePlayer(Colour colour): ComputerPlayer{colour}, levelTwo{make_shared<LevelTwoPlayer>(colour)}{}

void LevelThreePlayer::play(ChessBoard &board) const{
	shared_ptr<const ChessMove> bestMove = getBestAvoidCaptureMove(board);
	if(bestMove){
		board.executeChessMove(bestMove);
	}else{
		levelTwo->play(board);
	}
}

