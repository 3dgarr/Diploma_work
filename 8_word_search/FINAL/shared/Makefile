CXX = mpic++
CXXFLAGS = -std=c++11 -Wall

SRCS = $(wildcard *.cpp)
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

re: clean all

run: $(EXEC)
	mpirun -np $(NP) ./$(EXEC) $(TXT)

