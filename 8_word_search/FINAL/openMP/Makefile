CXX = g++
CXXFLAGS = -std=c++11 -Wall -fopenmp

SRCS = main.cpp ParallelWordCounter.cpp WordCounter.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = search

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(TXT) $(THREADS)

