CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -Wsuggest-override -g -std=c++17
LDFLAGS=

all: build



build: main.o AIComputerPlayer.o Bishop.o Board.o Castle.o \
DummyComputerPlayer.o MediumComputerPlayer.o Game.o King.o \
Queen.o Pawn.o Knight.o LocalPlayer.o Player.o Serialization.o

compile: main.o AIComputerPlayer.o Bishop.o Board.o Castle.o \
DummyComputerPlayer.o MediumComputerPlayer.o Game.o King.o \
Queen.o Pawn.o Knight.o LocalPlayer.o Player.o Serialization.o
	${LD} ${LDFLAGS} $^ -o chess

run:
	./chess
doc:
	

%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@
	
AIComputerPlayer.o: src/AIComputerPlayer.cpp src/AIComputerPlayer.hpp \
  src/MediumComputerPlayer.hpp src/Player.hpp src/GameEvent.h \
  src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
AIComputerPlayer.o: src/AIComputerPlayer.hpp src/MediumComputerPlayer.hpp \
  src/Player.hpp src/GameEvent.h src/Figure.h src/Board.hpp src/Ceil.h \
  src/Move.h
Bishop.o: src/Bishop.cpp src/Bishop.hpp src/Figure.h src/Board.hpp \
  src/Ceil.h src/Move.h
Bishop.o: src/Bishop.hpp src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Board.o: src/Board.cpp src/Board.hpp src/Ceil.h src/Figure.h src/Move.h \
  src/GameEvent.h src/Pawn.hpp src/King.hpp src/Queen.hpp src/Bishop.hpp \
  src/Knight.hpp src/Castle.hpp
Board.o: src/Board.hpp src/Ceil.h src/Figure.h src/Move.h
Castle.o: src/Castle.cpp src/Castle.hpp src/Figure.h src/Board.hpp \
  src/Ceil.h src/Move.h
Castle.o: src/Castle.hpp src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Ceil.o: src/Ceil.h src/Figure.h src/Board.hpp src/Move.h
DummyComputerPlayer.o: src/DummyComputerPlayer.cpp \
  src/DummyComputerPlayer.hpp src/Player.hpp src/GameEvent.h \
  src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
DummyComputerPlayer.o: src/DummyComputerPlayer.hpp src/Player.hpp \
  src/GameEvent.h src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Figure.o: src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Game.o: src/Game.cpp src/Game.hpp src/Board.hpp src/Ceil.h src/Figure.h \
  src/Move.h src/DummyComputerPlayer.hpp src/Player.hpp src/GameEvent.h \
  src/LocalPlayer.hpp src/MediumComputerPlayer.hpp \
  src/AIComputerPlayer.hpp src/Serialization.hpp src/Queen.hpp \
  src/Bishop.hpp src/Knight.hpp src/Castle.hpp
Game.o: src/Game.hpp src/Board.hpp src/Ceil.h src/Figure.h src/Move.h \
  src/DummyComputerPlayer.hpp src/Player.hpp src/GameEvent.h \
  src/LocalPlayer.hpp src/MediumComputerPlayer.hpp \
  src/AIComputerPlayer.hpp src/Serialization.hpp
GameEvent.o: src/GameEvent.h
King.o: src/King.cpp src/King.hpp src/Figure.h src/Board.hpp src/Ceil.h \
  src/Move.h src/GameEvent.h src/Castle.hpp
King.o: src/King.hpp src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Knight.o: src/Knight.cpp src/Knight.hpp src/Figure.h src/Board.hpp \
  src/Ceil.h src/Move.h
Knight.o: src/Knight.hpp src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
LocalPlayer.o: src/LocalPlayer.cpp src/LocalPlayer.hpp src/Player.hpp \
  src/GameEvent.h src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
LocalPlayer.o: src/LocalPlayer.hpp src/Player.hpp src/GameEvent.h \
  src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
MediumComputerPlayer.o: src/MediumComputerPlayer.cpp \
  src/MediumComputerPlayer.hpp src/Player.hpp src/GameEvent.h \
  src/Figure.h src/Board.hpp src/Ceil.h src/Move.h src/King.hpp \
  src/Queen.hpp src/Bishop.hpp src/Castle.hpp src/Pawn.hpp \
  src/Knight.hpp
MediumComputerPlayer.o: src/MediumComputerPlayer.hpp src/Player.hpp \
  src/GameEvent.h src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Move.o: src/Move.h src/Ceil.h src/Figure.h src/Board.hpp
Pawn.o: src/Pawn.cpp src/Pawn.hpp src/Figure.h src/Board.hpp src/Ceil.h \
  src/Move.h src/GameEvent.h
Pawn.o: src/Pawn.hpp src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Player.o: src/Player.hpp src/GameEvent.h src/Figure.h src/Board.hpp \
  src/Ceil.h src/Move.h
Queen.o: src/Queen.cpp src/Queen.hpp src/Figure.h src/Board.hpp \
  src/Ceil.h src/Move.h src/Bishop.hpp src/Castle.hpp
Queen.o: src/Queen.hpp src/Figure.h src/Board.hpp src/Ceil.h src/Move.h
Serialization.o: src/Serialization.hpp
main.o: src/main.cpp src/Game.hpp src/Board.hpp src/Ceil.h src/Figure.h \
  src/Move.h src/DummyComputerPlayer.hpp src/Player.hpp src/GameEvent.h \
  src/LocalPlayer.hpp src/MediumComputerPlayer.hpp \
  src/AIComputerPlayer.hpp src/Serialization.hpp

clean:
	rm -f main.o AIComputerPlayer.o Bishop.o Board.o Castle.o \
DummyComputerPlayer.o MediumComputerPlayer.o Game.o King.o \
Queen.o Pawn.o Knight.o LocalPlayer.o Player.o Serialization.o chess
