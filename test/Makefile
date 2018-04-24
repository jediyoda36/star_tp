.PHONY: clean all

RM = rm -rf 

CXX = g++
CXXFLAGS = -std=c++11

INC = -I../include
LDFLAGS = -L../lib
LDLIBS = -lstar -lpthread -lboost_system -lboost_thread

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %cpp, %o, $(SRCS))

TARGETS = $(patsubst %cpp, %bin, $(SRCS))

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

%.bin: %.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

all: $(TARGETS)

clean:
	$(RM) $(OBJS) $(TARGETS)
