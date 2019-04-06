CC = g++
BASICFLAGS= 

FLAGS= -Wall $(BASICFLAGS)

OPTFLAG= 

program: employee.o main.o schedule.o rules.o
	$(CC) $(FLAGS) employee.o main.o schedule.o rules.o -o program

main.o: main.cc main.h
	$(CC) -c main.cc

employee.o: employee.cpp employee.hpp
	$(CC) -c employee.cpp

schedule.o: schedule.cpp schedule.hpp score_schedule.cpp
	$(CC) -c schedule.cpp

rules.o: rules.cc rules.h
	$(CC) -c rules.cc

clean:
	rm *.o program

#compile and run
cr:
	make
	./program
