all: use1.out

simvd.o: simvd.cpp
	g++ -std=c++11 -c simvd.cpp

use1.out: use1.cpp simvd.o
	g++ -std=c++11 -o use1.out simvd.o use1.cpp
