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
}
