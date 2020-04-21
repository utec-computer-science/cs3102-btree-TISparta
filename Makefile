CXX = g++
CXXFLAGS = -std=c++14 -O2 -lgtest -lgtest_main -pthread

test: FORCE
	$(CXX) -o $@ $(CXXFLAGS) test.cpp

FORCE: ;

clean:
	rm test
