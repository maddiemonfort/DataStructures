all: sparseMatrix

sparseMatrix: main.o
	g++ main.o -o sparseMatrix

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o *gch *stackdump