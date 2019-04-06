CC = g++
BASICFLAGS= 

FLAGS= -Wall $(BASICFLAGS)

OPTFLAG= 

program: employee.o main.o
	$(CC) $(FLAGS) employee.o main.o -o program

main.o: main.cc main.h
	$(CC) -c main.cc

employee.o: employee.cpp employee.hpp
	$(CC) -c employee.cpp

clean:
	rm *.o program

#compile and run
cr:
	make
	./program
