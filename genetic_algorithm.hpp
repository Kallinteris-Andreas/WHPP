#ifndef GENETIC_DEF
#define GENETIC_DEF
#include <iostream>
#include "schedule.hpp"

#define MAX_INT 23476867 // not exactly


class genetic_algorithm {
	private:
		int pop;
		schedule* population;
	public:
		genetic_algorithm(int pop);
		int selection();
};
#endif