CXX = g++
CXXFLAGS = -std=c++11
TARGET = client

$(TARGET): linda.h linda.cpp Addons.h Lexer.cpp Lexer.h Main.cpp Parser.cpp Parser.h Source.cpp Source.h Structs.h Token.cpp Token.h
	$(CXX) linda.h linda.cpp Addons.h Lexer.cpp Lexer.h Main.cpp Parser.cpp Parser.h Source.cpp Source.h Structs.h Token.cpp Token.h -o $(TARGET)


.PHONY: clean
clean:
	rm -f *.o
	rm -f *.gch
	rm -f $(TARGET)
