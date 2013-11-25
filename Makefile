start: start.o mystery.o precomputec.o
	g++ start.o mystery.o precomputec.o -o start

start.o: start.cpp
	g++ -Wall -c start.cpp

precomputec.o: precomputec.cpp
	g++ -Wall -c precomputec.cpp

clean: 
	rm -f start.o start
