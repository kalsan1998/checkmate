CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = bishop.o chessboard.o invalidmove.o location.o pawnendcapture.o pieceadd.o standardmove.o capture.o chessmove.o emptypiece.o king.o mobilepiece.o pawnend.o piece.o queen.o boardedit.o castling.o knight.o pawndouble.o pawn.o pieceremove.o rook.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
