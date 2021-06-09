CXX = g++
CXXFLAGS = -std=c++11
TARGET = linda

$(TARGET): main.cpp linda.h linda.cpp Structs.h
	g++ main.cpp linda.cpp -o $(TARGET)

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.gch
	rm -f $(TARGET)
