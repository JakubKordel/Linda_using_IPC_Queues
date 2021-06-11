CXX = g++
CXXFLAGS = -std=c++11 -fno-stack-protector
TARGET = server

$(TARGET): main.o
	$(CXX) main.o -o $(TARGET)

main.o: main.cpp Server.h
	$(CXX) $(CXXFLAGS) -c main.cpp Server.h

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.gch
	rm -f $(TARGET)
