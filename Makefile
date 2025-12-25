CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = main.cpp BMPHeader.cpp BMPImage.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = Images

TEST_SRC = test.cpp BMPHeader.cpp BMPImage.cpp
TEST_BIN = test_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

run: all
	./$(TARGET)

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SRC) -lgtest -lgtest_main -pthread
	./$(TEST_BIN)

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_BIN)

.PHONY: all run clean test

