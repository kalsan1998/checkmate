#include "leveloneplayer.h"
#include <vector>
#include "chessboard.h"
#include "chessmove.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

LevelOnePlayer::LevelOnePlayer(Colour colour): ComputerPlayer{colour}{}

void LevelOnePlayer::play(ChessBoard &board) const{
	const vector<shared_ptr<const ChessMove>> moves = getAllMoves(board);
	int size = moves.size();
	int randomMove = rand() % size;
	board.executeChessMove(moves[randomMove]);
}
