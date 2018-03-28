#ifndef BOARD_EDIT_H
#define BOARD_EDIT_H

#include "boardchange.h"
#include <memory>

class BoardEdit: public BoardChange{
	protected:
	BoardEdit(std::shared_ptr<Piece> piece);
	shared_ptr<Piece> pieceAffected;

	public:
	virtual bool operator==(BoardEdit &edit) const;
	virtual bool operator!=(BoardEdit &edit) const;

	
	BoardEdit(BoardEdit &&other) noexcept;
	BoardEdit &operator=(BoardEdit &&other) noexcept;
	virtual ~BoardEdit() = 0;
};

#endif
