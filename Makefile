start: start.o mystery.o
	g++ start.o mystery.o -fopenmp -o start

prof: start
	g++ start.o mystery.o -g -pg -fopenmp -o startp
	./startp
	gprof -b startp gmon.out

start.o: start.cpp
	g++ -Wall -fopenmp -c start.cpp

clean: 
	rm -f start.o start
