start: start.o mystery.o
	mpic++ start.o mystery.o -o start

start.o: start.cpp
	mpic++ -Wall -c start.cpp

clean: 
	rm -f start.o start
