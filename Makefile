prof: start
	g++ start.o mystery.o precomputec.o -g -pg -fopenmp -o startp
	./startp
	gprof -b startp gmon.out

start: start.o mystery.o precomputec.o
	g++ start.o mystery.o precomputec.o -fopenmp -o start

start.o: start.cpp
	g++ -Wall -fopenmp -c start.cpp

precomputec.o: precomputec.cpp
	g++ -Wall -c precomputec.cpp

clean: 
	rm -f start.o start
