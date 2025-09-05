CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lSDL2

TARGET = sdl_window
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
