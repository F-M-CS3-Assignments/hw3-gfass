all:
	g++ -std=c++11 -Wall -o tct TimeCode.cpp TimeCodeTests.cpp
run:
	./tct
try: all run