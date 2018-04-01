#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include <memory>

class Piece;

class PieceFactory{
	public:
	static std::shared_ptr<Piece> generatePiece(char c);
	virtual ~PieceFactory() = 0;
};

#endif
