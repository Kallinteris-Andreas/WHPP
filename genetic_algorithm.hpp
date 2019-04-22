#ifndef GENETIC_DEF
#define GENETIC_DEF
#include <iostream>
#include "schedule.hpp"

#define MAX_INT 23476867 // not exactly

//default_random_engine dr (chrono::steady_clock::now().time_since_epoch().count());

class genetic_algorithm {
	private:
		int pop;
		schedule* population;
		schedule* new_population;

		int best_person();
	public:
		genetic_algorithm(int pop);
		int selection();
		void natural_selection();

		void crossbreed_vertical(int a ,int b,int index);


		void mutation_reversal(int possibility,int index);
		void mutation_random_column_random_reverse(int possibility,int index);

		schedule whpp();

};

int rand(int lim){
	static default_random_engine dr (chrono::steady_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> uid {0,lim};
	return uid(dr);
}

#endif
