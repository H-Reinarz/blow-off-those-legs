# http://www.ijon.de/comp/tutorials/makefile.html

OBJECTS = carPool.o

prog: $(OBJECTS)
	g++ -o outPut.o $(OBJECTS) -std=c++11 -Wall

%.o: carPool.cpp carPool.hpp
	g++ -c carPool.cpp -std=c++11
	
clean:
	rm $(OBJECTS)
