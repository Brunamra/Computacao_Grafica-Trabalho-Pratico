generator: generator.o primitives.o
	g++ -o generator generator.o primitives.o

generator.o: generator.cpp primitives.h
	g++ -c generator.cpp

primitives.o: primitives.h

clean:
	rm *.o *.3d generator