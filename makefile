TARGET = simu_plasma

CXX = g++

CXXFLAGS = -Wall -I./headers

SRC = $(wildcard source/*.cpp)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)