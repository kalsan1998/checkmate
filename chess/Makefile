CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = location.o pawn.o piece.o chessmove.o pieceremove.o pieceadd.o boardedit.o boardchange.o enpassant.o pawnend.o standardmove.o pawnendcapture.o capture.o pawndouble.o king.o emptypiece.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
