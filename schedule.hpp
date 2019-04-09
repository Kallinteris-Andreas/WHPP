#ifndef SCHEDULE_DEF
#define SCHEDULE_DEF
#include <iostream>
#include <cstdint>
#include <cstdio>
#include "employee.hpp"
#include "rules.h"
#include <string.h>
#include <random>
#include <stdlib.h>
#include <chrono>

using namespace std;

#define MAX_INT 23476867 // not exactly


class schedule {
	private:
		employee workers[NO_WORKERS];
		//morning_assignments
	public:
		schedule();
		void print();
		void init();
		bool satisfy_constraint();
		int score();
		int score_individual(int worker);

		employee* get_worker(int i){return &workers[i];};
		void set_worker(int i,employee w){workers[i]=w;};

		//Returns 2 indexes considering score_individual 
		int* selection(); 
		//Takes two employee indexes and places their two crossbreeds at a table
		void crossbreed_vertical(int a,int b,int position);
		void crossbreed_horizontal(int a,int b,int position);
		//This mutation occurs with p possibility per chromosome and rotate the whole genome
		void mutation_reversal(int possibility,int index);
		//This mutation occurs with p possibility per chromosome and mutate one random genes
		void mutation_random_genes(int possibility,int index);

		void whpp_algorithm();
};
#endif
