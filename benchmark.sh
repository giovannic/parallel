make clean
g++ -Wall -fopenmp -Ofast -pg -c start.cpp  
g++ start.o mystery.o precomputec.o -g -pg -fopenmp -Ofast -o startp
./startp
gprof startp gmon.out > benchmark.out
