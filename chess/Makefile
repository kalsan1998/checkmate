CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o humanplayer.o gamecontroller.o player.o piecefactory.o bishop.o chessboard.o invalidmove.o location.o pieceadd.o standardmove.o capture.o chessmove.o emptypiece.o king.o mobilepiece.o piece.o queen.o boardedit.o castling.o knight.o pawn.o pieceremove.o rook.o enpassant.o classicchessboard.o boarddisplay.o textdisplay.o computerplayer.o leveloneplayer.o leveltwoplayer.o levelthreeplayer.o graphicsdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
