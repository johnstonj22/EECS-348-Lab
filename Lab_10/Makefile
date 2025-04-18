CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = calculator.cpp
EXE = calculator

all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE)

clean:
	rm -f $(EXE)

run: $(EXE)
	./$(EXE)