CC=g++
CFLAGS=-Wall -g
progname=CHESS

VPATH=backend;frontend
BACKENDFILES=draw.o game.o piece.o pawn.o knight.o rook.o bishop.o queen.o king.o space.o util.o
FRONTENDFILES=table.o

# SDL Includes Flags
WINDOWS_LINK_FLAGS=-lmingw32 -lSDL2main -lSDL2
# On my machine I put the SDL library files in a folder
# "sdl_dev" inside my root C directory.  You will need to
# change this for your system.
SDL_INCLUDE=-IC:\sdl_dev\include\ -LC:\sdl_dev\lib


# man I probably should have spent the time learning cmake but
# my arrogance and lack of wanting to learn cmake have led me
# to creating an incredibly system specific makefile.
all: $(BACKENDFILES) $(FRONTENDFILES)
	$(CC) prog.cpp $^ -o $(progname) $(SDL_INCLUDE) $(WINDOWS_LINK_FLAGS)


# If you are on linux you will want to replace the "del" with "rm -f"
# If you are on Mac I think it's the same (but idk never used macos)
# If you are on ReactOS, why are you trying to run this lame chess game?
clean:
	del *.o $(progname)


game.o: game.cpp game.h
	$(CC) -c $< $(CFLAGS)

space.o: space.cpp space.h piece.o move.h
	$(CC) -c $< $(CFLAGS)

piece.o: piece.cpp piece.h move.h
	$(CC) -c $<  $(CFLAGS)

pawn.o: pawn.cpp pawn.h piece.o
	$(CC) -c $<  $(CFLAGS)

knight.o: knight.cpp knight.h piece.o
	$(CC) -c $<  $(CFLAGS)

rook.o: rook.cpp rook.h piece.o
	$(CC) -c $<  $(CFLAGS)

bishop.o: bishop.cpp bishop.h piece.o
	$(CC) -c $<  $(CFLAGS)

queen.o: queen.cpp queen.h piece.o
	$(CC) -c $<  $(CFLAGS)

king.o: king.cpp king.h
	$(CC) -c $<  $(CFLAGS)

util.o: util.cpp util.h
	$(CC) -c $<  $(CFLAGS)

table.o: table.cpp table.h
	$(CC) -c $< $(CFLAGS)
