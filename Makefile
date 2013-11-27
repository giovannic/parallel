
CXX = mpic++

start: start.o mystery.o precomputec.o
	$(CXX) -fopenmp -Ofast -Wall  start.o mystery.o precomputec.o -o start

start.o: start.cpp
	$(CXX) -fopenmp -Ofast -Wall -c start.cpp

precomputec.o: precomputec.cpp
	$(CXX) -Wall -c precomputec.cpp

clean: 
	rm -f start.o start
