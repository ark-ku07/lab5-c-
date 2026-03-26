CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = cafe
OBJS = main.o cafe.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp cafe.h
	$(CXX) $(CXXFLAGS) -c main.cpp

cafe.o: cafe.cpp cafe.h
	$(CXX) $(CXXFLAGS) -c cafe.cpp

clean:
	del *.o $(TARGET).exe 2> nul || true

run: $(TARGET)
	.\$(TARGET).exe

.PHONY: all clean run