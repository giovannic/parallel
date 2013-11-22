start: start.o mystery.o
	g++ start.o mystery.o -o start

start.o: start.cpp
	g++ -Wall -c start.cpp

clean: 
	rm -f start.o start
