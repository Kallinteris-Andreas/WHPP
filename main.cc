#include "main.h"

int main(){
	schedule sched;
	sched.init();
	sched.print();

	if (sched.satisfy_constraint()){
		std::cout << "The current schedule DOES satisfy the constraint" << std::endl;
		std::cout << "The current score is: " << sched.score() << std::endl;
	}
	else
		std::cout << "The current schedule DOES NOT satisfy the constraint" << std::endl;
	int* x =sched.selection();
	sched.crossbreed_vertical(x[0],x[1],0);
	sched.mutation_random_genes(0.5);
}
