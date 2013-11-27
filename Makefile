prof: start
	g++ start.o mystery.o precomputec.o -g -pg -fopenmp -Ofast -o startp
	./startp
	gprof -b startp gmon.out

start: start.o mystery.o precomputec.o
	g++ start.o mystery.o precomputec.o -fopenmp -Ofast -o start

start.o: start.cpp
	g++ -Wall -fopenmp -Ofast -c -pg start.cpp

precomputec.o: precomputec.cpp
	g++ -Wall -c -Ofast precomputec.cpp

clean: 
	rm -f start.o start
