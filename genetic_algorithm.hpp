#ifndef GENETIC_DEF
#define GENETIC_DEF
#include <iostream>
#include "schedule.hpp"

#define MAX_INT 23476867 // not exactly


class genetic_algorithm {
	private:
		int pop;
		schedule* population;
		schedule* new_population;
	public:
		genetic_algorithm(int pop);
		int selection();
		void natural_selection();

		void crossbreed_vertical(int a ,int b,int index);
		void crossbreed_vertical_switch(int a ,int b,int index);


		void mutation_reversal(int possibility,int index);
		void mutation_random_column_random_reverse(int possibility,int index);

		schedule whpp();

};
#endif