#ifndef GENETIC_DEF
#define GENETIC_DEF
#include <iostream>
#include <fstream>
#include "schedule.hpp"

#define MAX_INT 23476867 // not exactly

//default_random_engine dr (chrono::steady_clock::now().time_since_epoch().count());

class genetic_algorithm {
	private:
		int pop;
		schedule* population;
		schedule* new_population;

		int selection();
		void crossbreed_vertical(int a ,int b,int index);
		void mutation_reversal(int index);
		void mutation_random_column_random_reverse(int index);
		void mutation_daily(int index);
		int best_person();
	public:
		genetic_algorithm(int pop);
		schedule whpp();
};
#endif
