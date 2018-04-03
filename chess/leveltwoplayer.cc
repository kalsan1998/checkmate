#include "leveltwoplayer.h"
#include "leveloneplayer.h"
#include <vector>
#include "chessboard.h"
#include "chessmove.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

LevelTwoPlayer::LevelTwoPlayer(Colour colour): ComputerPlayer{colour}, levelOne{make_shared<LevelOnePlayer>(colour)}{}

void LevelTwoPlayer::play(ChessBoard &board) const{
	const vector<shared_ptr<const ChessMove>> moves = getPreferCaptureMoves(board);
	int size = moves.size();
	if(size > 0){
		int randomMove = rand() % size;
		board.executeChessMove(moves[randomMove]);
	}else{
		levelOne->play(board);
	}
}
