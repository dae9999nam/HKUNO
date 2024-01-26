CXX=g++
CXXFLAGS=-pedantic-errors -std=c++11
SRC=main.cpp onehavenocards.cpp random.cpp AI_requestAI.cpp card_effect.cpp display_requestUser.cpp display_waitingForAI.cpp whoWin.cpp display_result.cpp SaveAndLoad.cpp
OBJ=$(SRC:.cpp=.o)
BIN=main

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
