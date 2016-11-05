all: josephus

josephus: josephus.o
	g++ josephus.o -o josephus

josephus.o: josephus.cpp
	g++ -c josephus.cpp

clean:
	rm -rf *o *gch *stackdump