CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = extractNumeric
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC) extractNumeric.h
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
