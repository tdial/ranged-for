CXX=g++
CXXFLAGS=-Wall -Werror -g -std=c++11

all: example

example: example.cc
	$(CXX) $(CXXFLAGS) -o example example.cc

.PHONY:
clean:
	-rm -f example *~

