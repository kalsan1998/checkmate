#ifndef BOARD_EDIT_H
#define BOARD_EDIT_H

#include "boardchange.h"
#include <memory>

class Piece;

class BoardEdit: public BoardChange{
	protected:
	BoardEdit(std::shared_ptr<Piece>  piece);
	std::shared_ptr<Piece> pieceAffected;

	public:
	virtual bool operator==(const BoardEdit &edit) const;
	virtual bool operator!=(const BoardEdit &edit) const;

	
	BoardEdit(BoardEdit &&other) noexcept;
	BoardEdit &operator=(BoardEdit &&other) noexcept;
	virtual ~BoardEdit() = 0;
};

#endif
