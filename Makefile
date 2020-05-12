CXX = g++
CXXFLAGS = -std=c++14 -O2 -lgtest -lgtest_main -pthread

all: FORCE
	$(CXX) -o btree-test $(CXXFLAGS) btree-test.cpp
	$(CXX) -o bplustree-test $(CXXFLAGS) bplustree-test.cpp

FORCE: ;

clean:
	rm btree-test
