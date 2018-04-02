#ifndef CLASSIC_CHESS_BOARD_H
#define CLASSIC_CHESS_BOARD_H

#include "chessboard.h"
#include <vector>

class ClassicChessBoard: public ChessBoard{
	public:
	ClassicChessBoard();
	const std::vector<std::vector<int>> getBounds() const override;
};

#endif
