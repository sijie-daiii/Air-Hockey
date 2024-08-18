# Compiler and flags
CXX = g++
CXXFLAGS = -I../include -g -O0 -std=c++11
LDFLAGS = -lncurses

# Object files
OBJS = main.o slider/slider.o air_hockey/air_hockey.o zone/zone.o ball/ball.o key/key.o score/score.o util/util.o

# Target executable
TARGET = air_hockey_game

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile main.cpp
main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) -o main.o main.cpp

# Compile slider.cpp
slider/slider.o: slider/slider.cpp
	$(CXX) -c $(CXXFLAGS) -o slider/slider.o slider/slider.cpp

# Compile air_hockey.cpp
air_hockey/air_hockey.o: air_hockey/air_hockey.cpp
	$(CXX) -c $(CXXFLAGS) -o air_hockey/air_hockey.o air_hockey/air_hockey.cpp

# Compile zone.cpp
zone/zone.o: zone/zone.cpp
	$(CXX) -c $(CXXFLAGS) -o zone/zone.o zone/zone.cpp

# Compile ball.cpp
ball/ball.o: ball/ball.cpp
	$(CXX) -c $(CXXFLAGS) -o ball/ball.o ball/ball.cpp

# Compile key.cpp
key/key.o: key/key.cpp
	$(CXX) -c $(CXXFLAGS) -o key/key.o key/key.cpp

# Compile score.cpp
score/score.o: score/score.cpp
	$(CXX) -c $(CXXFLAGS) -o score/score.o score/score.cpp

# Compile util.cpp
util/util.o: util/util.cpp
	$(CXX) -c $(CXXFLAGS) -o util/util.o util/util.cpp

# Clean target to remove the executable and object files
clean:
	rm -f $(TARGET) main.o slider/slider.o air_hockey/air_hockey.o zone/zone.o ball/ball.o key/key.o score/score.o util/util.o air_hockey.o ball.o key.o score.o slider.o util.o zone.o

# Phony targets to avoid conflicts with files named 'clean' or 'all'
.PHONY: clean all
