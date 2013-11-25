CXX = mpic++

start: start.o mystery.o
	$(CXX) start.o mystery.o -fopenmp -o start

#TODO
prof: start
	$(CXX) start.o mystery.o -g -pg -fopenmp -o startp
	./startp
	gprof startp gmon.out

start.o: start.cpp
	$(CXX) -Wall -c start.cpp

clean: 
	rm -f start.o start
