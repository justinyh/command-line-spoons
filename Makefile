BIN=bin/
CXX=g++
CXXFLAGS=-g -Wall -std=c++11
SRC_DIR=src/
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

DEP=game.o card.o deck.o hand.o spoons.o
OBJS=$(addprefix $(BIN), $(DEP))
all: game

game: $(BIN) $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)
	
$(BIN):
	mkdir $(BIN)

$(BIN)game.o: $(addprefix $(SRC_DIR), card.cpp card.h deck.cpp deck.h hand.cpp hand.h spoons.cpp spoons.h)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c $(SRC_DIR)game.cpp
$(BIN)card.o: $(addprefix $(SRC_DIR),card.cpp card.h)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c $(SRC_DIR)card.cpp
$(BIN)deck.o: $(addprefix $(SRC_DIR),card.h card.cpp deck.cpp deck.h)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c $(SRC_DIR)deck.cpp
$(BIN)hand.o: $(addprefix $(SRC_DIR),card.h card.cpp hand.cpp hand.h)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c $(SRC_DIR)hand.cpp
$(BIN)spoons.o: $(addprefix $(SRC_DIR),spoons.h spoons.cpp)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c $(SRC_DIR)spoons.cpp

clean:
	rm -r bin game